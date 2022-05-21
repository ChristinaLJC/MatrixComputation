#include "Alias.hpp"
#include "Matrix.hpp"
#include "MException.hpp"
#include "MHighPrecision.hpp"

namespace Mx = Matrix; 

TEST_METHOD {
    using namespace Mx; 
    auto v = 1233211234567_pn; 
    bassert_eq_actual_expect(to_string(v), "1233211234567");
}

TEST_METHOD {
    using namespace Mx; 
    auto v = 0xf_pn; 
    bassert_eq_actual_expect(to_string(v), "15");
}

TEST_METHOD {
    using namespace Mx; 
    auto v = 0b1111'1111_pn;
    bassert_eq_actual_expect(to_string(v), "255");
}

TEST_METHOD {
    using namespace Mx; 
    auto v = 077_pn; 
    bassert_eq_actual_expect(to_string(v), "63");
}

TEST_METHOD {
    using namespace Mx; 
    // What's the value of factorial of 20. 
    auto v = 1_pn; 
    for (auto i = 1; i <= 20; ++i) 
        mul_u32_then_eq(v, i);
    using std::literals::operator""s; 
    println("1 * 2 * ... * 20 = "s + to_string(v));
    bassert_eq_actual_expect(to_string(v), "2432902008176640000"); 
}

TEST_METHOD {
    using namespace Mx; 
    auto v = 1_pn; 
    auto sum = 0_pn; 
    for (auto i = 1; i <= 20; ++i) {
        mul_u32_then_eq(v, i); 
        add_pn_then_eq(sum, v); 
    }
    using std::literals::operator""s; 
    println("1 + 1 * 2 + ... + 1 * --- * 20 = "s + to_string(sum));
}

TEST_METHOD {
    using namespace Mx; 
    auto identity = 14_pn; 
    auto exp = 14_pn; 
    for (auto i = 0; i < 14; ++i) {
        mul_pn_then_eq(identity, exp); 
    }
    for (auto i = 0; i < 14; ++i) {
        mul_u32_then_eq(exp, 14); 
    }
    bassert_eq_actual_expect (to_string(identity), to_string(exp));
    using namespace std::literals; 
    println("14 ^ 15 = "s + to_string(identity)); 
}

TEST_METHOD {
    using namespace Mx; 
    auto identity = 15_pn; 
    auto multiplier = 14_pn;
    auto result = 1_pn;
    uint32_t remain; 
    while (!is_zero(identity)) {
        if (mod_v_2(identity)) {
            mul_pn_then_eq(result, multiplier);  
        } 
        mul_pn_then_eq(multiplier, multiplier); 
        div_u32_then_eq(identity, 2); 
    }
    using namespace std::literals; 
    println("14 ^ 15 = "s + to_string(result)); 
}