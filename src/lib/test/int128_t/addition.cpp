#include "def/int128_t.hpp"

Use matrix; 

TEST_METHOD {
    // Add the basic addition with zero. 
    i128 base; 
    i128 base2; 
    i128 result = base + base2; 
    // Of course, now the result is zero absolutely. 
    bassert (!result); 
}

TEST_METHOD {
    // one plus one is two! 
    i128 base = 1; 
    i128 base2 = 1; 
    i128 result = base + base2; 
    bassert_eq ((std::string)result, "2"); 
}

TEST_METHOD {
    i128 base = 9; 
    i128 result = base + base; 
    bassert_eq ((std::string)result, "18"); 
}

TEST_METHOD {
    // More complex addition, self addition! 
    i128 base = 7; 
    base += base; 
    bassert_eq ((std::string)base, "14"); 
}

TEST_METHOD {
    i128 base = 4294967295ll; 
    base += base; 
    bassert_eq ((std::string)base, "8589934590"); 
}

TEST_METHOD {
    i128 base = 9223372036854775807ll; 
    base += base; 
    bassert_eq ((std::string)base, "18446744073709551614"); 
}

TEST_METHOD {
    i128 base = 170141183460469231731687303715884105727_i128; 
    // Overflow happens. 
    base += base; 
    bassert_eq ((std::string)base, "-2"); 
}

TEST_METHOD {
    i128 base = 170141183460469231731687303715884105727_i128; 
    try {
        // base += base; 
        base .template operator+= <true> (base); 
        bassert_eq ((std::string)base, "340282366920938463463374607431768211454"); 
    } catch (exception::MatrixArithmeticException const &) {
        bassert_eq ((std::string)base, "170141183460469231731687303715884105727"); 
    }
}

// The normal negative number addition tests. 
TEST_METHOD {
    i128 negative_one = -1; 
    negative_one += negative_one; 
    bassert_eq (negative_one, -2); 
}

TEST_METHOD {
    i128 basic = -4294967295ll; 
    basic += basic; 
    bassert_eq (basic, -8589934590ll); 
}

TEST_METHOD {
    i128 basic = -1267650600228229401496703205375_i128; 
    basic += 1267650600228229401496703205375_i128; 
    bassert (!basic); 
}

TEST_METHOD {
    i128 basic = -83076749736557242056487941267521535_i128; 
    basic += -83076749736557242056487941267521535_i128; 
    bassert_eq (basic, -166153499473114484112975882535043070_i128); 
}

TEST_METHOD {
    i128 basic = -21267647932558653966460912964485513215_i128; 
    basic = basic - 21267647932558653966460912964485513215_i128; 
    bassert_eq ((std::string)basic, "-42535295865117307932921825928971026430"); 
}

TEST_METHOD {
    // i128 basic = 170141183460469231731687303715884105728_i128; 
    
    // The maximum value of int128_t. 
    i128 basic = 170141183460469231731687303715884105727_i128; 
    try {
        basic.template operator++ <true>(); 
        bassert(false); 
    } catch (exception::MatrixArithmeticException const &) {
        bassert_eq ((std::string)basic, "170141183460469231731687303715884105727"); 
    }
}

TEST_METHOD {
    i128 basic = 170141183460469231731687303715884105727_i128; 
    try {
        // basic += basic; 
        basic .template operator+= <true> (basic); 
        bassert (false); 
    } catch (exception::MatrixArithmeticException const &) {
        bassert_eq (std::string(basic), "170141183460469231731687303715884105727");  
    }
}

TEST_METHOD {
    i128 basic = 170141183460469231731687303715884105727_i128; 
    try {
        basic .template operator+= <true> (-basic); 
        bassert_eq (basic, 0); 
    } catch (exception::MatrixArithmeticException const &) {
        bassert (false); 
    }
}