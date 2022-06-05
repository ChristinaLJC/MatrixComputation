#include "def/format.hpp"

namespace matrix::inline prelude {

    namespace helper {
        template <typename F, bool secure, size_t index = 0> 
        void add(u128 &result, u128 const &lhs, u128 const &rhs, u64 cached = 0) noexcept (!secure && !logical_error_detected) {
            lassert (cached <= std::numeric_limits<u32>::max()); 
            cached += F{}.template operator()<index>(lhs); 
            cached += F{}.template operator()<index>(rhs); 
            F{}.template operator()<index>(result) = static_cast<u32>(cached); 
            cached >>= 32; 
            if constexpr (index < 3) {
                add<F, secure, index + 1> (result, lhs, rhs, cached); 
            } else if constexpr (secure) {
                // Find the cached is over zero: means the overflow situation happening! 
                if (cached) {
                    // Just throw an exception describe it!  
                    throw exception::MatrixOverflowException("Overflow happen: the cached value now is {}. "_format(cached)); 
                }
            }
        }
    }

    template <bool secure> 
    u128 u128::operator+ (u128 const &rhs) const noexcept (!secure && !logical_error_detected) {
        u128 result; 
        helper::add<GetByIndex, secure>(result, *this, rhs); 
        return result; 
    }

    template <bool secure> 
    u128 &u128::operator+= (u128 const &rhs) noexcept (!secure && !logical_error_detected) {
        u128 result = *this + rhs; 
        return *this = result;  
    }

}