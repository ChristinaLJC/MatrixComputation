#include "def/matrix/linear_owned_matrix.hpp"

Use matrix; 

TEST_METHOD {
    LinearOwnedMatrix<int> x(2,2); 
    x[0][0] = 1;
    x[0][1] = 2;
    x[1][0] = -1;
    x[1][1] = -3;
    auto y = x.element_wise_product(x);
    bassert_eq(y[0][0], 1);
    bassert_eq(y[0][1], 4);
    bassert_eq(y[1][0], 1);
    bassert_eq(y[1][1], 9);
}

TEST_METHOD {
    LinearOwnedMatrix<double> x(2,3); 
    x[0][0] = 1.3;
    x[0][1] = 4.4;
    x[0][2] = 5.3;
    x[1][0] = -1.5;
    x[1][1] = -3.3;
    x[1][2] = 6.3;
    LinearOwnedMatrix<double> y(3,2); 
    y[0][0] = 1.3;
    y[0][1] = 4.4;
    y[1][0] = 5.3;
    y[1][1] = -1.5;
    y[2][0] = -3.3;
    y[2][1] = 6.3;
    auto z = x * y;
    bassert_eq(z.size(), 4);
    static_assert (std::is_same_v<std::decay_t<decltype(z[0][0])>, double>); 
    bassert_eq(z[0][0], 7.52);
    bassert_eq(z[0][1], 32.51);
    bassert_eq(z[1][0], -40.23);
    bassert_eq(z[1][1], 38.04);
}

TEST_METHOD {
    LinearOwnedMatrix<int> x(2,2); 
    x[0][0] = 1;
    x[0][1] = 2;
    x[1][0] = -1;
    x[1][1] = -3;
    bassert_eq (x.determinant(), -1);
}

TEST_METHOD {
    LinearOwnedMatrix<int> x(2,2); 
    x[0][0] = 1;
    x[0][1] = 2;
    x[1][0] = -1;
    x[1][1] = -3;
    auto ans = x.inverse();
    
    bassert_eq (ans[0][0], 3); 
    bassert_eq (ans[0][1], 2); 
    bassert_eq (ans[1][0], -1); 
    bassert_eq (ans[1][1], -1); 
}

TEST_METHOD {
    LinearOwnedMatrix<int> x(2,2); 
    x[0][0] = 1;
    x[0][1] = 2;
    x[1][0] = -1;
    x[1][1] = -3;
    bassert_eq (x.trace(), -2);
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
    auto y = x.cross_product(x);
    bassert_eq(y[0][0], 30);
    bassert_eq(y[0][1], 36);
    bassert_eq(y[0][2], 42);
    bassert_eq(y[1][0], 66);
    bassert_eq(y[1][1], 81);
    bassert_eq(y[1][2], 96);
    bassert_eq(y[2][0], 102);
    bassert_eq(y[2][1], 126);
    bassert_eq(y[2][2], 150);
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
    auto y = x.convolution(x);
    bassert_eq(y[0][0], 1);
    bassert_eq(y[0][1], 4);
    bassert_eq(y[0][2], 10);
    bassert_eq(y[0][3], 12);
    bassert_eq(y[0][4], 9);
    bassert_eq(y[1][0], 8);
    bassert_eq(y[1][1], 26);
    bassert_eq(y[1][2], 56);
    bassert_eq(y[1][3], 54);
    bassert_eq(y[1][4], 36);
    bassert_eq(y[2][0], 30);
    bassert_eq(y[2][1], 84);
    bassert_eq(y[2][2], 165);
    bassert_eq(y[2][3], 144);
}

TEST_METHOD {
    LinearOwnedMatrix<int> x(2,2); 
    x[0][0] = 1;
    x[0][1] = 2;
    x[1][0] = -1;
    x[1][1] = -3;
    auto y = x.element_wise_product(x);
    bassert_eq(y[0][0], 1);
    bassert_eq(y[0][1], 4);
    bassert_eq(y[1][0], 1);
    bassert_eq(y[1][1], 9);
}

TEST_METHOD {
    LinearOwnedMatrix<int> x(2,2); 
    x[0][0] = 1;
    x[0][1] = 2;
    x[1][0] = -1;
    x[1][1] = -3;
    auto y = x.dot_product(x);
    bassert_eq(y[0][0], 2);
    bassert_eq(y[0][1], 13);
}

TEST_METHOD {
    LinearOwnedMatrix<int> x(1,3); 
    x[0][0] = 1;
    x[0][1] = 2;
    x[0][2] = -4;
    auto y = x.dot_product(x);
    bassert_eq(y[0][0], 1);
    bassert_eq(y[0][1], 4);
    bassert_eq(y[0][2], 16);
}



