#pragma once 

#include "std.hpp" 

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
            LinearOwnedMatrix(Super &&self, size_t row): Super(std::move(self)), m_row(row) {} 
        public: 
            LinearOwnedMatrix(size_t r, size_t c): 
                ContainerType<ValueType>(r * c), m_row(r) {}  

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
                    return (Super&)self[row * (self.size() / self.row()) + index]; 
                }
            }; 

            Visiter operator[] (size_t index) {
                lassert (index < m_row); 
                return Visiter(*this, index); 
            }

            ConstVisitor operator[] (size_t index) const {
                lassert (index < m_row);
                return Visiter(*this, index); 
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
                if (rhs.row() != row) {
                    lassert (false); 
                    // Throw an exception describes the mismatching of the matrix. 
                }
                return LinearOwnedMatrix ((Super&)*this + (Super&)rhs, row); 
            }

            LinearOwnedMatrix operator-(LinearOwnedMatrix const &rhs) const {
                auto row = m_row; 
                if (rhs.row() != row) {
                    lassert (false); 
                    // Throw an exception describes the mismatching of the matrix. 
                }
                return LinearOwnedMatrix ((Super&)*this - (Super&)rhs, row); 
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