#pragma once 

#include "operator_plus.hpp"

namespace matrix::inline prelude {
    bool u128::operator ==(u32 v) const noexcept {
        if (helper::is_not_zero<GetByIndex, 3>(*this)) 
            return false; 
        if (helper::is_not_zero<GetByIndex, 2>(*this)) 
            return false; 
        if (helper::is_not_zero<GetByIndex, 1>(*this)) 
            return false; 
        return (std::get<0>(*this) == v); 
    }
    bool u128::operator ==(u64 v) const noexcept {
        if (helper::is_not_zero<GetByIndex, 3>(*this) || helper::is_not_zero<GetByIndex, 2>(*this)) 
            return false; 
        return std::get<1>(*this) * 0x100000000ULL + std::get<0>(*this) == v; 
    }

    namespace helper {
        template <typename F, size_t index = 3> 
        bool is_same(u128 const &lhs, u128 const &rhs) {
            if (F{}.template operator()<index>(lhs) != F{}.template operator()<index>(rhs)) 
                return false; 
            if constexpr (index) 
                return is_same<F, index - 1>(lhs, rhs); 
            else 
                return true; 
        }
    }

    bool u128::operator ==(u128 const &v) const noexcept {
        return helper::is_same<GetByIndex>(*this, v); 
    }
}