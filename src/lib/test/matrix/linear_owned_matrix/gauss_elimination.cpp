#include "def/matrix/linear_owned_matrix.hpp"
#include "algorithm/eigen.hpp"
// #include "algorithm/gauss_elimination.hpp"

Use matrix; 
Use matrix::algorithm; 

TEST_METHOD {
    LinearOwnedMatrix<float> x(2, 2); 
    x[0][0] = 1.; 
    x[1][1] = 1.; 
    auto m = gaussian_elimination_as_mut(x); 
    bassert_eq (m, 2); 
}