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
            using This = SparseOwnedMatrix;
            using Super = container<std::size_t, T>;  
            
            SparseOwnedMatrix(size_t row, size_t col): row(row), col(col) {} 

            struct Visitor {
                This &self; 
                size_t row; 
                Visitor (This &self, size_t row) : self(self), row(row) {} 

                ValueType &operator[] (size_t col) const {
                    return ((Super&)self)[row * self.col + col]; 
                }
            }; 

            struct ConstVisitor {
                This const &self; 
                size_t row; 
                ConstVisitor (This const &self, size_t row) : self(self), row(row) {} 

                ValueType const &operator[] (size_t col) const {
                    return ((Super&)self)[row * self.col + col]; 
                }
            }; 

            Visitor operator[] (size_t v) {
                return Visitor(*this, v); 
            }

            ConstVisitor operator[] (size_t v) const {
                return ConstVisitor(*this, v); 
            }
    }; 
}