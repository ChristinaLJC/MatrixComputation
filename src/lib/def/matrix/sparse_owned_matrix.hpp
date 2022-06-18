#pragma once 

#include "linear_owned_matrix.hpp"

namespace matrix {
    template <typename T, template <typename ...> typename container = std::map> 
    struct SparseOwnedMatrix : private container<std::size_t, T> {
        private: 
            size_t row, col; 
        public: 
            using ValueType = T; 
            template <typename O> 
            using MatrixOfType = SparseOwnedMatrix<O, container>; 
            
            SparseOwnedMatrix(size_t row, size_t col): row(row), col(col) {} 
    }; 
}