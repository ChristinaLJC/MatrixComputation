#include "def/uint128_t.hpp"

Use matrix; 

TEST_METHOD {
    u128 a; 
    bassert(a * 3u == 0u); 
}

TEST_METHOD {
    u128 seven = 7u; 
    bassert_eq (seven *= seven, 49u); 
}


TEST_METHOD {
    u128 big_number = 9999999u; 
    bassert_eq(big_number / 9u, 1111111u); 
}

TEST_METHOD {
    u128 alpha = 1u; 
    constexpr u32 up_bound = 5; 
    for (u32 i {}; i < up_bound; ++i) {
        // println(alpha); 
        alpha *= i + 1; 
    }
    for (u32 i {}; i < up_bound; ++i) {
        alpha /= i + 1; 
        // println(alpha); 
    }
    bassert_eq(alpha, 1u); 
}

TEST_METHOD {
    u128 t = 77u; 
    t /= t; 
    println(t); 
}
