#pragma once 

#include "std.hpp" 

namespace matrix {
    template <typename ValueType_, template <typename ...> typename ValueContainer_ = std::valarray> 
    class OwnedMatrix : ValueContainer_<ValueContainer_<ValueType_>> {
        private: 
        public: 
            using ValueType = ValueType_; 
            template <typename... Args>  
            using ContainerType = ValueContainer_<Args...>; 
            constexpr static bool is_fixed = false; 
            OwnedMatrix(size_t c, size_t r): 
                ContainerType<ContainerType<ValueType>>(ContainerType<ValueType>(r), c) {}  
        public: 
            struct Visiter{
                ContainerType<ValueType> &self; 
                Visiter(OwnedMatrix &self): self(self) {} 
                ValueType &operator[] (size_t index) {
                    lassert (index > 0); 
                    lassert (index < self.size()); 
                    return self[index]; 
                }
            }; 
            struct ConstVisitor {
                ContainerType<ValueType> const &self; 
                ConstVisitor(OwnedMatrix const &self): self(self) {} 
                ValueType const &operator[] (size_t index) {
                    lassert (index < self.size()); 
                    return self[index]; 
                }
            }; 

            Visiter operator[] (size_t index) {
                lassert (index < this->size()); 
                return (*this)[index]; 
            }
            ConstVisitor operator[] (size_t index) const {
                lassert (index < this->size()); 
                return (*this)[index]; 
            }
            
            size_t row() const noexcept {
                return this->size(); 
            }
            size_t col() const {
                lassert (this->size()); 
                // return (*this)[0].self.size(); 
                return this->ContainerType<ContainerType<ValueType>>::operator [](0).size(); 
            }
    }; 
}