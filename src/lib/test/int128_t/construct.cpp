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
    // i128 basic = 9223372036854775808ll; 
    // bassert_eq (basic, 0); 
}