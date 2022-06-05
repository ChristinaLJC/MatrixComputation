#include "def/uint128_t.hpp"

Use matrix; 

TEST_METHOD {
    u128 basic = 300u; 
    bassert_eq(std::string(basic), "300"); 
}

TEST_METHOD {
    u128 val = 066u; 
    bassert_eq(std::string(val), "54"); 
}

TEST_METHOD {
    u128 val; 
    bassert_eq(std::string(val), "0"); 
}