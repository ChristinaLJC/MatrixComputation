#pragma once 

#include "std.hpp"

#include "uint128_t.hpp"

namespace matrix::inline prelude {
    class int128_t; 
    using i128 = int128_t; 
    class int128_t : private uint128_t {

        private: 
            constexpr explicit(true) int128_t(uint128_t const &rhs): 
                uint128_t(rhs) {} 

        public: 

            constexpr int128_t(): uint128_t() {} 
            constexpr int128_t(i32 v): uint128_t(
                {
                    (u32)v, 
                    v < 0 ? 0xffffffffu : 0, 
                    v < 0 ? 0xffffffffu : 0, 
                    v < 0 ? 0xffffffffu : 0, 
                }
            ) {} 
            constexpr int128_t(i64 v): uint128_t({
                (u32)v, 
                static_cast<u32>((u64)v >> 32), 
                v < 0 ? 0xffffffff : 0, 
                v < 0 ? 0xffffffff : 0, 
            }) {} 
            constexpr int128_t(i128 const &) = default; 

            inline bool is_negative() const noexcept {
                return std::get<3>(*this) & 0x80000000; 
            }

            template <bool secure = false> 
            constexpr i128 operator+ (i128 const &rhs) const noexcept (!secure && !logical_error_detected) {
                i128 result = i128(
                    static_cast<u128 const &>(*this) .template operator+ <false> (static_cast<u128 const &>(rhs))
                ); 
                if constexpr (secure) {
                    if (*this && rhs) {
                        if (!(this->is_negative() ^ rhs.is_negative())) {
                            if (result.is_negative() ^ this->is_negative()) {
                                throw exception::MatrixOverflowException("Addition between i128 meets overflow! "); 
                            }
                        }
                    } 
                }
                return result; 
            }

            template <bool secure = false> 
            constexpr i128 &operator+= (i128 const &rhs) noexcept(!secure && !logical_error_detected) {
                return *this = this -> template operator+ <secure> (rhs); 
            }

            template <bool secure = false> 
            constexpr i128 operator- () const noexcept(!secure && !logical_error_detected) {
                // if (static_cast<std::array<u32, 4> const &>(*this) == (std::array<u32, 4>){0u, 0u, 0u, 0x80000000u, }) {
                //         throw false; 
                //     }
                // i128 result = i128()
                u128 result = ~static_cast<u128 const &>(*this); 
                ++result; 
                if constexpr (secure) {
                    if (static_cast<u128 const &>(*this) == result) {
                        throw false; 
                    }
                }
                return i128(result); 
            }

            template <bool secure = false> 
            constexpr i128 operator- (i128 const &rhs) const noexcept (!secure && !logical_error_detected) {
                return this -> template operator+ <secure> (
                    rhs . template operator- <secure> ()
                ); 
            }

            template <bool secure = false> 
            constexpr i128 &operator-= (i128 const &rhs) noexcept (!secure && !logical_error_detected) {
                return *this = this -> template operator- <secure> (rhs); 
            }

            // template <bool secure = false> 
            // constexpr i128 operator* (i128 cosnt &rhs) const noexcept (!secure && !logical_error_detected) {

            // }

            // template <bool secure = false> 
            constexpr i128 operator/ (i128 const &rhs) const {
                if (!rhs) {
                    throw exception::MatrixZeroDividedException("int128_t divided by zero. "); 
                }
                if (!*this) {
                    return 0; 
                }
                u128 dividend = 
                    this->is_negative() ? 
                    -*this : 
                    *this; 
                u128 divisor = 
                    rhs . is_negative() ? 
                    -rhs : 
                    rhs; 
                i128 result = (i128)(dividend / divisor); 
                if (this->is_negative() ^ rhs.is_negative()) 
                    result = -result; 
                return result; 
            }

    }; 
}