#pragma once 

#include "std.hpp" 

namespace matrix {

    template <typename ValueType_, template <typename ...> ValueContainer_ = std::valarray> 
    class OwnedMatrix {
        private: 
        public: 
            using ValueType = ValueType_; 
            using ContainerType = ValueContainer_; 
            constexpr bool is_fixed = false; 
        
        private: 
            ContainerType<ContainerType<ValueType_>> values; 
        public: 
            
    }; 
}