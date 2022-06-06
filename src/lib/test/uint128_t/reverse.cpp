#include "def/uint128_t.hpp"

/** 
 * This is the reverse operations testing benches. 
 */ 

Use matrix; 

// Test the zero reverse bits operation. 
TEST_METHOD {
    u128 x = 0u; 
    x = ~x; 
    ++x; 
    bassert_eq(x, 0u); 
}

// Test the normal uint32_t value reverse situation. 
TEST_METHOD {
    u128 x = 77u; 
    x += ~x; 
    ++x; 
    bassert_eq(x, 0u); 
}

// Test the uint64_t value reverse. 
TEST_METHOD {
    u128 x = 4515905963825004072ull; 
    x += ~x; 
    ++x; 
    bassert_eq (x, 0u); 
}

// Test the uint128_t itself reverse. 
TEST_METHOD {
    u128 x = 21518075645647519188452225399249248381_u128; 
    x += ~x; 
    ++x; 
    bassert_eq (x, 0u); 
}