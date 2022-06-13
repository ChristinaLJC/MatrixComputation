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