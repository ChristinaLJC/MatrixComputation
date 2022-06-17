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

        std::vector<typename Matrix::ValueType> sliced_vector (len); 

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
            for (int i = 0; i < len; ++i) {
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
    std::vector<typename Matrix::ValueType> eigenvalue(Matrix const &self) {
        using ResultType = std::vector<typename Matrix::ValueType>; 
        
        Matrix temp = self; 
        for (int i = 0; i < 100; ++i) {
            auto [q, r] = qr_factorization(temp);
            temp = r * q;
        }

        ResultType result; 
        result.reserve(temp.row()); 

        for (int i = 0; i < temp.row(); ++i) {
            // result[0][i] = temp[i][i];
            result.push_back(temp[i][i]); 
        }

        sort(result.begin(), result.end());

        return result;
    }

    template <typename Matrix, typename ResultDataType = typename Matrix::ValueType> 
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

            gaussian_elimination(temp); 

            for (size_t j = 0; j < len; ++j) {
                if (temp[j][j]) {
                    auto pivot = temp[j][j]; 
                    for (size_t k = j; k < len; ++k) {
                        temp[j][k] /= pivot; 
                    }
                } else {
                    // for (size_t k = 0; k < len; ++k) {
                    // }
                    // ans.push_back({value, temp[k]}); 
                    todo("")
                }
            }
        } 
        return ans; 
    } 

    template <typename OriginMatrix> 
    auto gaussian_elimination(OriginMatrix const &self_) {
        using DataType = typename type_traits::TypeUpgrade<typename OriginMatrix::ValueType>::type; 
        using ResultType = typename OriginMatrix::template MatrixOfType<DataType>; 
        ResultType self = self_; 
        size_t row = self.row(); 

        std::vector<size_t> permutation (row); 
        for (size_t i = 0; i < row; ++i) 
            permutation[i] = i; 
        
        for (size_t i = 0; i < row; ++i) {
            auto col = self.col(); 
            if (i >= col) 
                break; 
            
            auto pivot = self[permutation[i]][i]; 

            if (is_nearly_zero(pivot)) {
                size_t j; 
                for (j = i + 1; j < row; ++j) {
                    if (!is_nearly_zero(self[permutation[j]][i])) {
                        std::swap(permutation[i], permutation[j]); 
                        break; 
                    } 
                }
                if (j == row) {
                    todo ("It cannot find the pivot. "); 
                }
            }

            for (size_t j = i + 1; j < row; ++j) {
                auto divisor = self[permutation[j]][i] / pivot; 
                self[permutation[j]][i] = {}; 
                for (size_t k = i + 1; k < col; ++k) {
                    self[permutation[j]][k] -= self[permutation[i]][k] * divisor; 
                }
            }
            // for (size_t j = 0; j < )
        }

        return self; 

        // for (size_t i = 0; i < n; ++i) {
        //     auto pivot = self[i][i];
        //     if (is_nearly_zero(pivot)) {
        //         for (size_t j = i + 1; j < n; ++j) {
        //             if (!is_nearly_zero(self[j][i])) { 
        //                 // You have no need to write so complicated codes to exchange them, todo: use a better memory allocation. 
        //                 for (size_t k = 0; k < n; ++k) {
        //                     std::swap(self[j][k], self[i][k]); 
        //                 }
        //                 break;
        //             } 
        //         }
        //     }

        //     pivot = self[i][i];
        //     if (pivot == 0) continue;

        //     for (size_t j = i + 1; j < n; ++j) {
        //         auto temp = self[j][i];
        //         if (temp == 0) continue;

        //         for (size_t k = 0; k < n; ++k) {
        //             self[j][k] = self[j][k] - (double) self[j - 1][k] * temp / pivot;
        //         }
        //     }
        // }
    }
}