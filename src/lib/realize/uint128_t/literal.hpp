#pragma once 

namespace matrix::inline prelude {
    namespace helper {

        template <u32 carry, size_t len> 
        constexpr u128 carry_value() {
            if constexpr (len) 
                return carry_value<carry, len - 1>() * carry; 
            else 
                return 1u; 
        }

        template <u32 carry> 
        constexpr u128 build() {
            return 0u; 
        }

        template <u32 carry, char v, char... chars> 
        constexpr u128 build() {
            if constexpr (v >= '0' && v <= '9') {
                static_assert ((u32)(v - '0') < carry); 
                constexpr auto lhs = carry_value<carry, sizeof...(chars)>() * (u32)(v - '0'); 
                constexpr auto ans = lhs + build<carry, chars...>(); 
                static_assert (ans >= lhs); 
                return ans; 
            } else if constexpr (v >= 'a' && v <= 'f') {
                constexpr auto lhs = carry_value<carry, sizeof...(chars)>() * (u32)(v - 'a' + 10); 
                constexpr auto ans = lhs + build<carry, chars...>(); 
                static_assert (ans >= lhs); 
                return ans; 
            } else if constexpr (v >= 'A' && v <= 'F') {
                constexpr auto lhs = carry_value<carry, sizeof...(chars)>() * (u32)(v - 'A' + 10); 
                constexpr auto ans = lhs + build<carry, chars...>(); 
                static_assert (ans >= lhs); 
                return ans; 
            } else {
                abort(); 
                throw false; 
            }
        }

        template <u32 carry, char... chars> 
        class LiteralCarry {
            public: 
            constexpr static u128 get() noexcept {
                return build<carry, chars...>(); 
            }
        }; 

        template <char... chars> 
        class PrefixUint128_t : public LiteralCarry<10u, chars...> {
        }; 

        template <char... chars> 
        class PrefixUint128_t<'0', 'x', chars...> : public LiteralCarry<16u, chars...> {
        }; 

        template <char... chars> 
        class PrefixUint128_t<'0', 'X', chars...> : public LiteralCarry<16u, chars...> {
        }; 

        template <char... chars> 
        class PrefixUint128_t<'0', 'b', chars...> : public LiteralCarry<2u, chars...> {
        }; 

        template <char... chars> 
        class PrefixUint128_t<'0', 'B', chars...> : public LiteralCarry<2u, chars...> {
        }; 

        template <char... chars> 
        class PrefixUint128_t<'0', chars...> : public LiteralCarry<8u, chars...> {
        }; 
    }

    template <char... chars> 
    constexpr u128 operator""_u128 () noexcept {
        return helper::PrefixUint128_t<chars...>::get(); 
    }

    template <char... chars> 
    constexpr u128 operator""_uint128_t() noexcept {
        return helper::PrefixUint128_t<chars...>::get(); 
    } 
}