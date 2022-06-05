#pragma once 

namespace matrix::inline prelude {

    template <bool secure> 
    u128 u128::operator- (u128 const &rhs) const noexcept (!secure && !logical_error_detected) {
        if constexpr (secure) {
            if (*this < rhs) {
                throw exception::MatrixOverflowException("[uint128_t minus operator overflow]"); 
            }
        }
        u128 result = ~rhs; 
        ++result; 
        result += *this; 
        return result; 
    }

    template <bool secure> 
    u128 &u128::operator-= (u128 const &rhs) noexcept (!secure && !logical_error_detected) {
        u128 result = this->template operator- <secure> (rhs); 
        return *this = result; 
    }

}