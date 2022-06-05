#pragma once 

namespace matrix::inline prelude {

    namespace helper {
        template <typename F, size_t upper_index, bool eq_return_true> 
        constexpr bool less_than(u128 const &lhs, u128 const &rhs) noexcept {
            auto &&lhs_v = F{}.template operator()<upper_index>(lhs); 
            auto &&rhs_v = F{}.template operator()<upper_index>(rhs); 
            if (lhs_v < rhs_v) {
                return true; 
            } else if (lhs_v > rhs_v) {
                return false; 
            } else if constexpr (upper_index) {
                return less_than<F, upper_index-1, eq_return_true>(lhs, rhs); 
            } else {
                return eq_return_true; 
            }
        }
    }

    constexpr bool u128::operator< (u128 const &rhs) const noexcept {
        return helper::less_than<GetByIndex, 3, false>(*this, rhs); 
    }

    constexpr bool u128::operator<= (u128 const &rhs) const noexcept {
        return helper::less_than<GetByIndex, 3, true>(*this, rhs); 
    }
}