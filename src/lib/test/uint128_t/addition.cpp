#include "def/uint128_t.hpp"

Use matrix; 

// Do a simple addition test. 
TEST_METHOD {
    u128 lhs = 0u; 
    u128 rhs = 0u; 
    auto res = lhs + rhs; 
    bassert_eq (res, 0u); 
}

// Test the left handside addition: 
TEST_METHOD {
    u128 simple; 
    auto result = simple + 1u; 
    bassert_eq (result, 1u); 
}

// Add some difficulty: addition with a quite large value. 
TEST_METHOD {
    u128 simple; 
    auto result = simple + 8589934591ull; 
    bassert_eq (result, 8589934591ull);  
}

// Attempt to add as a rhs value. 
TEST_METHOD {
    u128 simple; 
    auto result = 2u + simple; 
    bassert_eq (result, 2u);  
}

// Add a big number in left handside. 
TEST_METHOD {
    u128 simple; 
    auto result = 12312239581ull + simple; 
    bassert_eq (result, 12312239581ull); 
}

// Prefix autoincrement. 
TEST_METHOD {
    u128 v = 41u; 
    ++v; 
    bassert_eq (v, 42u); 
}

// Prefix autoincrement in complex situation. 
TEST_METHOD {
    u128 v = 10524622862698ull; 
    ++v; 
    bassert_eq (v, 10524622862699ull); 
}

// Addition and then eq simple test. 
TEST_METHOD {
    u128 v; 
    v += 0u; 
    bassert_eq (v, 0u); 
}

// Addition and then eq with a small number. 
TEST_METHOD {
    u128 v; 
    v += 2u; 
    bassert_eq (v, 2u); 
}

// Add and then eq with a large value. 
TEST_METHOD {
    u128 v; 
    v += 8209686820727ull; 
    bassert_eq (v, 8209686820727ull); 
}

// Use a for-loop to add more numbers. 
// This value is calculated by python, actually. 
TEST_METHOD {
    u128 v; 
    auto numbers = {
        18764998447377ull, 
        18764998447377ull, 
        18764998447377ull, 
        18764998447377ull, 
        18764998447377ull, 
        18764998447377ull, 
    }; 
    for (auto k: numbers) 
        v += k; 
    bassert_eq (v, 112589990684262ull); 
}

// Attempt to add a more large value! 
TEST_METHOD {
    u128 v = 18446744073709551615ull; 
    v += 18446744073709551615ull; 
    bassert_eq (v, 36893488147419103230_u128); 
}