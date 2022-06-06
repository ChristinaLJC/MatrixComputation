#include "def/uint128_t.hpp"

Use matrix; 

TEST_METHOD {
    auto v = 0x144_u128; 
    bassert_eq (v, 324u); 
}

TEST_METHOD {
    auto a = 18446744073709551615_u128; 
    a += 1u; 
    bassert_eq (a, 18446744073709551616_u128); 
}

TEST_METHOD {
    auto a = 340282366920938463463374607431768211455_u128; 
    a += 1u; 
    // It would meets an overflow! 
    bassert (!a); 
}

TEST_METHOD {
    // This statement would meets an static-assert error! 
    // auto a = 340282366920938463463374607431768211456_u128; 
    bassert (true); 
}

TEST_METHOD {
    auto t = 20220606_u128; 
    auto t2 = 20220606_uint128_t; 
    bassert_eq (t, t2); 
}

TEST_METHOD {
    u128 special = 0b1'000_u128; 
    bassert_eq (special, 8u); 
}