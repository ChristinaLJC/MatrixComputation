#include <tuple>
#include <math.h>

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

        // todo: what are you doing? 
        delete sliced_vector;

        return {Q, R};
    }
}

