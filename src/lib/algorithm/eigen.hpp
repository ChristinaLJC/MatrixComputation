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

        for (size_t j = 0; j < len; ++j) {
            for (size_t i = 0; i < len; ++i) {
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

    template <typename Matrix> 
    std::vector<Matrix::ValueType> eigenvalue(Matrix const &self) {
        using ResultType = std::vector<Matrix::ValueType>; 
        
        Matrix temp = self; 
        for (int i = 0; i < 100; ++i) {
            auto [q, r] = qr_factorization(temp);
            temp = r * q;
        }

        ResultType result; 
        result.reserve(temp.row()); 

        for (int i = 0; i < temp.row(); ++i) {
            // result[0][i] = temp[i][i];
            result.push_back(temp[i][j]); 
        }

        sort(result.begin(), resul.end());
        // todo: sort the result

        return result;
    }

    template <typename ResultDataType = Matrix::ValueType, typename Matrix> 
    std::vector<std::pair<ResultDataType, std::vector<ResultDataType>>> eigenvector (Matrix const &self) {
        auto len = self.row(); 
        if (len != self.col()) {
            abort(); 
        }
        using ReturnType = std::vector<std::pair<ResultDataType, std::vector<ResultDataType>>>; 
        ReturnType ans; 
        ans.reserve(len); 

        size_t cnt = 0; 
        auto eigenvalues = eigenvalue(self); 

        auto last = eigenvalues[0]; 
        for (size_t i = 0; i < len; ++i) {
            lassert (i < eigenvalues.size());
            auto value = eigenvalues[i]; 

            if (i != 0 && last == value) 
                continue; 
            
            Matrix temp = self; 
            for (size_t j = 0; j < len; ++j) {
                temp[j][j] -= value; 
            }

            temp = gaussian_elimination(temp); 

            for (size_t j = 0; j < len; ++j) {
                if (temp[j][j]) {
                    auto pivot = temp[j][j]; 
                    for (size_t k = j; k < len; ++k) {
                        temp[j][k] /= pivot; 
                    }
                } else {
                    // for (size_t k = 0; k < len; ++k) {
                    // }
                    ans.push_back({value, temp[k]}); 
                }
            }
        } 
        return ans; 
    }
}