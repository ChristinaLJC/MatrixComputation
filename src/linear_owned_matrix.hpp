#pragma once 

#include "std.hpp" 
#include "def/mexception.hpp"

namespace matrix::exception {
    struct MatrixStructureException : public MatrixBaseException {
        using MatrixBaseException::MatrixBaseException; 
        ~MatrixStructureException() = 0; 
    }; 

    MatrixStructureException::~MatrixStructureException() {} 

    struct MatrixStructureMismatchingException : public MatrixStructureException {
        using MatrixStructureException::MatrixStructureException; 
    }; 

    struct MatrixStructureNullException : public MatrixStructureException {
        using MatrixStructureException::MatrixStructureException; 
    }; 
}

namespace matrix {
    template <typename ValueType_, template <typename ...> typename ValueContainer_ = std::valarray> 
    class LinearOwnedMatrix : ValueContainer_<ValueType_> {
        private: 
            size_t m_row; 
        public: 
            using ValueType = ValueType_; 
            template <typename... Args>  
            using ContainerType = ValueContainer_<Args...>; 
            using Super = ContainerType<ValueType>; 
            using This = LinearOwnedMatrix; 

            constexpr static bool is_fixed = false; 
            
        private: 
            LinearOwnedMatrix(Super &&self, size_t row): Super(std::move(self)), m_row(row) {
                lassert (size());
                // if (!size()) {
                //     throw MatrixStructureNullException
                // }
            }
        public: 
            LinearOwnedMatrix(size_t r, size_t c): 
                ContainerType<ValueType>(r * c), m_row(r) {
                    if (!r || !c) {
                        throw matrix::exception::MatrixStructureNullException ("LinearOwnedMatrix cannot be initialized as empty size. "); 
                    }
                }  

            struct Visiter{
                LinearOwnedMatrix &self; 
                size_t row; 
                Visiter(LinearOwnedMatrix &self, size_t row): self(self), row(row) {} 
                ValueType &operator[] (size_t index) {
                    lassert (index < self.size() / self.row()); 
                    return ((Super&)self)[row * (self.size() / self.row()) + index]; 
                }
            }; 
            struct ConstVisitor {
                LinearOwnedMatrix const &self; 
                size_t row; 
                ConstVisitor(LinearOwnedMatrix const &self, size_t row): self(self), row(row) {} 
                ValueType const &operator[] (size_t index) {
                    lassert (index < self.size() / self.row()); 
                    return ((Super const &)self)[row * (self.size() / self.row()) + index]; 
                }
            }; 

            Visiter operator[] (size_t index) {
                lassert (index < m_row); 
                return Visiter(*this, index); 
            }

            ConstVisitor operator[] (size_t index) const {
                lassert (index < m_row);
                return ConstVisitor(*this, index); 
            }
            
            size_t row() const noexcept {
                return m_row; 
            }

            size_t col() const noexcept {
                return this->size() / m_row; 
            }

            size_t size() const noexcept {
                return this->Super::size(); 
            }

            LinearOwnedMatrix operator+(LinearOwnedMatrix const &rhs) const {
                auto row = m_row; 
                // Throw an exception describes the mismatching of the matrix. 
                Use matrix::exception; 
                if (rhs.row() != row) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix addition with the mismatched row value. "); 
                } else if (size() != rhs.size()) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix addition with the mismatched col value. "); 
                }
                return LinearOwnedMatrix ((Super&)*this + (Super&)rhs, row); 
            }

            LinearOwnedMatrix operator-(LinearOwnedMatrix const &rhs) const {
                Use matrix::exception; 
                auto row = m_row; 
                if (rhs.row() != row) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix subtraction with the mismatched row value. ");
                } else if (size() != rhs.size()) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix subtraction with the mismatched col value. ");
                }
                return LinearOwnedMatrix ((Super&)*this - (Super&)rhs, row); 
            }

            LinearOwnedMatrix operator*(ValueType const &rhs) const {
                return LinearOwnedMatrix ((Super&)*this * rhs, row()); 
            }

            LinearOwnedMatrix operator/(ValueType const &rhs) const {
                return LinearOwnedMatrix ((Super&)*this / rhs, row()); 
            }

            LinearOwnedMatrix cross_product(LinearOwnedMatrix const &rhs) const {
                Use matrix::exception;
                auto row = m_row;
                if (size() / row != rhs.row()) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix cross product with the mismatched matrix size. ");
                }
                This ans(row, rhs.size() / rhs.row());
                for (size_t r = 0; r < row; ++r){
                    for (size_t c = 0; c < rhs.size() / rhs.row()){
                        for (size_t k = 0; k < size() / row; ++k){
                            ans[r][c] += ((*this)[r][k] * rhs[k][c]); // Can '+=' be used directly without manual initialization?
                        }
                    }
                }
                return ans;
            }

            LinearOwnedMatrix dot_product(LinearOwnedMatrix const &rhs) const { // Only regard one-column-matrix as vector
                Use matrix::exception;
                auto row = m_row;
                if (rhs.row() != row) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix dot product with the mismatched row value. ");
                } else if (size() != rhs.size()) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix dot product with the mismatched col value. ");
                }
                This ans(1, size() / row);
                for (size_t r = 0; r < row; ++i){
                    for (size_t c = 0; c < rhs.size() / rhs.row()){
                        ans[0][c] += (*this)[r][c] * rhs[r][c]; // Can '+=' be used directly without manual initialization?
                    }
                }
                return ans;
            }

            LinearOwnedMatrix transposition() const {
                auto row = m_row;
                This ans (size() / row, row);
                for (size_t r = 0; r < size() / row; ++r) {
                    for (size_t c = 0; c < row; ++c) {
                        ans[r][c] = (*this)[c][r]; 
                    }
                }
                return ans; 
            }

            LinearOwnedMatrix conjugation() const {
                auto row = m_row;
                This ans (size() / row, row);
                for (size_t r = 0; r < size() / row; ++r) {
                    for (size_t c = 0; c < row; ++c) {
                        ans[r][c] = conj((*this)[r][c]);
                    }
                }
                return ans;
            }

            ValueType max() const {
                auto row = m_row;
                ValueType max = (*this)[0][0];
                for (size_t r = 0; r < size() / row; ++r) {
                    for (size_t c = 0; c < row; ++c) {
                        if (max < (*this)[c][r]) {
                            max = (*this)[c][r];
                        }
                    }
                }
                return max;
            }

            ValueType min() const {
                auto row = m_row;
                ValueType min = (*this)[0][0];
                for (size_t r = 0; r < size() / row; ++r) {
                    for (size_t c = 0; c < row; ++c) {
                        if (min > (*this)[c][r]) {
                            min = (*this)[c][r];
                        }
                    }
                }
                return min;
            }

            ValueType sum() const {
                auto row = m_row;
                ValueType sum{};
                for (size_t r = 0; r < size() / row; ++r) {
                    for (size_t c = 0; c < row; ++c) {
                        sum = sum + (*this)[c][r];
                    }
                }
                return sum;
            }

            ValueType avg() const {
                return sum() / size();
            }

            LinearOwnedMatrix determinant_cut(LinearOwnedMatrix const &matrix, size_t size, size_t i){ //should be private
                This temp (size, size);
                for (size_t r = 0; r < size; ++r) {
                    for (size_t c = 0; c < size; ++c) {
                        temp[r][c] = matrix[r + 1][c + (c >= i)];
                    }
                }
                return temp;
            }

            ValueType determinant_calculate(LinearOwnedMatrix const &matrix, size_t size){ //should be private
                if (size == 1){
                    return matrix[0][0];
                }
                ValueType ans{};
                for (size_t i = 0; i < size; ++i){
                    ans = ans + matrix[0][i] * determinant_calculate(matrix, determinant_cut(size - 1, i),size - 1) * (i % 2 ? -1 : 1);
                }
                return ans;
            }

            ValueType determinant() const {
                Use matrix::exception;
                auto row = m_row;
                if (row != (size() / row)){
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix determinant with non-square matrix. ");
                }
                return determinant_calculate(row);
            }

            ValueType trace() const {
                Use matrix::exception;
                auto row = m_row;
                if (row != (size() / row)){
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix trace with non-square matrix. ");
                }
                ValueType trace{};
                for (size_t i = 0; i < size(); i++){
                    trace = trace + (*this)[i][i];
                }
                return trace;
            }

            static LinearOwnedMatrix with_size(size_t k) {
                // if (std::numeric_limits<size_t>::max() / k < k) {
                //     abort(); 
                //     // Cannot construct such a large value! 
                // }
                return LinearOwnedMatrix(k, k); 
            }
            
            static LinearOwnedMatrix with_identity_size(size_t k) {
                This ans (k, k); 
                for (size_t i = 0; i < k; ++i) {
                    ans[i][i] = 1; 
                }
                return ans; 
            }
    }; 
}