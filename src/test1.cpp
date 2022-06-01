TEST_METHOD {
    // do nothing. 
    bassert (true); 
}

TEST_METHOD {
    bassert (false); 
}

TEST_METHOD {
    bassert (1 + 1 == 2); 
}

TEST_METHOD {
    bassert (false && true); 
}

TEST_METHOD {
    bassert_eq (1 + 2 + 3, 10); 
}

TEST_METHOD {
    bassert_in (100, lower_bound(101));
}