#include "std.hpp"

struct AssertError: public std::runtime_error {
    private:
    std::function<std::string ()> error_message;  
    public: 
    AssertError(std::function<std::string ()> message) : std::runtime_error(""), error_message(std::move(message)) {} 
    AssertError(std::string message): AssertError([mess = std::move(message)]() {return mess; } ) {} 
    AssertError(char const *message): AssertError(std::string(message)) {} 
    std::string what_as_string() const {
        return error_message(); 
    } 
};


#ifdef __cpp_lib_source_location
void bassert (bool bool_expression, std::string info = "", std::source_location const location = std::source_location::current()) {
    if (!bool_expression) {
        using namespace std::literals; 
        throw AssertError("file: "s + location.file_name() + '(' + location.line() 
            + ':' + location.column() + ')' + ' ' + '\'' + location.function_name() + '\'' + ':'
            + ' ' + info); 
    }
}
#else 
void bassert (bool bool_expression, std::string info = "") {
    if (!bool_expression)
        throw AssertError(std::move(info)); 
}
#endif
template <typename T, typename V> 
void bassert_eq(T &&t, V &&v) {
    if (t != v) {
        std::stringstream error_info; 
        error_info << "[Equivalent Assertion Fail: ] Expected: \""
            << v 
            << "\", Actual: \"" 
            << t 
            << "\". \n";
        throw AssertError(error_info.str());
    }
}

thread_local static std::vector<std::string> infos; 

void println(auto &&to_print) {
    infos.push_back(std::forward<decltype(to_print)>(to_print));
}

template <typename T, typename V> 
void bassert_eq_actual_expect(T &&t, V &&v) {
    bassert_eq(std::forward<T>(t), std::forward<V>(v));
}

template <size_t > 
void test(); 

template <size_t s, typename T> 
void helper(T &in) {
    if constexpr (s > 0) {
        if constexpr (s > 1)
            helper<s-1>(in);
        auto job = []() -> std::pair<double, std::vector<std::string>>{
            auto begin = std::chrono::high_resolution_clock::now(); 
            test<s-1>(); 
            return 
                {std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() / 1e9, 
                    std::move(infos)}; 
        }; 
        in.push_back(std::async(job));
    }
}

#define TEST_METHOD template<> void test<__COUNTER__>()

#ifndef TEST_FILE
#error Please use -D to define the test file. Suggested: -D TEST_FILE=\"{your file path}\". Demo: TEST_FILE=\"test.cpp\"
#else 
#include TEST_FILE
#endif

size_t constexpr END_TEST_NUMBERS = __COUNTER__; 

#ifndef TIME_OUT 
#define TIME_OUT 3s 
#endif

// std::wstring get_from_result(std::vector<std::variant<std::monostate, AssertError, double>> &results) {
std::wstring get_from_result(auto &results) {

    std::wstringstream print_out_message; 

    size_t successful{}; 
    size_t fails {}; 

    double average_time {}; 

    for (auto &it: results) {
        if (auto fail_sit = std::get_if<AssertError>(&it); fail_sit) {
            ++fails; 
        } else if (auto succ_sit = std::get_if<std::pair<double, std::vector<std::string>>>(&it); succ_sit) {
            ++successful; 
            average_time += std::get<double>(*succ_sit);
        }
    }

    average_time /= successful; 

    double successful_percent = double(successful) / results.size(); 
    double fail_or_successful_percent = double (results.size() - fails) / results.size(); 

    print_out_message << L"\033[96m测试台所有测试完成，共 " << results.size() << L" 组测试进行完毕。\n\n" 
        << L"\033[37m测试信息汇总：\n\t" << successful << L" 组测试通过，平均用时 " << average_time * 1e3 << L" ms. " 
        << L"\n\t" << fails << L" 组测试失败。" 
        << L"\n\t" << results.size() - successful - fails << L" 组测试超时。\n\n"; 
    
    constexpr int BLOCK_NUM = 50; 

    print_out_message << L"\033[97m["; 

    int now = 0; 
    print_out_message << L"\033[92m"; 
    for (;now < int(successful_percent * BLOCK_NUM); ++now) {
        print_out_message << L'='; 
    } 
    print_out_message << L"\033[93m"; 
    for (; now < int(fail_or_successful_percent * BLOCK_NUM); ++now) {
        print_out_message << L'='; 
    }
    print_out_message << L"\033[91m"; 
    for (; now < BLOCK_NUM; ++now) {
        print_out_message << L'='; 
    }
    print_out_message << L"\033[97m]\n"; 
    if (fails > 0) {
        print_out_message << L"\n发生错误测试列表：\n\n"; 
        for (int i = 0; i < results.size(); ++i) {
            if (auto err_pt = std::get_if<AssertError>(&results.at(i)); err_pt) {
                print_out_message << L'\t' << i << L':' << L' '
                    << std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(err_pt->what_as_string()) << L'\n'; 
            }
        }
    }
    if (fails + successful < results.size()) {
        print_out_message << L'\n' << L"超时的测试点：\n\n\t"; 
        {
            bool have_blank = false; 
            for (int i = 0; i < results.size(); ++i) {
                if (auto overtime_p = std::get_if<std::monostate>(&results.at(i)); overtime_p) {
                    if (have_blank)
                        print_out_message << L' '; 
                    print_out_message << i; 
                    have_blank = true; 
                }
            }
            print_out_message << L'\n'; 
        }
    }
    print_out_message << L'\n' << L'\n';
    print_out_message << L"----------------------------------------------------"; 
    print_out_message << L'\n' << L'\n';
    {
        print_out_message << L"成功通过的测试点：\n\n";  
        size_t cnt {}; 
        for (auto &i : results) {
            if (auto p = std::get_if<std::pair<double, std::vector<std::string>>>(&i); p) {
                print_out_message << '\t' << cnt << L": 花费时间 " << std::get<double>(*p) << " ms. \n"; 
                auto &&infos = std::get<std::vector<std::string>>(*p); 
                if (infos.size()) {
                    print_out_message << L"\t运行过程输出：\n\t"; 
                    for (auto &&to_out: infos) {
                        print_out_message << std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(std::move(to_out)) << L'\n'; 
                    }
                }
                print_out_message << L'\n'; 
            }
            ++cnt; 
        }
    }
    return print_out_message.str(); 
}

// void deal_result(std::vector<std::variant<std::monostate, AssertError, double>> &results) {
void deal_result (auto &results) {
    auto message = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(get_from_result(results)); 
    for (auto i: message) {
        using namespace std::literals::chrono_literals; 
        // std::wcout << int(i) << ' '; 
        // std::wcout.flush(); 
        std::cout << i; 
        std::cout.flush(); 
        std::this_thread::sleep_for(5703us); 
    }
}

int main() {
    std::vector<std::future<std::pair<double, std::vector<std::string>>>> asyncs; 
    asyncs.reserve(END_TEST_NUMBERS); 

    helper<END_TEST_NUMBERS>(asyncs); 

    using namespace std::literals::chrono_literals; 
    auto until = std::chrono::high_resolution_clock::now() + TIME_OUT;

    std::vector<std::variant<std::monostate, AssertError, std::pair<double, std::vector<std::string>>>> results (asyncs.size()); 

    while (std::chrono::high_resolution_clock::now() <= until) {
        bool flag = true; 
        for (size_t i = 0; i < results.size(); ++i) {
            if (auto pt = std::get_if<std::monostate>(&results.at(i)); pt) {
                // Find a flag do not finish well! 
                if (auto state = asyncs.at(i).wait_for(0s); state == std::future_status::ready) {
                    try {
                        results.at(i) = std::move(asyncs.at(i).get()); 
                    } catch (AssertError &error) {
                        results.at(i).emplace<AssertError>(std::move(error)); 
                    } catch (std::exception &run_error) {
                        using std::literals::operator""s; 
                        results.at(i).emplace<AssertError>("[Runtime Error]: "s + run_error.what()); 
                    }
                } else {
                    flag = false; 
                }
            }
        }
        if (flag) 
            break; 
    }

    deal_result(results); 

    exit(0);
}