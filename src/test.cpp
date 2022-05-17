#include "Matrix.hpp" 

TEST_METHOD {
    auto x = 3; 
    auto y = 5; 
    bassert(x + y == 8, "x + y == 8 when in context that {x = 3, y = 5}. ");
}

TEST_METHOD {
    int result {}; 
    for (int i = 0; i < 100; ++i) {
        result += i; 
    }
    bassert (result == 4950, "0 + 1 + ... + 98 + 99 == 4950. "); 
}

TEST_METHOD {
    float f = 1. / 3; 
    bassert (f * 3 == 1, "0.33... * 3 == 1");
}

TEST_METHOD {
    bassert (1 == 2, "1 == 2");
}

TEST_METHOD {
    constexpr auto is_prime = [](auto i) {
        for (decltype(i) it = 2; it < i; ++it) {
            if (i % it == 0)
                return false; 
            if (it * it > i)
                break; 
        }
        return true; 
    };
    bassert (is_prime(2), "2 is a prime. ");
    bassert (is_prime(7), "7 is a prime. "); 
    bassert (!is_prime(42), "42 isn't a prime. "); 
    bassert (is_prime(1201), "1201 is a prime. ");
    bassert (!is_prime(1919), "1919 isn't a prime. "); 
    bassert (!is_prime(-6), "-6 isn't a prime. ");
}

TEST_METHOD {
    using namespace Matrix; 
    auto x = std::vector{7, 6, 4, 6, 7}; 
    auto y = std::vector{1, 2, 5, 2, 1}; 
    auto &&together = add(x, y); 
    bassert (together == std::vector{8, 8, 9, 8, 8}, "{7,6,4,6,7} + {1,2,5,2,1} = {8,8,9,8,8}. ");
}

TEST_METHOD {
    using namespace Matrix; 
    auto x = {1., 0.1, 0.01, 0.001, 0.0001}; 
    auto y = {-1., -0.1, -0.01, -0.001, -0.0001};
    auto &&plus = add(x, y); 
    bassert (plus == std::vector<double>{0, 0, 0, 0, 0}, "{1, 0.1, ... 0.0001} + {-1, -0.1, ... -0.0001} equals {0 ... 0}. ");
}

TEST_METHOD {
    using namespace Matrix; 
    constexpr auto equal_seq_generator = [](auto start, size_t length, auto step) {
        std::vector<decltype(start + step)> ans; 
        ans.reserve(length); 
        for (size_t i {}; i < length; ++i) {
            ans.push_back(start + step * i); 
        }
        return ans; 
    }; 
    auto f1 = equal_seq_generator(3, 5, 2); 
    auto f2 = equal_seq_generator(4, 5, 1); 
    auto &&f3 = add(f1, f2); 
    bassert (f3 == equal_seq_generator(7, 5, 3), "[3, 5, 7 ...] + [4, 5, 6 ...] == [7, 10, 13 ...] for length = 5. "); 
}

TEST_METHOD {
    constexpr auto is_prime_naive = [](size_t val) {
        for (size_t i = 2; i < val; ++i) {
            if (val % i == 0)
                return false; 
        }
        return true; 
    }; 
    bassert (!is_prime_naive(12011436), "12011436 isn't a prime number. "); 
    bassert (!is_prime_naive(12012908), "12012908 isn't a prime number. "); 
    bassert (is_prime_naive(0xdeadbeef), "DeadBeaf is a prime number. ");
}

TEST_METHOD {
    constexpr auto is_prime_naive = [](size_t val) {
        for (size_t i = 2; i < val; ++i) {
            if (val % i == 0)
                return false; 
        }
        return true; 
    }; 
    bassert (!is_prime_naive(20220516), "Today 2022-05-16 isn't a prime number. ");
}

TEST_METHOD {
    std::vector<uint32_t> vals {1}; 
    bassert (vals.size() == 1 && vals.at(0) == 1, "vals == [1]");

    auto multi = [&vals] (uint32_t val) {
        uint64_t cache {}; 
        for (auto &&tmp: vals) {
            uint64_t cal = (uint64_t) tmp * val + cache;
            tmp = cal & 0xFFFFFFFF; 
            cache = cal >> 32; 
        }
        if (cache > 0)
            vals.push_back(cache); 
        bassert (cache <= 0xFFFFFFFF, "cache should less than the normal val. "); 
    }; 

    for (uint32_t i = 1; i < 60; ++i) 
        multi(i); 
    
    auto show = [] (auto &to_show_vec) {
        std::stringstream to_show_str; 
        to_show_str << "0x"; 
        auto &&it = to_show_vec.crbegin(); 
        // to_show_str.setw(8); 
        to_show_str << std::hex; 
        to_show_str << *it; 
        for (++it; it != to_show_vec.crend(); ++it) {
            to_show_str << std::setfill('0');
            to_show_str << std::setw(8); 
            to_show_str << *it; 
        }
        return to_show_str.str(); 
    }; 

    using std::literals::operator ""s; 
    bassert (false, "1 * 2 * ... * 59 = "s + show(vals));
}

TEST_METHOD {
    int x; 
    while (true) {
        ++x; 
    }
}

TEST_METHOD {
    using namespace Matrix; 
    auto x = {1, 2, 3}; 
    auto y = {2, 4} ;
    auto &&plus = add(x, y); 
    bassert (plus == std::vector{3, 6, 3}, "{1,2,3} + {2,4} should equals {3,6,3}. ");   
}

// This method is powered by Huang Haonan 
TEST_METHOD{
    std::vector<uint32_t> vals1 {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF};
    std::vector<uint32_t> vals2 {1};
    if (vals1.size() < vals2.size())
        std::swap(vals1, vals2);

    std::vector<uint32_t> result = vals1;

    uint64_t remain = {};
    for (uint32_t i = 0; i < vals1.size(); ++i) {
        if (i < vals2.size())
            remain += (uint64_t) vals1.at(i) + vals2.at(i);
        else remain += (uint64_t) vals1.at(i);
        result.at(i) = remain & 0xFFFFFFFF;
        remain >>= 32;
    };
    if (remain > 0)
        result.push_back(remain);
    auto show = [] (auto &to_show_vec) {
        std::stringstream to_show_str;
        to_show_str << "0x";
        auto &&it = to_show_vec.crbegin();
        // to_show_str.setw(8);
        to_show_str << std::hex;
        to_show_str << *it;
        for (++it; it != to_show_vec.crend(); ++it) {
            to_show_str << std::setfill('0');
            to_show_str << std::setw(8);
            to_show_str << *it;
        }
        return to_show_str.str();
    };

    using std::literals::operator ""s;
    bassert (false, "0 + 1 = "s + show(result));
};

// This method is powered by Huang Haonan 
TEST_METHOD {
    std::vector<uint32_t> vals {101};
    uint32_t di = 7;

    uint64_t remain {};
    std::vector<uint32_t> quotient {};
    for (uint32_t i = vals.size()-1; i != 0xFFFFFFFF; i--){
        remain += vals.at(i);
        quotient.push_back(remain / di);
        remain %= di;
        remain <<= 32;
    }
    quotient = std::vector(quotient.rbegin(), quotient.rend()); 
    auto show = [] (auto &to_show_vec) {
        bassert(to_show_vec.size(), "Number shouldn't equals 0. "); 
       std::stringstream to_show_str;
       to_show_str << "0x";
       auto &&it = to_show_vec.crbegin();
       // to_show_str.setw(8);
       to_show_str << std::hex;
       to_show_str << *it;
       for (++it; it != to_show_vec.crend(); ++it) {
           to_show_str << std::setfill('0');
           to_show_str << std::setw(8);
           to_show_str << *it;
       }
       return to_show_str.str();
    };

    using std::literals::operator ""s;
    bassert (false, "101 / 7= "s + show(quotient));
}