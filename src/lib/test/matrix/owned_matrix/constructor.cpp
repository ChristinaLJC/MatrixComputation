#include "def/matrix/owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    OwnedMatrix<int> simple(3, 3);  
    bassert_eq (simple.row(), 3); 
}

TEST_METHOD {
    OwnedMatrix<double> simple (4, 5); 
    bassert_eq (simple.col(), 5); 
}

TEST_METHOD {
    OwnedMatrix<float> simple (2, 1); 
    auto simple2 = simple; 
    auto result = simple + simple2; 
    // bassert_eq (result[0][0], 0.f); 
    // auto k = result[0][0]; 
    // auto k = result[1]; 
    // auto k2 = 
}