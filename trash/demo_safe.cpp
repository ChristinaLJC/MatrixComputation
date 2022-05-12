#include "safe.hpp" 

#include <iostream> 

using matrix::Option, matrix::Result; 
using matrix::overloaded; 

Result<int, std::logic_error> double_a_integer(int v) {
    // using namespace std::literals;
    if (v >= 0)
        return v * 2; 
    else 
        return std::logic_error{"Input a negative value. "}; 
}

Result<int, std::logic_error> revert_integer(int v) {
    using namespace std::literals;
    if (v > 0 && v < 10) 
        return 10 - v; 
    else 
        return std::logic_error{"Invoke "s + __FUNCTION__ + " with an invalid value: arg v = " + std::to_string(v)}; 
}

[[maybe_unused]] Result<std::monostate, std::logic_error> method(int input) {
    auto ans = $(revert_integer(
        $(double_a_integer(input))
    )); 
    std::cout << "revert ( double ( " << input << " ) ) = " << ans << "\n"; 
    return std::monostate{}; 
}

int main() {
    auto test_list = {-1, 0, 1, 4, 6, 11}; 
    for (auto t: test_list) {
        std::cout << "Invoke method(" << t << "): \n"; 
        auto err = method(t); 
        std::cout << err.try_what() << std::endl; 
    }
}
