#pragma once 

namespace matrix::inline prelude {

    namespace helper {
        template <typename F, size_t up_index> 
        constexpr bool partial_eq(u128 const &lhs, u128 const &rhs) noexcept {
            auto &&lhs_val = F{}.template operator()<up_index>(lhs); 
            auto &&rhs_val = F{}.template operator()<up_index>(rhs); 
            if (lhs_val != rhs_val) {
                return false; 
            } else if constexpr (up_index) {
                return partial_eq<F, up_index - 1>(lhs, rhs); 
            } else {
                return true; 
            }
        }
    }

    constexpr bool u128::operator ==(u128 const &rhs) const noexcept {
        return helper::partial_eq<GetByIndex, 3>(*this, rhs); 
    }

    constexpr bool u128::operator ==(u32 rhs) const noexcept {
        return *this == u128(rhs); 
    }

    constexpr bool u128::operator ==(u64 rhs) const noexcept {
        return *this == u128(rhs); 
    }
}