#include "def/uint128_t.hpp"

Use matrix; 

TEST_METHOD {
    u128 x = 0u; 
    x = ~x; 
    ++x; 
    bassert_eq(x, 0u); 
}

TEST_METHOD {
    u128 x = 77u; 
    x += ~x; 
    ++x; 
    bassert_eq(x, 0u); 
}