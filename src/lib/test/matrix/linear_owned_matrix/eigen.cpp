#include "def/matrix/linear_owned_matrix.hpp"
#include "algorithm/eigen.hpp"

Use matrix; 

TEST_METHOD {
    LinearOwnedMatrix<std::complex<float>> x (2, 2); 
    // x.trace(); 
    auto e = matrix::algorithm::eigenvalue(x); 
}