#include "def/uint128_t.hpp"

Use matrix; 

TEST_METHOD {
    u128 v = 2u; 
    u128 v2 = 3u; 
    bassert (v != v2); 
}

TEST_METHOD {
    u128 v = 7u; 
    bassert (v == 7u); 
}

TEST_METHOD {
    u128 v = 007u; 
    bassert (v == 7u); 
}

TEST_METHOD {
    u128 v = 011u; 
    bassert (v != 11u); 
}