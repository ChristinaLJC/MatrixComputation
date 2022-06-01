#pragma once 

namespace matrix {
    inline namespace prelude {
        template <bool secure>
        uint128_t u128::operator+ (u64 other) const noexcept(!secure && logical_error_detected) {
            u64 cached = other & 0xFFFFFFFF + std::get<0>(*this); 
            u128 ans; 
            std::get<0>(ans) = cached; 
            cached >>= 32;
            cached += (other >> 32) + std::get<1>(*this); 
            std::get<1>(ans) = cached; 
            cached >>= 32; 
            cached += std::get<2>(*this); 
            std::get<2>(ans) = cached; 
            cached >>= 32; 
            cached += std::get<3>(*this); 
            std::get<3>(ans) = cached; 
            if constexpr (secure) {
                lassert (cached <= 0xFFFFFFFF); 
            }
            return ans; 
        }
        template <bool secure>
        uint128_t u128::operator+ (u32 other) const noexcept(!secure && logical_error_detected) {
            u64 cached = other + (u64)std::get<0>(*this); 
            u128 ans; 
            std::get<0>(ans) = cached; 
            cached >>= 32; 
            cached += std::get<1>(*this); 
            std::get<1>(ans) = cached; 
            cached >>= 32; 
            cached += std::get<2>(*this); 
            std::get<2>(ans) = cached; 
            cached >>= 32; 
            cached += std::get<3>(*this); 
            std::get<3>(ans) = cached; 
            if constexpr (secure) {
                lassert (cached <= 0xFFFFFFFF); 
            }
            return ans; 
        }

        namespace helper {
            template <typename F, bool secure, size_t top = 4, typename V, size_t now_index = 0> 
            void plus_together(V const &lhs, V const &rhs, V &ans, u64 cached = 0) {
                if constexpr (now_index < top) {
                    lassert(cached <= 0xFFFFFFFF); 
                    cached += (i64)F{}.template operator()<now_index>(lhs) + F{}.template operator()<now_index>(rhs); 
                    F{}.template operator()<now_index>(ans) = cached; 
                    plus_together<F, V, secure, top, now_index + 1>(lhs, rhs, ans, cached >> 32); 
                } else {
                    // Cached shouldn't be greater than zero, or a overflow exception would happens! 
                    // todo: throw an overflow exception. 
                }
            }
        }

        template <bool secure> 
        u128 u128::operator+ (u128 const &rhs) const noexcept (!secure && logical_error_detected) {
            u64 cached {}; 
            u128 ans; 
            helper::plus_together<u128::GetByIndex, secure, 4>(*this, rhs, ans); 
            return ans; 
        }
        // template <bool secure>
        // uint128_t operator- (u64) const noexcept(!secure && logical_error_detected) {

        // }
        // template <bool secure>
        // uint128_t operator- (u32) const noexcept(!secure && logical_error_detected); 
        // template <bool secure>
        // uint128_t operator* (u64) const noexcept(!secure && logical_error_detected);
        // template <bool secure>
        // uint128_t operator* (u32) const noexcept(!secure && logical_error_detected);
        // template <bool secure>
        // uint128_t operator/ (u64) const noexcept(!secure && logical_error_detected);
        // template <bool secure>
        // uint128_t operator/ (u32) const noexcept(!secure && logical_error_detected);
        // u32 operator% (u32) const noexcept(logical_error_detected); 
        // u64 operator% (u64) const noexcept(logical_error_detected); 

    }
}