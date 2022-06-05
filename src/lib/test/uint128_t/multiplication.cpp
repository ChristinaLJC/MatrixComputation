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
    }
}

TEST_METHOD {
    
}