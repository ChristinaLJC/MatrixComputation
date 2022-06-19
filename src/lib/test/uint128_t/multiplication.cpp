#include "def/uint128_t.hpp"

Use matrix; 

TEST_METHOD {
    /** 
     * simple multiplication test, 3 times 7 is 21. 
     */ 
    u128 basic = 3u; 
    bassert_eq (basic * 7u, 21u); 
}

TEST_METHOD {
    /** 
     * 0 times anything would ends as 0. 
     */ 
    u128 zero = 0u; 
    bassert_eq (zero * 1000u, 0u); 
}

TEST_METHOD {
    /** 
     * 40! is out of the range of the u128. 
     */ 
    u128 base {1u}; 
    try {
        for (u32 k {1}; k <= 40; ++k) {
            base.template operator*= <true>(k); 
        }
        // You shouldn't calculate it correctly! 
        bassert(false); 
    } catch (exception::MatrixOverflowException const &) {
        bassert(true); 
    }
}

TEST_METHOD {
    /** 
     * Calculate the factorial of 30. 
     */ 
    u128 base {1u}; 
    try {
        for (u32 k {1}; k <= 30; ++k) {
            base *= k; 
        }
        bassert_eq (base, 265252859812191058636308480000000_u128); 
    } catch (exception::MatrixBaseException const &) {
        bassert (false); 
    }
}

TEST_METHOD {
    /** 
     * Calculate two simple uint64_t value multiplication, with the uint128_t at right hand side. 
     */ 
    auto v = 10477159787109540020ull * 1464069050530265433_u128; 
    bassert_eq (v, 15339285381767342174140209057136128660_u128);     
}

TEST_METHOD {
    /** 
     * Calculate the maximum of the uint64_t multiplication. 
     */ 
    auto v = 18446744073709551615ull * 18446744073709551615_u128; 
    bassert_eq (v, 340282366920938463426481119284349108225_u128); 
}