#pragma once 

#include "std.hpp" 

#include "def/matrix/linear_owned_matrix.hpp"

namespace matrix::algorithm {
    template <typename Matrix, typename DataType = typename type_traits::template TypeUpgrade<typename Matrix::ValueType>::type>  
    std::pair<typename Matrix::template MatrixOfType<DataType>, typename Matrix::template MatrixOfType<DataType>> qr_factorization(Matrix const &self) {
        auto len = self.row(); 
        if (len != self.col()) {
            throw matrix::exception::MatrixNonSquareException( __FILE__ ":" STRING(__LINE__) " " STRING(__FUNCTION__) ": the matrix is not a square matrix. "); 
        }

        static_assert (
            std::is_same_v< 
                typename type_traits::template TypeUpgrade<typename Matrix::ValueType>::type, 
                DataType> 
        ); 
        // using DataType = typename type_traits::template TypeUpgrade<typename Matrix::ValueType>::type; 

        auto q = Matrix::template MatrixOfType<DataType>::with_size(len); 
        auto r = Matrix::template MatrixOfType<DataType>::with_size(len); 

        std::vector<DataType> sliced_vector (len); 

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

            DataType alpha {}; 
            for (int i = 0; i < len; ++i) {
                alpha += sliced_vector[i] * sliced_vector[i];
            }
            alpha = sqrt(alpha); 
            r[j][j] = alpha; 

            for (size_t i = 0; i < len; ++i) {
                q[i][j] = sliced_vector[i] / alpha; 
            }
        }

        // todo: examine the deep copy happen or not. 
        return {q, r}; 
    }

    namespace helper {
        struct ComplexComp {
            template <typename T> 
            bool operator () (T const &lhs, T const &rhs) const {
                if constexpr (type_traits::IsComplex<T>::value) {
                    return abs(lhs) < abs(rhs); 
                } else {
                    return lhs < rhs; 
                }
            } 
        }; 
    }

    template <typename Matrix> 
    auto eigenvalue(Matrix const &self) {

        constexpr int attempt_cnt = 100; 

        // using ResultType = std::vector<typename Matrix::ValueType>; 
        using DataType = typename type_traits::template TypeUpgrade<typename Matrix::ValueType>::type; 
        using ResultType = std::vector<DataType>; 
        
        typename Matrix::template MatrixOfType<DataType> temp = self; 
        for (int i = 0; i < attempt_cnt; ++i) {
            auto [q, r] = qr_factorization(temp);
            temp = r * q;
        }

        ResultType result; 
        result.reserve(temp.row()); 

        for (int i = 0; i < temp.row(); ++i) {
            // result[0][i] = temp[i][i];
            result.push_back(temp[i][i]); 
        }

        sort(result.begin(), result.end(), helper::ComplexComp{});

        return result;
    }

    template <typename Matrix> 
    auto gaussian_elimination_as_mut(Matrix &self) {

        size_t row = self.row(); 
        
        for (size_t i = 0; i < row; ++i) {
            auto col = self.col(); 
            if (i >= col) 
                break; 
            
            auto pivot = self[i][i]; 

            if (is_nearly_zero(pivot)) {
                size_t j; 
                for (j = i + 1; j < row; ++j) {
                    if (!is_nearly_zero(self[j][i])) {
                        // std::swap(permutation[i], permutation[j]); 
                        for (size_t k {}; k < col; ++k) {
                            std::swap(self[i][k], self[j][k]); 
                        }
                        break; 
                    } 
                }
                if (j == row) {
                    return i; 
                }
            }

            for (size_t j = i + 1; j < row; ++j) {
                auto divisor = self[j][i] / pivot; 
                self[j][i] = {}; 
                for (size_t k = i + 1; k < col; ++k) {
                    self[j][k] -= self[i][k] * divisor; 
                    if (algorithm::is_nearly_zero(self[j][k])) {
                        self[j][k] = 0; 
                    }
                }

            }
        }

        return row; 
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
        }

        return self; 
    }

    template <typename Matrix, typename ResultDataType = typename type_traits::template TypeUpgrade<typename Matrix::ValueType>::type> 
    auto eigenvector (Matrix const &self) {
        auto len = self.row(); 
        if (len != self.col()) {
            throw matrix::exception::MatrixNonSquareException( __FILE__ ":" STRING(__LINE__) " " STRING(__FUNCTION__) ": the matrix is not a square matrix. "); 
        }

        typename Matrix::template MatrixOfType<ResultDataType> ans(len, len);

        size_t cnt = 0; 
        auto eigenvalues = eigenvalue(self); 

        auto last = eigenvalues[0]; 
        for (size_t i = 0; i < len; ++i) {
            lassert (i < eigenvalues.size());
            auto value = eigenvalues[i]; 

            // std::cout << "last: " << last << "\nvalue: " << value << "\ni:" << i << "\n";
            static_assert (std::is_same_v<decltype(value), double>); 
            if (i != 0 && type_traits::is_nearly_same(last, value)) {
                continue; 
            }
                
            typename Matrix::template MatrixOfType<double> temp = self; 
            for (size_t j = 0; j < len; ++j) {
                temp[j][j] -= value; 
            }

            // for (size_t i = 0; i < temp.row(); ++i) {
            //     for (size_t j = 0; j < temp.col(); ++j) {
            //         std::cout << temp[i][j] << " ";
            //     }
            //     std::cout << "\n";
            // }

            gaussian_elimination_as_mut(temp); 

            // std::cout << "cur value: " << value << std::endl;
            // for (size_t i = 0; i < temp.row(); ++i) {
            //     for (size_t j = 0; j < temp.col(); ++j) {
            //         std::cout << temp[i][j] << " ";
            //     }
            //     std::cout << "\n";
            // }

            for (size_t j = 0; j < len; ++j) {

                if (!is_nearly_zero(temp[j][j])) {
                    auto pivot = temp[j][j]; 
                    for (size_t k = j; k < len; ++k) {
                        temp[j][k] /= pivot; 
                        // std::cout << temp[j][k] << " | ";
                    }
                } else {
                    for (size_t k = 0; k < len; ++k){
                        ans[k][cnt] = -temp[k][j];
                    }
                    ans[j][cnt] = 1;
                    cnt++;
                }

            }
            last = value;
        } 
        return ans; 
    } 

    template <typename Matrix, typename ResultDataType = typename type_traits::template TypeUpgrade<typename Matrix::ValueType>::type> 
    auto eigenvector_depreacated (Matrix const &self) {
        auto len = self.row(); 
        if (len != self.col()) {
            throw matrix::exception::MatrixNonSquareException( __FILE__ ":" STRING(__LINE__) " " STRING(__FUNCTION__) ": the matrix is not a square matrix. "); 
        }

        using ResultType = std::vector<std::pair<ResultDataType, std::vector<ResultDataType>>>; 

        using SuggestedMatrix = typename Matrix::template MatrixOfType<ResultDataType>; 

        ResultType ans; 
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

            gaussian_elimination_as_mut(temp); 

            for (size_t j = 0; j < len; ++j) {
                if (!is_nearly_zero(temp[j][j])) {
                    auto pivot = temp[j][j]; 
                    for (size_t k = j; k < len; ++k) {
                        temp[j][k] /= pivot; 
                    }
                } else {
                    std::vector<ResultDataType> t; 
                    t.resize(len); 
                    for (size_t k = 0; k < len; ++k) 
                        t[k] = temp[k][j]; 
                    ans.push_back({value, std::move(t)}); 
                }
            }
        } 
        return ans; 
    } 

}