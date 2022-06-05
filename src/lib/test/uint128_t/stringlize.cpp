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

TEST_METHOD {
    u128 simple = 21u; 
    bassert_eq(std::string(simple), "21"); 
}

TEST_METHOD {
    u128 simple = 21u; 
    bassert_eq ("{}"_format(simple), "21"); 
}

TEST_METHOD {
    u128 a = 392u; 
    bassert_eq (a.into<std::string>(), "392"); 
}

TEST_METHOD {
    u128 a = 66535u ;
    bassert_eq (type_traits::Into<std::string>{}.into(a), "66535"); 
}

TEST_METHOD {
    bassert_eq ("{}"_format(u128(1111111u)), "1111111"); 
}