#include "def/matrix/linear_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    auto matrix = LinearOwnedMatrix<int>::with_identity_size(3); 
    auto m2 = matrix / 4;
    bassert_eq (m2[1][1], 0.25); 
}

TEST_METHOD {
    LinearOwnedMatrix<double> matrix (3, 3); 
    matrix[1][2] = 4.5;
    matrix[2][1] = 5.0;
    auto result = matrix / 5;
    bassert_eq (result[1][2], 0.9);
    bassert_eq (result[2][1], 1);
}

TEST_METHOD {
    LinearOwnedMatrix<float> vector (3, 1); 
    vector[1][0] = 45;
    vector[2][0] = 6.3;
    auto result = vector / 3;
    bassert_eq (result[1][0], 15);
    bassert_eq (result[2][0], 2.1);
}



