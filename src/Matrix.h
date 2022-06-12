
#ifndef ZIP_CPP_MATRIX_H
#define ZIP_CPP_MATRIX_H

#include "std.hpp"

namespace mat {
    template<typename T>
    class Matrix {
    public:
        //constructor and destructor
        Matrix();

        Matrix(const Matrix& matrix);

        Matrix(size_t r, size_t c, T* d);

        Matrix(size_t r, size_t c, T d);

        Matrix(size_t r, size_t c);
        ~Matrix();

        Matrix& operator=(const Matrix& matrix);

        T* operator[](size_t r);

        const T* operator[](size_t r) const;

        size_t rows() const;

        size_t cols() const;

        size_t tots() const;

        friend std::istream& operator>>(std::istream& in, Matrix<T>& res) {
            size_t r, c;
            in >> r >> c;
            res.reshape(r, c);
            for (int i = 0; i < res.row; ++i) {
                for (int j = 0; j < res.col; ++j) {
                    in >> res[i][j];
                }
            }
            return in;
        }

        friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& res) {
            out << "row: " << res.row << " col: " << res.col << "\n";
            for (int i = 0; i < res.row; ++i) {
                for (int j = 0; j < res.col; ++j) {
                    out << res[i][j] << "\t";
                }
                out << "\n";
            }
            return out;
        }

        Matrix& operator+=(const Matrix& rhs); //todo: add more operators

        Matrix<T>& reshape(size_t r, size_t c);

    private:
        T* data;
        T** pdata;
        size_t row, col, tot;

        void init(size_t r, size_t c);

        void remove();
    };

    template<typename T>
    Matrix<T> mat_transpose(const Matrix<T>& matrix);

    template<typename T>
    Matrix<T> mat_conjugate(const Matrix<T>& matrix);

    template<typename T>
    Matrix<T> mat_ele_mul(const Matrix<T>& lhs, const Matrix<T>& rhs);

    template<typename T>
    Matrix<T> mat_dot(const Matrix<T>& lhs, const Matrix<T>& rhs);

    template<typename T>
    Matrix<T> mat_cross(const Matrix<T>& lhs, const Matrix<T>& rhs);

    template<typename T1, typename T2>
    Matrix<T1> operator*(const Matrix<T1>& lhs, const Matrix<T2>& rhs); //todo: add more operators

    template<typename T>
    T mat_min(const Matrix<T>& matrix);

    template<typename T>
    T mat_max(const Matrix<T>& matrix);

    template<typename T>
    T mat_sum(const Matrix<T>& matrix);

    template<typename T>
    T mat_avg(const Matrix<T>& matrix);

    template<typename T>
    Matrix<T> mat_slice(const Matrix<T>& matrix, size_t row1, size_t row2, size_t col1, size_t col2);

    template<typename T>
    T mat_det(const Matrix<T> & matrix);

    template<typename T>
    Matrix <T> mat_inv(const Matrix<T> & matrix, const T& eps);

    template<typename T>
    T mat_trace(const Matrix<T> & matrix);

    template<typename T>
    Matrix <T> mat_conv(const Matrix<T> & lhs, const Matrix<T> & rhs);

    template<typename T>
    T mat_eig_val(const Matrix<T> &matrix, const T& eps, const T& identity); //Only return the principal eigenvalue

    template<typename T>
    Matrix<T> mat_eig_vec(const Matrix<T> &matrix, const T& eps, const T& identity); //Only return the principal eigenvector

}


#endif //ZIP_CPP_MATRIX_H
