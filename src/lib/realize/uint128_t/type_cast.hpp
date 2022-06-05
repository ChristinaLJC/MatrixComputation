#pragma once 

namespace matrix::inline prelude {

    namespace helper {
        // Reverse comparing! 
        template <typename F, size_t index, u32 val_match, u32... vals> 
        constexpr bool congruence(u128 const &self) {
            static_assert (index == sizeof...(vals)); 
            auto &&v = F{}.template operator()<index>(self); 
            if (v != val_match) {
                return false; 
            } else if constexpr (index) {
                return congruence<F, index - 1, vals...>(self); 
            } else {
                return true; 
            }
        }
    }

    constexpr u128::operator bool() const noexcept {
        return !helper::congruence<GetByIndex, 3, 0, 0, 0, 0>(*this); 
    }
}