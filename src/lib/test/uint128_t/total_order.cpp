Use matrix; 

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