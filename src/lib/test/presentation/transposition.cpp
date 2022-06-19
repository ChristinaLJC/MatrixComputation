#include "def/matrix/linear_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    LinearOwnedMatrix<double> matrix (3, 3); 
    matrix[1][2] = 3.7;
    matrix[2][1] = 1.2;
    auto result = matrix.transposition();
    bassert_eq (result[1][2], 1.2);
    bassert_eq (result[2][1], 3.7);
}

TEST_METHOD {
    LinearOwnedMatrix<float> vector (3, 1); 
    vector[1][0] = 4.5;
    vector[2][0] = 5.7;
    auto result = vector.transposition();
    bassert_eq (result[0][1], 4.5);
    bassert_eq (result[0][2], 5.7);
}



