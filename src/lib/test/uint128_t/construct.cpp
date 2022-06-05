#include "def/uint128_t.hpp"

Use matrix; 

TEST_METHOD {
    u128 v; 
    bassert (!v); 
} 

TEST_METHOD {
    u128 s(1u); 
    bassert (s); 
}

TEST_METHOD {
    u128 k;
    u128 k2 = k; 
    bassert (!k); 
    bassert (!k2); 
}

TEST_METHOD {
    u128 v (1ull); 
    bassert (v); 
}