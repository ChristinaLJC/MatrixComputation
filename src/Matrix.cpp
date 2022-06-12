
#include "Matrix.h"

namespace mat {

    template<typename T>
    Matrix<T>::Matrix() {

    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix& matrix) {
        init(matrix.row, matrix.col);
        memcpy(data, matrix.data, tot * sizeof(T));
    }

    template<typename T>
    Matrix<T>::Matrix(size_t r, size_t c, T* d) {
        init(r, c);
        memcpy(data, d, tot * sizeof(T));
    }

    template<typename T>
    Matrix<T>::Matrix(size_t r, size_t c, T d) {
        init(r, c);
        for (size_t i = 0; i < tot; ++i) {
            data[i] = d;
        }
    }

    template<typename T>
    Matrix<T>::Matrix(size_t r, size_t c) {
        init(r, c);
    }

    template<typename T>
    void Matrix<T>::init(size_t r, size_t c) {
        row = r;
        col = c;
        tot = row * col;
        data = new T[row * col]();
        pdata = new T* [row];

        T* pointer = data;
        for (size_t i = 0; i < row; ++i) {
            pdata[i] = pointer;
            pointer += col;
        }
    }

    template<typename T>
    Matrix<T>::~Matrix() {
        remove();
    }

    template<typename T>
    Matrix <T>& Matrix<T>::operator=(const Matrix <T>& matrix) {
        if (data == matrix.data) return *this;
        if (row != matrix.row || col != matrix.col) {
            reshape(matrix.row, matrix.col);
        }
        memcpy(data, matrix.data, tot * sizeof(T));
        return *this;
    }

    template<typename T>
    T* Matrix<T>::operator[](size_t r) {
        assert(r < row);
        return pdata[r];
    }

    template<typename T>
    const T* Matrix<T>::operator[](size_t r) const {
        assert(r < row);
        return pdata[r];
    }

    template<typename T>
    size_t Matrix<T>::rows() const {
        return row;
    }

    template<typename T>
    size_t Matrix<T>::cols() const {
        return col;
    }

    template<typename T>
    size_t Matrix<T>::tots() const {
        return tot;
    }

    template<typename T>
    Matrix <T>& Matrix<T>::operator+=(const Matrix <T>& rhs) {
        assert(row == rhs.row);
        assert(col == rhs.col);
        assert(data != NULL);
        assert(rhs.data != NULL);
        for (size_t i = 0; i < tot; ++i) {
            data[i] += rhs.data[i];
        }
        return *this;
    }

    template<typename T>
    Matrix <T>& Matrix<T>::reshape(size_t r, size_t c) {
        if (row == r && col == c) return *this;
        assert(data != NULL);
        T* ndata = new T[r * c]();
        memcpy(ndata, data, (tot < r * c ? tot : r * c) * sizeof(T));
        delete[] pdata;
        delete[] data;
        init(r, c);
        memcpy(data, ndata, tot * sizeof(T));
        delete[] ndata;
        return *this;
    }

    template<typename T>
    void Matrix<T>::remove() {
        delete[] data;
        delete[] pdata;
    }

    template<typename T>
    Matrix <T> mat_transpose(const Matrix <T>& matrix) {
//        assert(matrix.data != NULL);
        size_t row = matrix.cols();
        size_t col = matrix.rows();
        Matrix<T> res(row, col);
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                res[i][j] = matrix[j][i];
            }
        }
        return res;
    }

    template<typename T>
    Matrix <T> mat_conjugate(const Matrix <T>& matrix) {
//        assert(matrix.data != NULL);
        Matrix<T> res(matrix.rows(), matrix.cols());
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                res[i][j] = conj(matrix[i][j]);
            }
        }
        return res;
    }

    template<typename T>
    Matrix <T> mat_ele_mul(const Matrix <T>& lhs, const Matrix <T>& rhs) {
        assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols());
        Matrix<T> res(lhs.rows(), lhs.cols());
        for (size_t i = 0; i < lhs.rows(); ++i) {
            for (size_t j = 0; j < lhs.cols(); ++j) {
                res[i][j] = lhs[i][j] * rhs[i][j];
            }
        }
        return res;
    }

    template<typename T>
    Matrix <T> mat_dot(const Matrix <T>& lhs, const Matrix <T>& rhs) {
        assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols());
        Matrix<T> res(1, lhs.cols());
        for (size_t i = 0; i < lhs.cols(); ++i) {
            for (size_t j = 0; j < lhs.rows(); ++j) {
                res[0][i] += lhs[j][i] * rhs[j][i];
            }
        }
        return res;
    }

    template<typename T>
    Matrix <T> mat_cross(const Matrix <T>& lhs, const Matrix <T>& rhs) {
        return lhs * rhs;
    }

    template<typename T1, typename T2>
    Matrix <T1> operator*(const Matrix <T1>& lhs, const Matrix <T2>& rhs) {
        assert(lhs.cols() == rhs.rows());
        size_t row = lhs.rows(), col = rhs.cols(), t = lhs.cols();
        Matrix<T1> res(row, col);
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                for (size_t k = 0; k < t; ++k) {
                    res[i][j] += (lhs[i][k] * rhs[k][j]);
                }
            }
        }
        return res;
    }

    template<typename T>
    T mat_min(const Matrix <T>& matrix) {
        T min = matrix[0][0];
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                if (min > matrix[i][j])
                    min = matrix[i][j];
            }
        }
        return min;
    }

    template<typename T>
    T mat_max(const Matrix <T>& matrix) {
        T max = matrix[0][0];
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                if (max < matrix[i][j])
                    max = matrix[i][j];
            }
        }
        return max;
    }

    template<typename T>
    T mat_sum(const Matrix <T>& matrix) {
        T sum{};
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                sum += matrix[i][j];
            }
        }
        return sum;
    }

    template<typename T>
    T mat_avg(const Matrix <T>& matrix) {
        T sum{};
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                sum += matrix[i][j];
            }
        }
        return sum / matrix.tots();
    }

    template<typename T>
    Matrix <T> mat_slice(const Matrix <T>& matrix, size_t row1, size_t row2, size_t col1, size_t col2) {
        size_t row = row2 - row1 + 1, col = col2 - col1 + 1;
        Matrix<T> res(row, col);
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                res[i][j] = matrix[row1 + i][col1 + j];
            }
        }
        return res;
    }

    template<typename T>
    Matrix <T> mat_det_cut(const Matrix <T>& matrix, size_t n, size_t i) {
        Matrix<T> temp(matrix);
        for (size_t c = 0; c < n; ++c) {
            for (size_t r = 0; r < n; ++r) {
                temp[c][r] = matrix[c + 1][r + (r >= i)];
            }
        }
        return temp;
    }

    template<typename T>
    T mat_det_cal(const Matrix <T>& matrix, size_t n) {
        assert(matrix.rows() == matrix.cols());
        if (n == 1)
            return matrix[0][0];
        T ans{};
        for (size_t i = 0; i < n; ++i) {
            ans += matrix[0][i] * mat_det_cal(mat_det_cut(matrix, n - 1, i), n - 1) * (i % 2 ? -1 : 1);
        }
        return ans;
    }

    template<typename T>
    T mat_det(const Matrix <T>& matrix) {
        Matrix<T> temp(matrix);
        return mat_det_cal(temp, matrix.cols());
    }

    template<typename T>
    Matrix <T> mat_adj(const Matrix <T>& matrix, size_t n) {
        Matrix<T> ans(n, n);
        if (n == 1) {
            ans[0][0] = 1;
        } else {
            Matrix<T> temp(n - 1, n - 1);
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    for (size_t k = 0; k < n - 1; ++k) {
                        for (size_t t = 0; t < n - 1; ++t) {
                            temp[k][t] = matrix[k >= i ? k + 1 : k][t >= j ? t + 1 : t];
                        }
                    }
                    ans[j][i] = mat_det_cal(temp, n - 1) * ((i + j) % 2 == 1 ? -1 : 1);
                }
            }
        }
        return ans;
    }

    template<typename T>
    Matrix <T> mat_inv(const Matrix <T>& matrix, const T& eps) {
        assert(matrix.cols() == matrix.rows());
        T det = mat_det(matrix);
        assert(det > eps);
        size_t n = matrix.rows();
        Matrix<T> ans(n, n);
        Matrix<T> adj = mat_adj(matrix, n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                ans[i][j] = adj[i][j] / det;
            }
        }
        return ans;
    }

    template<typename T>
    T mat_trace(const Matrix <T>& matrix) {
        assert(matrix.cols() == matrix.rows());
        T trace{};
        for (size_t i = 0; i < matrix.cols(); ++i) {
            trace += matrix[i][i];
        }
        return trace;
    }

    template<typename T>
    Matrix <T> mat_conv(const Matrix <T>& lhs, const Matrix <T>& rhs) {
        assert(lhs.rows() >= rhs.rows() && lhs.cols() >= rhs.cols());
        size_t row = lhs.rows() + rhs.rows() - 1, col = lhs.cols() + rhs.cols() - 1;
        Matrix<T> res(row, col);
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                for (size_t m = 0; m < rhs.rows(); ++m) {
                    for (size_t n = 0; n < rhs.cols(); ++n) {
                        if (i - m < lhs.rows() && j - n < lhs.cols())
                            res[i][j] += lhs[i - m][j - n] * rhs[m][n];
                    }
                }
            }
        }
        return res;
    }

    template<typename T>
    Matrix <T> mat_eig(const Matrix <T>& matrix, const T& eps, const T& identity, bool return_val) {
        assert(matrix.cols() == matrix.rows());
        size_t n = matrix.cols();
        bool t = 0;
        T res[2]{}, u[n][2]{identity};
        while (true) {
            t = !t;
            for (size_t i = 0; i < n; ++i) {
                u[i][t] = identity - identity;
                for (size_t j = 0; j < n; ++j) {
                    u[i][t] += u[j][!t] * matrix[i][j];
                }
            }
            res[t] = u[0][t] / u[0][!t];
            if (abs(res[1] - res[0]) <= abs(eps)) break;
        }
        if (return_val) return Matrix<T>(1, 1, res[t]);
        T min = u[0][t];
        for (size_t i = 1; i < n; ++i) {
            if (abs(u[i][t]) < abs(min)) min = u[i][t];
        }
        Matrix<T> ans(n,1);
        for (size_t i = 0; i < n; ++i) {
            ans[i][0] = u[i][t] / min;
        }
        return ans;
    }

    template<typename T>
    T mat_eig_val(const Matrix <T>& matrix, const T& eps, const T& identity) {
        return mat_eig(matrix, eps, identity, true)[0][0];
    }


    template<typename T>
    Matrix <T> mat_eig_vec(const Matrix <T>& matrix, const T& eps, const T& identity) {
        return mat_eig(matrix, eps, identity, false);
    }
}