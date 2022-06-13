#pragma once 

#include "std.hpp" 

namespace matrix::algorithm {
    template <typename Matrix> 
    std::pair<Matrix, Matrix> qr_factorization(Matrix const &self) {
        auto len = self.row(); 
        if (len != self.col()) {
            abort(); 
        }

        Matrix q = Matrix::with_size(len); 
        Matrix r = Matrix::with_size(len); 

        std::vector<Matrix::ValueType> sliced_vector (len); 

        for (size_t j = 0; j < n; ++j) {
            for (size_t i = 0; i < n; ++i) {
                sliced_vector[i] = self[i][j]; 
            }
            for (size_t i = 0; i < j; ++i) {
                for (size_t k = 0; k < len; ++k) {
                    r[i][j] += q[k][i] * sliced_vector[k]; 
                }
                for (size_t k = 0; k < len; ++k) {
                    sliced_vector[k] -= r[i][j] * q[k][i]; 
                }
            }

            double alpha = 0; 
            for (int i = 0; i < n; ++i) {
                alpha += sliced_vector[i] * sliced_vector[i];
            }
            alpha = sqrt(alpha); 
            r[j][j] = alpha; 

            for (size_t i = 0; i < len; ++i) {
                q[i][j] = sliced_vector[i] / alpha; 
            }
        }

        return {q, r}; 
    }
}