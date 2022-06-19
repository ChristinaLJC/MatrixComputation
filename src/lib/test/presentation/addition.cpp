#include "def/matrix/linear_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    auto matrix = LinearOwnedMatrix<int>::with_identity_size(3); 
    auto m2 = matrix; 
    auto plus = matrix + m2; 
    bassert_eq (plus[1][1], 2); 
}

TEST_METHOD {
    LinearOwnedMatrix<double> matrix1 (3, 3); 
    matrix1[1][2] = 4.5;
    matrix1[2][1] = 5.5;
    LinearOwnedMatrix<double> matrix2 (3, 3);
    matrix2[1][2] = 3.6;
    matrix2[2][1] = 4.5;
    auto result = matrix1 + matrix2;
    bassert_eq (result[1][2], 8.1);
    bassert_eq (result[2][1], 10);
}

TEST_METHOD {
    LinearOwnedMatrix<double> vector1 (3, 1); 
    vector1[1][0] = 4.5;
    vector1[2][0] = 5.5;
    LinearOwnedMatrix<double> vector2 (3, 1);
    vector2[1][0] = 3.6;
    vector2[2][0] = 4.5;
    auto result = vector1 + vector2;
    bassert_eq (result[1][0], 8.1);
    bassert_eq (result[2][0], 10.0);
}



