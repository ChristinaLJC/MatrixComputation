#pragma once 

namespace matrix::inline prelude {

    namespace helper {
        template <typename F, size_t index, u32 to_divide> 
        constexpr void divide_and_then_eq(u128 &self, u32 *remainder = nullptr, u64 cached = 0) noexcept (!logical_error_detected) {
            auto &&v = F{}.template operator()<index>(self); 
            cached = (cached << 32) + v; 

            lassert ((i64) cached >= 0); 

            lldiv_t result = std::div((i64)cached, (i64)to_divide); 

            // cached = result.
            v = result.quot; 
            cached = result.rem; 
            if constexpr (index) {
                divide_and_then_eq<F, index - 1, to_divide>(self, remainder, cached); 
            } else {
                lassert (cached <= std::numeric_limits<u32>::max()); 
                if (remainder) {
                    *remainder = static_cast<u32>(cached); 
                }
            }
        }
    }

    template <u32 to_divide> 
    constexpr u128 &u128::divide_and_then_eq(u32 *remainder) noexcept(!logical_error_detected) {
        helper::divide_and_then_eq<GetByIndex, 3, to_divide>(*this, remainder); 
        return *this; 
    }
}