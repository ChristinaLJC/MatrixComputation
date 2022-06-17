#include "def/matrix/linear_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    LinearOwnedMatrix<int> matrix (3, 3); 
    bassert_eq (matrix[0][0], 0); 
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
    // LinearOwnedMatrix<int> matrix 
    auto matrix = LinearOwnedMatrix<int>::with_identity_size(3); 
    bassert_eq (matrix[2][2], 1); 
}

TEST_METHOD {
    auto matrix = LinearOwnedMatrix<int>::with_identity_size(3); 
    auto m2 = matrix; 
    auto plus = matrix + m2; 
    bassert_eq (plus[1][1], 2); 
}

// TEST_METHOD {
//     auto t = LinearOwnedMatrix<int>::with_identity_size(4); 
//     auto t2 = LinearOwnedMatrix<int>::with_identity_size(3); 
//     auto plus = t + t2; 
//     bassert_eq (plus[0][0], 2); 
// }

// Convert operator between different matrixes. 

TEST_METHOD {
    auto matrix = LinearOwnedMatrix<int>::with_identity_size(2); 
    matrix[0][1] = -1; 
    matrix[1][0] = -1; 

    bassert_eq (matrix.size(), 4); 
    bassert_eq (matrix.sum(), 0); 
    bassert_eq (matrix.min(), -1); 
}

TEST_METHOD {
    auto matrix = LinearOwnedMatrix<int>::with_identity_size(3); 
    auto float_matrix = LinearOwnedMatrix<float>(matrix); 

    bassert_eq (float_matrix.row(), 3); 
    bassert_eq (float_matrix.col(), 3); 
    bassert_eq (float_matrix.size(), 9); 

    bassert_eq (float_matrix.sum(), 3.0); 
    bassert_eq (float_matrix[0][1], 0.); 
    bassert_eq (float_matrix[2][2], 1.0); 
}

TEST_METHOD {
    auto matrix = LinearOwnedMatrix<int>::with_identity_size (9); 
    auto matrix2 = LinearOwnedMatrix<double>::with_identity_size (8); 

    // matrix2 = matrix; 
    matrix = matrix2; 

    bassert_eq (matrix.size(), 64); 
    bassert_eq (matrix.sum(), 8); 
}