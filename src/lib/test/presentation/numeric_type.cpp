#include "def/matrix/linear_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    LinearOwnedMatrix<int> matrix (3, 3); 
    matrix[2][1] = 5;
    bassert_eq (matrix[2][1], 5);
    bassert_eq (matrix[1][2], 0); 

}

TEST_METHOD {
    LinearOwnedMatrix<float> matrix (2, 3); 
    bassert_eq (matrix.col(), 3); 
}

TEST_METHOD {
    LinearOwnedMatrix<short> matrix (4, 1); 
    bassert_eq (matrix.row(), 4); 
}

TEST_METHOD {
    LinearOwnedMatrix<char> matrix (5, 6); 
    bassert_eq (matrix.size(), 30); 
}

TEST_METHOD {
    auto matrix = LinearOwnedMatrix<int>::with_identity_size(3); 
    auto float_matrix = LinearOwnedMatrix<float>(matrix); 

    bassert_eq (float_matrix.row(), 3); 
    bassert_eq (float_matrix.col(), 3); 
    bassert_eq (float_matrix.size(), 9); 

    bassert_eq (float_matrix[0][1], 0.); 
    bassert_eq (float_matrix[2][2], 1.0); 
}
