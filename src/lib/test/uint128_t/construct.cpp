#include "def/uint128_t.hpp"

Use matrix; 

// Check the basic empty-parameter constructor. 
TEST_METHOD {
    u128 v; 
    bassert (!v); 
} 

// Check the simple uint32_t constructor. 
TEST_METHOD {
    u128 s(1u); 
    bassert (s); 
}

// Check the simple uint64_t constructor. 
TEST_METHOD {
    u128 v {(u64)65535}; 
    bassert_eq (v, 65535u); 
}

// Check the a little complex uint64_t constructor. 
TEST_METHOD {
    u128 v {137438953440ull}; 
    bassert_ne (v, 68719476720ull); 
    bassert_eq (v, 137438953440ull); 
}

// Check the copy constructor basically. 
TEST_METHOD {
    u128 v; 
    u128 v2 = v; 
    bassert (!v2); 
    bassert_eq (v, v2); 
}

// Check the normal number copy constructor. 
TEST_METHOD {
    u128 v = 1u; 
    u128 v2 = v; 
    bassert (v2); 
    bassert_eq (v, v2); 
}

// Check the complex number copy constructor. 
TEST_METHOD {
    u128 v = 431953908621ull; 
    u128 v2 = v; 
    bassert_eq (v2, 431953908621ull); 
}

TEST_METHOD {
    
}