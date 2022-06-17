#include "def/matrix/linear_owned_matrix.hpp"
#include "algorithm/gauss_elimination.hpp"

Use matrix; 
Use matrix::algorithm; 

TEST_METHOD {
    LinearOwnedMatrix<float> x(2, 2); 
    gauss_elimination(x); 
}