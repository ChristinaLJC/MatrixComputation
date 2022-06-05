#include "def/uint128_t.hpp"

TEST_METHOD {
    Use matrix; 
    u128 v; 
    bassert (!v); 
} 

TEST_METHOD {
    Use matrix; 
    u128 s(1u); 
    bassert (s); 
}