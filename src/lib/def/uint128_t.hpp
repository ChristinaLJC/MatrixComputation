#pragma once 

#include "std.hpp" 

namespace matrix {
    inline namespace prelude {
        class uint128_t; 
        using u128 = uint128_t; 
        class uint128_t : private std::array<u32, 4> {
            public: 

                inline static size_t constexpr DECIMAL_LENGTH = 39; 

                template <bool secure = false> 
                u128 operator+ (u128 const &) const noexcept(!secure && !logical_error_detected);  
                template <bool secure = false> 
                u128 operator+ (u64) const noexcept(!secure && !logical_error_detected); 
                template <bool secure = false> 
                u128 operator+ (u32) const noexcept(!secure && !logical_error_detected); 
                template <bool secure = false> 
                u128 operator- (u128 const &) const noexcept(!secure && !logical_error_detected);  
                template <bool secure = false> 
                u128 operator- (u64) const noexcept(!secure && !logical_error_detected); 
                template <bool secure = false> 
                u128 operator- (u32) const noexcept(!secure && !logical_error_detected); 
                template <bool secure = false> 
                u128 operator* (u128 const &) const noexcept(!secure && !logical_error_detected);  
                template <bool secure = false> 
                u128 operator* (u64) const noexcept(!secure && !logical_error_detected);
                template <bool secure = false> 
                u128 operator* (u32) const noexcept(!secure && !logical_error_detected);
                template <bool secure = true> 
                u128 operator/ (u128 const &) const noexcept(!secure && !logical_error_detected);  
                template <bool secure = true> 
                u128 operator/ (u64) const noexcept(!secure && !logical_error_detected);
                template <bool secure = true> 
                u128 operator/ (u32) const noexcept(!secure && !logical_error_detected);
                u128 operator% (u128) const noexcept (!logical_error_detected); 
                u64 operator% (u64) const noexcept(!logical_error_detected); 
                u32 operator% (u32) const noexcept(!logical_error_detected); 
                
                /** 
                 * Divide a uint32_t value and get the quotient and remainder. 
                 *
                 * Not check of the divisor is zero! 
                 */ 
                u128 &divide_and_equal(u32, u32 * = nullptr) noexcept(!logical_error_detected);
                template <typename T> 
                T into() const; 
            private: 
                struct GetByIndex {
                    template <size_t k> 
                    u32 &operator()(u128 &self) const noexcept {
                        return std::get<k>(self); 
                    }
                    template <size_t k> 
                    u32 const &operator()(u128 const &self) const noexcept {
                        return std::get<k>(self); 
                    }
                }; 
        }; 
    }
}

#include "realize/operator_u128.hpp"