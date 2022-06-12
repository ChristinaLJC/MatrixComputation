#include "Matrix.h"
#include "Matrix.cpp"

using namespace std;
using namespace mat;

const double eps = 1e-7;

int main() {
    int* data1 = new int[10]{1, 2, -1, 3, 4, -2, 5, -4, 1, 15};
    int* data2 = new int[4]{89, 2, 10, 15};
    Matrix<int> t1(2, 5, data1);
    Matrix<int> t2(2, 2, data2);
    cout << t1;
    cout << t2;
    cout << mat_conv(t1, t2);
    Matrix<double> t3(3,3,10);
    cout << t3;
    t3.reshape(2,2);
    cout << t3;
    cout << t3*t2;
    double* data3 = new double[4]{1,1,1,6};
    Matrix<double>t4(2,2,data3);
    cout << t4;
    cout << mat_det(t4) << endl;
    cout << mat_inv(t4, eps);
    double* data4 = new double[9]{1, 2, 1, 3, 4, 2, 5, 4, 1};
    Matrix<double> t5(3, 3, data4);
    cout << t1;
    cout << mat_eig_val(t5, 0.00001, 1.0) << endl;
    cout << mat_eig_vec(t5, 0.00001, 1.0);


    complex<double>* data5 = new complex<double>[9]{{1}, {2}, {-1}, {3}, {4}, {5}, {-4}, {1}, {0,5}};
    complex<double>* data6 = new complex<double>[4]{{8}, {2,-1}, {1,5}, {3,1}};
    Matrix<complex<double>> t6(3, 3, data5);
    Matrix<complex<double>> t7(2, 2, data6);
    cout << t6;
    cout << mat_eig_val(t7, {0.00001,0.00001}, {1.0,0}) << endl;
    cout << mat_eig_vec(t7, {0.00001,0.00001}, {1.0,0});
    cout << t7;
    cout << mat_conv(t6, t7);

}
