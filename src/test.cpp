#include "Matrix.hpp" 

TEST_METHOD {
    auto x = 3; 
    auto y = 5; 
    bassert(x + y == 8, "x + y != 8 when invoke {x = 3, y = 5}. ");
}

TEST_METHOD {
    int result {}; 
    for (int i = 0; i < 100; ++i) {
        result += i; 
    }
    bassert (result == 4950, "0 + 1 + ... + 98 + 99 != 4950. "); 
}

TEST_METHOD {
    float f = 1. / 3; 
    bassert (f * 3 == 1, "0.33... * 3 != 1");
}

TEST_METHOD {
    bassert (1 == 2, "1 != 2");
}

TEST_METHOD {
    constexpr auto is_prime = [](auto i) {
        for (decltype(i) it = 2; it < i; ++it) {
            if (i % it == 0)
                return false; 
            if (it * it > i)
                break; 
        }
        return true; 
    };
    bassert (is_prime(2), "2 isn't a prime. ");
    bassert (is_prime(7), "7 isn't a prime. "); 
    bassert (!is_prime(42), "42 is a prime. "); 
    bassert (is_prime(1201), "1201 is not a prime. ");
    bassert (!is_prime(1919), "1919 is a prime. "); 
    bassert (!is_prime(-6), "-6 is a prime. ");
}

TEST_METHOD {
    using namespace Matrix; 
    auto x = std::vector{7, 6, 4, 6, 7}; 
    auto y = std::vector{1, 2, 5, 2, 1}; 
    auto &&together = add(x, y); 
    bassert (together == std::vector{8, 8, 9, 8, 8}, "together is not {8, 8, 9, 8, 8}. ");
}

TEST_METHOD {
    using namespace Matrix; 
}