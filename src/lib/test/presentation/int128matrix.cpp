#include "def/int128_t.hpp"

Use matrix; 

TEST_METHOD{
    LinearOwnedMatrix<i128> x(3,3);
    x[0][2] = 4294967295ll;
    bassert_eq(x[0][0], 0);
    bassert_eq(x[0][2], 4294967295ll);
}