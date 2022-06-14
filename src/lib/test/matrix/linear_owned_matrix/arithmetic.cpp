#include "def/matrix/linear_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    LinearOwnedMatrix<int> base (2, 3); 
    base[0][1] = 7; 
    auto r = base.transposition(); 
    bassert_eq(r[1][0], 7); 
}

TEST_METHOD {
    LinearOwnedMatrix<int> base (2, 3); 
    bassert_eq (base.row(), 2); 

    auto r = base.transposition(); 
    bassert_eq (r.row(), 3); 
}