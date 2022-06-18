#include "def/matrix/linear_owned_matrix.hpp"
#include "algorithm/eigen.hpp"

Use matrix; 
Use matrix::algorithm;

// TEST_METHOD {
//     LinearOwnedMatrix<std::complex<int>> x(2,2); 
//     Use std::literals; 
//     x[0][0] = {0,2};
//     x[0][1] = {1,0};
//     x[1][0] = {1,1};
//     x[1][1] = {2,0};
//     // auto y = eigenvalue(x);
//     // bassert_eq (y[0], 2.098684 + 0.544910i);
//     // bassert_eq (y[1], -0.098684 + 1.455090i);
//     auto z = eigenvector(x);
//     bassert_eq(z[0][0], 0.8593 + 0i);
//     bassert_eq(z[0][1], 0.3792 + 0.0816i);
//     bassert_eq(z[1][0], -0.2775 - 0.4297i);
//     bassert_eq(z[1][1], 0.9217 + 0i);
//     // bassert_eq(z[1][0], -0.2775 - 0.4297i);
//     // bassert_eq(z[1][1], 0.9217);
// }

TEST_METHOD {
    LinearOwnedMatrix<int> x(3,3); 
    Use std::literals; 
    x[0][0] = -1;
    x[0][1] = 2;
    x[0][2] = 2;
    x[1][0] = 2;
    x[1][1] = -1;
    x[1][2] = -2;
    x[2][0] = 2;
    x[2][1] = -2;
    x[2][2] = -1;
    auto y = eigenvalue(x);
    bassert_eq (y[0], -5);
    bassert_eq (y[1], 1);
    bassert_eq (y[2], 1);
    auto z = eigenvector(x);
    bassert_eq(z[0][0], 1);
    bassert_eq(z[1][0], 1);
    bassert_eq(z[2][0], 0);
    
    bassert_eq(z[0][1], 1);
    bassert_eq(z[1][1], 0);
    bassert_eq(z[2][1], 1);

    bassert_eq(z[0][2], 0);
    bassert_eq(z[1][2], 0);
    bassert_eq(z[2][2], 0);
}