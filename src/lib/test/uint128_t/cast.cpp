#include "def/uint128_t.hpp"

Use matrix; 

/** 
 * This test is testing the secure cast from uint128_t to uint32_t. 
 * 
 * When it fails, it would throw an exception BadCastException. 
 */ 
TEST_METHOD {
    auto t = 7158278826_u128; 
    try {
        (void)(u32)t; 
        // Cannot cast it as a 32-bit value safely. 
        bassert (false); 
    } catch (exception::MatrixBaseException const &e) {
        bassert_eq (typeid(e), typeid(exception::MatrixBadCastException)); 
    }
}

/** 
 * Simple test to cast a normal number safely. 
 */ 
TEST_METHOD {
    u32 simple_number = 970534638u;
    u128 simple = simple_number; 
    try {
        simple_number = simple; 
        bassert (true); 
    } catch (exception::MatrixBaseException const &) {
        // It won't activate an exception. 
        bassert (false); 
    }
}

/** 
 * Test a large enough number. 
 */ 
TEST_METHOD {
    u64 s = 6149085634720987965ull; 
    u128 l = s; 
    try {
        s = l; 
        bassert (true); 
    } catch (exception::MatrixBaseException const &) {
        // Why you want to throw an exception now? 
        bassert (false); 
    }
}

/** 
 * Test a quite large number, so it possibly throw an exception emmm.... 
 */ 
TEST_METHOD {
    // Obviously, this number is a little larger than ... u64::maximum. 
    u128 s = 18446744073709551616_u128; 
    bassert (s > std::numeric_limits<u64>::max()); 
    try {
        (void)(u64)s; 
        bassert (false); 
    } catch (exception::MatrixBaseException const &e) {
        bassert_eq (typeid(e), typeid(exception::MatrixBadCastException)); 
    }
}