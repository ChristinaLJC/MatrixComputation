#include "def/matrix/sparse_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    SparseOwnedMatrix<int> m (3, 3); 
    bassert_eq (m[0][0], 0); 
}

TEST_METHOD {
    SparseOwnedMatrix<int> m (3, 3); 
    m[0][0] = 1; 
    bassert_eq (m[0][0], 1); 
}