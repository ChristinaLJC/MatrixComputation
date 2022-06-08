#pragma once 

#include "realize/uint128_t/literal.hpp"

namespace matrix::inline prelude {

    template <char... chars> 
    i128 constexpr operator""_i128() noexcept {
        i128 constexpr result = i128(operator""_u128<chars...>()); 
        static_assert (
            std::get<3>(result) < 0x8000'0000u
        ); 
        return result; 
    }

    template <char... chars> 
    i128 constexpr operator""_int128_t() noexcept {
        return operator""_i128 <chars...>(); 
    }
}