#include "def/uint128_t.hpp"

Use matrix; 

TEST_METHOD {
    u128 basic = 21u; 
    auto result = basic - 21u; 
    bassert_eq (result, 0u); 
}

TEST_METHOD {
    u128 basic = 1u; 
    auto result = basic - 0u; 
    bassert_eq (result, 1u); 
}

TEST_METHOD {
    u128 basic; 
    auto result = basic - 0u; 
    bassert_eq (result, 0u); 
}

// Test the normal number subtraction. 
TEST_METHOD {
    u128 basic = 375809638u; 
    auto result = basic - 107374182u; 
    bassert_eq (result, 268435456u); 
}

// Test the large number subtraction. 
TEST_METHOD {
    u128 basic = 515968737826ull; 
    auto result = basic - 447249261090ull; 
    bassert_eq (result, 68719476736ull); 
}

// Overflow testing! 
TEST_METHOD {
    u128 basic; 
    basic -= 1u; 
    bassert_eq (basic, 0xffffffffffffffffffffffffffffffff_u128); 
}

// Test the complex calculations, subtract to zero then goes back. 
TEST_METHOD {
    u128 basic = 0xbaadfeed_u128; 
    basic -= 3131965165u; 
    basic += 3131965165u; 
    bassert_eq (basic, 0xbaadfeed_u128); 
}

// Test the inverse arithmetic operations. 
TEST_METHOD {
    u128 basic = 0xfeef_u128; 
    basic -= 0x10000u; 
    basic += 0x10000u; 
    bassert_eq (basic, 0xfeefu); 
}

// Subtract itself, and then jumps to zero. 
TEST_METHOD {
    u128 basic = 0x7f7f7f7fu; 
    basic -= basic; 
    bassert_eq (basic, 0u); 
}

// Subtract itself again and again. 
TEST_METHOD {
    u128 basic = 0x65535u; 
    basic -= basic -= basic; 
    bassert_eq (basic, 0u); 
}

// Test a more complex overflow situation. 
TEST_METHOD {
    u128 basic; 
    basic -= 170141183460469231731687303715884105728_u128; 
    bassert_eq (basic, 170141183460469231731687303715884105728_u128);
}