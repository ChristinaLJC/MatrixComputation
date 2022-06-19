#include "def/matrix/owned_matrix.hpp"
#include "algorithm/eigen.hpp"

Use matrix; 

TEST_METHOD {
    OwnedMatrix<int> simple(3, 3);  
    simple[0][0] = 1;
    simple[1][1] = 2;
    simple[2][2] = 3;
    
    bassert_eq (simple.row(), 4); 
}