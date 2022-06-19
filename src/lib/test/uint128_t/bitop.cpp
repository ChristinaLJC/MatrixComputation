#include "def/uint128_t.hpp"

Use matrix; 

/** 
 * Of course, in expection we do not think it may cause an exception of this part. 
 *   It's so easy to realize, and we do not have a further complex situation. 
 *   But the test is necessary, for the better optimization in the future. 
 */ 

// Simple 'or' op test. 
TEST_METHOD {
    u128 b1 = 0b1u; 
    u128 b2 = 0b10u; 
    bassert_eq (b1 | b2, 0b11u); 
}

TEST_METHOD {
    u128 seven = 0b111u; 
    u128 eight = 0b1000u; 
    bassert_eq (seven | eight, 0b1111u); 
}

TEST_METHOD {
    u128 special = 0b1'000_u128; 
    u128 special2 = 0u | special; 
    bassert_eq (special2, special); 
}
