#include "def/matrix/linear_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    auto s = LinearOwnedMatrix<std::complex<int>>::with_identity_size(3); 
    bassert_eq (s.size(), 9); 
}

TEST_METHOD {
    auto s = LinearOwnedMatrix<std::complex<int>>::with_identity_size(3); 
    auto s2 = ~s; 
    bassert_eq (s, s2); 
}

TEST_METHOD {
    auto s = LinearOwnedMatrix<std::complex<int>>::with_identity_size(3); 
    Use std::literals; 
    s[0][1] = 1i; 
    
    auto s2 = ~s; 
    bassert_ne (s, s2); 
}