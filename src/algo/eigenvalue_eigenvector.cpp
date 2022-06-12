#include <tuple>
#include <math.h>

#define NUM 100

namespace matrix::algorithm {

    template <typename ResultMatrix = typename type_traits::DefaultInverseMatrixType<OriginMatrix>::type,
            typename OriginMatrix>
    std::tuple<ResultMatrix, ResultMatrix> QR_factorization(OriginMatrix const &self) {
        if (self.row() != self.col()) {
            // throw exception
        }

        auto n = self.row(); // the size of the matrix is n*n

        ResultMatrix Q = new_matrix(n, n); // use new_matrix to new a matrix
        ResultMatrix R = new_matrix(n, n);

        ResultMatrix sliced_vector = new_matrix(n, 1);

        for (int j = 0; j < n; ++j) {

            for(int i = 0; i < n; ++i) {
                sliced_vector[i][0] = self[i][j];
            }

            for (int i = 0; i < j; ++i) {

                for (int k = 0; k < N; ++k) {
                    R[i][j] += Q[k][i] * sliced_vector[k][0];
                }

                for (int k = 0; k < N; ++k) {
                    sliced_vector[k][0] -= R[i][j] * Q[k][i];
                }

            }

            // calculate the length of the vector
            double alpha = 0;
            for (int i = 0; i < n; ++i) {
                alpha += sliced_vector[i][0] * sliced_vector[i][0];
            }
            alpha = sqrt(alpha);

            R[j][j] = alpha;

            // calculate the current column of Q
            for (int i = 0; i < n; ++i) {
                Q[i][j] = sliced_vector[i][0] / alpha;
            }
        }

        return {Q, R};
    }


    template <typename ResultMatrix = typename type_traits::DefaultInverseMatrixType<OriginMatrix>::type,
            typename OriginMatrix>
    ResultMatrix eigenvalue(OriginMatrix const &self) {
        ResultMatrix temp = self;
        for (int i = 0; i < NUM; ++i) {
            auto [Q, R] = QR_factorization(temp);
            temp = R * Q;
        }

        ResultMatrix result = new_matrix(1, n);
        for (int i = 0; i < temp.row(); ++i) {
            result[0][i] = temp[i][i];
        }

        // todo: sort the result

        return result;
    }

    template <typename ResultMatrix = typename type_traits::DefaultInverseMatrixType<OriginMatrix>::type,
            typename OriginMatrix>
    ResultMatrix eigenvector(OriginMatrix const &self) {
        int n = self.row();

        ResultMatrix result = new_matrix(n, n);

        int cnt = 0;
        auto eigenvalues = eigenvalue(self);

        auto last = eigenvalues[0][0];
        for (int i = 0; i < n; ++i) {
            auto value = eigenvalues[0][i];

            if (i != 0 && last == value) continue;

            OriginMatrix temp = self;
            for (int j = 0; j < n; ++j) {
                temp[j][j] -= value;
            }

            temp = gaussian_elimination(temp);

            for (int j = 0; j < n; ++j) {
                if (temp[j][j] != 0) {
                    auto pivot = temp[j][j];
                    for (int k = j; k < n; ++k) {
                        temp[j][k] /= pivot;
                    }
                }
                else {
                    for (int k = 0; k < n; ++k) {
                        result[k][cnt] = temp[k][j];
                    }
                    cnt++;
                }
            }

            last = value;
        }

        return result;
    }



}

