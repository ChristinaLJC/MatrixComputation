#include "def/uint128_t.hpp"

Use matrix; 

TEST_METHOD {
    u128 d = 1234u; 
    u128 f = 2u; 
    d = d % f; 
    bassert_eq(d, 0u); 
}

TEST_METHOD {
    u128 d = 107u; 
    u128 d2 = 7u; 
    bassert_eq(d2 % d, 7u); 
}

TEST_METHOD {
    u128 d = 107u; 
    u128 d2 = 7u; 
    bassert_eq(d % d2, 2u); 
}