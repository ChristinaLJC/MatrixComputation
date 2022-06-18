#include "def/matrix/linear_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    auto matrix = LinearOwnedMatrix<int>(3, 4); 
    LinearOwnedMatrix<float> f = matrix; 
    bassert_eq (f.row(), 3); 
    bassert_eq (f.col(), 4); 
    bassert_eq (f.size(), 12); 
}