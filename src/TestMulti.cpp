#include "BasicCal.hpp"

namespace P {
    using namespace Matrix; 
    using namespace std::literals; 
}

#define Use using namespace 

TEST_METHOD {

    Use P; 

    auto left_hs = 99999999999999999999_pn; // 20 numbers. 
    auto right_hs = 1_pn; 

    auto ans = mul_pn(left_hs, right_hs); 

    // println(to_string(left_hs) + " times " + to_string(right_hs) + " equals " + to_string(ans)); 
    bassert_eq_actual_expect(to_string(ans), "99999999999999999999"); 
}

TEST_METHOD {

    Use P; 

    auto left_hs = 7372871937307182_pn; 
    auto right_hs = 9482812340860233678342_pn; 

    auto ans = mul_pn(left_hs, right_hs); 

    // The result is powered by python! 
    bassert_eq_actual_expect(to_string(ans), "69915560994678644586800144790234452244"); 

}

TEST_METHOD {
    
    Use P; 

    // Codes from Christina Branch 

    auto left_hs = 99999999999999999999_pn;
    auto right_hs = 1_pn;
    auto ans = mul_pn(left_hs, right_hs);
    
    println(to_string(ans));

    std::vector<uint32_t> result;

}