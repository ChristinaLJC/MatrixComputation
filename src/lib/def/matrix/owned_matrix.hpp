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
                ContainerType<ContainerType<ValueType>>(c, ContainerType<ValueType>(r)) {}  
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
            // ContainerType<ValueType> &
            Visiter operator[] (size_t index) {
                lassert (index > 0); 
                lassert (index < this->size()); 
                return (*this)[index]; 
            }
    }; 
}