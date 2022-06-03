#pragma once 

namespace matrix {
    inline namespace prelude {
        template <bool secure>
        uint128_t u128::operator+ (u64 other) const noexcept(!secure && !logical_error_detected) {
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
        uint128_t u128::operator+ (u32 other) const noexcept(!secure && !logical_error_detected) {
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
                } else if constexpr (secure) {
                    // Cached shouldn't be greater than zero, or a overflow exception would happens! 
                    // todo: throw an overflow exception. 
                    throw exception::MatrixOverflowException ("default"); 
                }
            }
        }

        template <bool secure> 
        u128 u128::operator+ (u128 const &rhs) const noexcept (!secure && !logical_error_detected) {
            u64 cached {}; 
            u128 ans; 
            helper::plus_together<u128::GetByIndex, secure, 4>(*this, rhs, ans); 
            return ans; 
        }

        namespace helper {
            template <typename F, size_t v = 3> 
            void divide_and_equal(u128 &dividend, u32 divisor, u32 *remainder, u64 cached = 0) noexcept (!logical_error_detected) {
                lassert (cached <= 0xFFFFFFFF); 
                cached += F{}.template operator()<v>(dividend); 
                lldiv_t result = std::div((i64)cached, (i64)divisor); 

                lassert (result.quot >= 0); 
                lassert (result.quot <= 0xFFFFFFFFLL); 
                F{}.template operator()<v>(dividend) = result.quot; 

                if constexpr (v) {
                    divide_and_equal<F, v - 1>(dividend, divisor, remainder, result.rem); 
                } else {
                    if (remainder) {
                        lassert (result.rem <= 0xFFFFFFFFLL); 
                        *remainder = result.rem; 
                    }
                }
            }

            template <typename F, u32 divisor, u32 *remainder, size_t v = 3> 
            void divide_and_equal(u128 &dividend, u64 cached = 0) noexcept (!logical_error_detected) {
                lassert (cached <= 0xFFFFFFFF); 
                cached += F{}.template operator()<v>(dividend); 
                lldiv_t result = std::div((i64)cached, (i64)divisor); 
                
                lassert (result.quot >= 0); 
                lassert (result.quot <= 0xFFFFFFFFLL); 
                F{}.template operator()<v>(dividend) = result.quot; 

                if constexpr (v) {
                    divide_and_equal<F, divisor, remainder, v - 1>(dividend, result.rem); 
                } else if constexpr (remainder) {
                    lassert (result.rem <= 0xFFFFFFFFLL); 
                    *remainder = result.rem; 
                }
            }

        }

        u128 &u128::divide_and_equal(u32 divisor, u32 *remainder) noexcept (!logical_error_detected) {
            helper::divide_and_equal<GetByIndex>(*this, divisor, remainder); 
            return *this; 
        }

        template <u32 divisor, u32 *remainder> 
        u128 &u128::divide_and_equal() noexcept(!logical_error_detected) {
            static_assert (divisor); 
            helper::divide_and_equal<GetByIndex, divisor, remainder>(*this); 
            return *this; 
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

    namespace helper {
        std::string &reverse(std::string &s) noexcept {
            if (s.size() <= 1) 
                return s; 
            size_t i = 0; 
            size_t end = s.size(); 
            while (i + 1 < end) {
                std::swap(s[i], s[end-1]); 
                ++i; --end; 
            }
            return s; 
        }
    }

    template <>  
    std::string u128::into() const {
        std::string result; 
        result.reserve(DECIMAL_LENGTH); 
        return result; 
    }
}

namespace matrix::type_traits {
    template <> template <>
    std::string Into<std::string>::into(u128 const &v) const {
        return v.into<std::string>(); 
    }
}