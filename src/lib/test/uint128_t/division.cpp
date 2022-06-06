#include "def/uint128_t.hpp"

/**  
 * The division operator tests of uint128_t type. 
 */ 
Use matrix; 

// Test the 0/0 situation. 
TEST_METHOD {
    u128 simple; 
    try {
        simple = simple / 0u; 
        bassert (false); 
    } catch (exception::MatrixZeroDividedException const &) {
        bassert (true); 
    }
}

// Test the 1/0 situation. Of course it won't get a result like infinity (We are not the floating point! )
TEST_METHOD {
    u128 simple = 1u; 
    try {
        simple = simple / 0u; 
        bassert (false); 
    } catch (exception::MatrixZeroDividedException const &) {
        bassert (true); 
    }
}

// Test the normal uint32_t division situation. 
TEST_METHOD {
    u128 simple = 3842362683u; 
    simple /= 723869815u; 
    bassert_eq (simple, 5u); 
}

TEST_METHOD {
    u128 simple = 3036075090u; 
    simple /= 28562u; 
    bassert_eq (simple, 106297u); 
}

TEST_METHOD {
    u128 simple = 2903686969u; 
    simple /= 1388u; 
    bassert_eq (simple, 2091993u); 
}

// Test the uint64_t division situation. 
TEST_METHOD {
    u128 simple = 3803750444866983160ull; 
    simple /= 1619100036517165913ull; 
    bassert_eq (simple, 2u); 
}

TEST_METHOD {
    u128 simple = 17663743046949793761ull; 
    simple /= 3501859577u; 
    bassert_eq (simple, 5044103756ull); 
}

TEST_METHOD {
    u128 simple = 629236015u; 
    simple /= 7463161731071348756ull; 
    bassert_eq (simple, 0u); 
}

TEST_METHOD {
    auto ans = 32u / 2_u128; 
    bassert_eq (ans, 16u); 
}

TEST_METHOD {
    auto ans = 14132301644367579006ull / 4044787813_u128; 
    bassert_eq (ans, 3493953774ull); 
}