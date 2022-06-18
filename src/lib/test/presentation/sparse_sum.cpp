#include "def/matrix/sparse_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    SparseOwnedMatrix<int> m (5000, 5000);
    m[4][5] = 7;
    m[5][0] = 5;
    bassert_eq(m.sum(), 12);
}