#include "def/int128_t.hpp"

Use matrix; 

TEST_METHOD {
    i128 basic; 
    bassert (!basic);     
}

TEST_METHOD {
    i128 basic {2}; 
    bassert (basic); 
}

TEST_METHOD {
    i128 basic {65535}; 
    bassert_eq (basic, 65535); 
}

TEST_METHOD {
    i128 basic = 2147483647; 
    bassert_eq (basic, 2147483647); 
}

TEST_METHOD {
    i128 basic = 4294967295ll; 
    bassert_eq (basic, 4294967295ll); 
}

TEST_METHOD {
    i128 basic = 9223372036854775807ll; 
    bassert_eq (basic, 9223372036854775807ll); 
}

TEST_METHOD {
    i128 basic = 9223372036854775808_i128; 
    bassert (basic > 9223372036854775807ll); 
}

TEST_METHOD {
    i128 basic = 170141183460469231731687303715884105727_i128; 
    bassert_eq (basic.into<std::string>(), "170141183460469231731687303715884105727");  
}

TEST_METHOD {
    i128 basic = -170141183460469231731687303715884105727_i128; 
    bassert_eq (std::string(basic), "-170141183460469231731687303715884105727"); 
}

TEST_METHOD {
    i128 basic = 7; 
    basic = -basic; 
    basic = -basic; 
    bassert_eq (basic, 7); 
}