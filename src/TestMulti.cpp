#include "BasicCal.hpp"

TEST_METHOD {
    using namespace Matrix;
    using namespace std::literals;
    auto left_hs = 99999999999999999999_pn;
    auto right_hs = 1_pn;
    auto ans = mul_pn(left_hs, right_hs);
    
    println(to_string(ans));

    std::vector<uint32_t> result;
}