Use matrix; 

TEST_METHOD {
    u128 v = 2u; 
    u128 v2 = 3u; 
    bassert (v != v2); 
}

TEST_METHOD {
    u128 v = 7u; 
    bassert (v == 7u); 
}

TEST_METHOD {
    u128 v = 007u; 
    bassert (v == 7u); 
}

TEST_METHOD {
    u128 v = 011u; 
    bassert (v != 11u); 
}

TEST_METHOD {
    bassert (u128(99999u) == 99999u); 
}

TEST_METHOD {
    u128 less; 
    bassert (less < 1u); 
}

TEST_METHOD {
    u128 great_eq; 
    bassert (great_eq >= 0u); 
}

TEST_METHOD {
    u128 great; 
    for (u32 i{}; i < 100; ++i) 
        great += i; 
    bassert (great > 4949u); 
}

TEST_METHOD {
    u128 less; 
    for (u32 i{}; i < 100; i += 2) {
        less += i; 
    }
    bassert (less < 2451u); 
}