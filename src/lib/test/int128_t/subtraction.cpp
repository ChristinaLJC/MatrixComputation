#include "def/int128_t.hpp"

Use matrix; 

TEST_METHOD {
    i128 t = 1; 
    i128 ans = t - 2; 
    bassert_eq (ans, -1); 
}

TEST_METHOD {
    i128 t = 66666; 
    i128 ans = t - t; 
    bassert (!ans); 
}

TEST_METHOD {
}