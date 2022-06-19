#include "def/matrix/linear_owned_matrix.hpp"
#include "algorithm/eigen.hpp"

Use matrix; 
Use matrix::algorithm;

TEST_METHOD {
    LinearOwnedMatrix<std::complex<int>> x(2,2); 
    Use std::literals; 
    x[0][0] = {0,2};
    x[0][1] = {1,0};
    x[1][0] = {1,1};
    x[1][1] = {2,0};
    auto y = eigenvalue(x);
    bassert_eq (y[0], -0.098684 + 1.455090i);
    bassert_eq (y[1], 2.098684 + 0.544910i);
    auto z = eigenvector(x);
    bassert_eq(z[0][0], -0.321797 + 1.776887i);
    bassert_eq(z[0][1], 0.321797 + 0.223113i);
    bassert_eq(z[1][0], 1);
    bassert_eq(z[1][1], 1);
}

TEST_METHOD {
    LinearOwnedMatrix<double> x(3,3); 
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
    bassert_eq(z[0][0], -0.5);
    bassert_eq(z[1][0], 1);
    bassert_eq(z[2][0], 1);
    
    bassert_eq(z[0][1], 1);
    bassert_eq(z[1][1], 1);
    bassert_eq(z[2][1], 0);

    bassert_eq(z[0][2], 1);
    bassert_eq(z[1][2], 0);
    bassert_eq(z[2][2], 1);
}

TEST_METHOD{
    LinearOwnedMatrix<int> x(5000,5000);
    for (int i = 0; i < 5000; ++i){
        for (int j = 0; j < 5000; ++j){
            x[i][j] = i+j;
        }
    }
    bassert_eq(x[1000][2000], 3000);
    bassert_eq(x[3456][3456], 3456+3456);
}

TEST_METHOD{
    LinearOwnedMatrix<int> x(3,3);
    x[0][0] = 1;
    x[0][1] = 2;
    x[0][2] = 3;
    x[1][0] = 4;
    x[1][1] = 5;
    x[1][2] = 6;
    x[2][0] = 7;
    x[2][1] = 8;
    x[2][2] = 9;
    bassert_eq(x.max(), 9);
    bassert_eq(x.min(), 1);
    bassert_eq(x.sum(), 45);
    bassert_eq(x.avg(), 5);
    bassert_eq(x.max(0,1,0,2), 6);
    bassert_eq(x.min(0,1,0,2), 1);
    bassert_eq(x.sum(0,1,0,2), 21);
    bassert_eq(x.avg(0,1,0,2), 3);
}

TEST_METHOD{
    LinearOwnedMatrix<int> x(3,3);
    x[0][0] = 1;
    x[0][1] = 2;
    x[0][2] = 3;
    x[1][0] = 4;
    x[1][1] = 5;
    x[1][2] = 6;
    x[2][0] = 7;
    x[2][1] = 8;
    x[2][2] = 9;
    auto y = slice(0,1,0,2);
    bassert_eq(y[0][0], 1);
    bassert_eq(y[0][1], 2);
    bassert_eq(y[0][2], 3);
    bassert_eq(y[1][0], 4);
    bassert_eq(y[1][1], 5);
    bassert_eq(y[1][2], 6);
}

TEST_METHOD{
    LinearOwnedMatrix<int> x(3,3);
    x[0][0] = 1;
    x[0][1] = 2;
    x[0][2] = 3;
    x[1][0] = 4;
    x[1][1] = 5;
    x[1][2] = 6;
    x[2][0] = 7;
    x[2][1] = 8;
    x[2][2] = 9;
    auto y = reshape(1,9);
    bassert_eq(y[0][0], 1);
    bassert_eq(y[0][1], 2);
    bassert_eq(y[0][2], 3);
    bassert_eq(y[0][3], 4);
    bassert_eq(y[0][4], 5);
    bassert_eq(y[0][5], 6);
    bassert_eq(y[0][6], 7);
    bassert_eq(y[0][7], 8);
    bassert_eq(y[0][8], 9);
}