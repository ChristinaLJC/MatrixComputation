#include "def/uint128_t.hpp" 

TEST_METHOD {
    matrix::u128 v; 
    bassert (!v); 
}

TEST_METHOD {
    Use matrix; 
    u128 v; 
    v = v + 5u; 
    bassert (v == 5u); 
}

TEST_METHOD {
    Use matrix; 
    u128 v; 
    v += 5u; 
    bassert (v == 5u); 
}
