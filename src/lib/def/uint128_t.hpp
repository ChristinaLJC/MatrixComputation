#pragma once 

#include "std.hpp" 

namespace matrix {
    inline namespace prelude {
        class uint128_t; 
        using u128 = uint128_t; 
        class uint128_t : private std::array<u32, 4> {
            public: 

                inline static size_t constexpr DECIMAL_LENGTH = 39; 

                uint128_t(): std::array<u32, 4>({}) {} 
                uint128_t(u32 v): std::array<u32, 4>({v}) {} 
                uint128_t(u64 v): std::array<u32, 4>({(u32)(v % 0xFFFFFFFF), (u32)(v >> 32)}) {} 
                uint128_t(u128 const &) = default; 

                template <bool secure = false> 
                u128 operator+ (u128 const &) const noexcept(!secure && !logical_error_detected);  
                // template <bool secure = false> 
                // u128 operator+ (u64) const noexcept(!secure && !logical_error_detected); 
                // template <bool secure = false> 
                // u128 operator+ (u32) const noexcept(!secure && !logical_error_detected); 

                template <bool secure = false> 
                u128 &operator+= (u128 const &) noexcept (!secure && !logical_error_detected); 
                // template <bool secure = false> 
                // u128 operator+= (u64 ) const noexcept (!secure && !logical_error_detected); 
                // template <bool secure = false> 
                // u128 operator+= (u32 ) const noexcept (!secure && !logical_error_detected); 


                template <bool secure = false> 
                u128 operator- (u128 const &) const noexcept(!secure && !logical_error_detected);  
                // template <bool secure = false> 
                // u128 operator- (u64) const noexcept(!secure && !logical_error_detected); 
                // template <bool secure = false> 
                // u128 operator- (u32) const noexcept(!secure && !logical_error_detected); 

                template <bool secure = false> 
                u128 operator* (u128 const &) const noexcept(!secure && !logical_error_detected);  
                // template <bool secure = false> 
                // u128 operator* (u64) const noexcept(!secure && !logical_error_detected);
                // template <bool secure = false> 
                // u128 operator* (u32) const noexcept(!secure && !logical_error_detected);
                template <bool secure = true> 
                u128 operator/ (u128 const &) const noexcept(!secure && !logical_error_detected);  
                // template <bool secure = true> 
                // u128 operator/ (u64) const noexcept(!secure && !logical_error_detected);
                // template <bool secure = true> 
                // u128 operator/ (u32) const noexcept(!secure && !logical_error_detected);
                u128 operator% (u128) const noexcept (!logical_error_detected); 
                // u64 operator% (u64) const noexcept(!logical_error_detected); 
                // u32 operator% (u32) const noexcept(!logical_error_detected); 

                u128 operator~() const noexcept (!logical_error_detected); 
                
                /** 
                 * Divide a uint32_t value and get the quotient and remainder. 
                 *
                 * Not check of the divisor is zero! 
                 */ 
                u128 &divide_and_equal(u32, u32 * = nullptr) noexcept(!logical_error_detected);

                template <u32 > 
                u128 &divide_and_equal(u32 *) noexcept(!logical_error_detected); 

                template <typename T> 
                T into() const; 

                operator bool() const noexcept; 

                operator std::string() const noexcept(!logical_error_detected); 

                // bool operator ==(u32 ) const noexcept; 
                // bool operator ==(u64 ) const noexcept; 
                bool operator ==(u128 const &) const noexcept; 

            private: 
                struct GetByIndex {
                    template <size_t k> 
                    u32 &operator()(u128 &self) const noexcept {
                        return std::get<k>(self); 
                    }
                    template <size_t k> 
                    u32 const &operator()(u128 const &self) const noexcept {
                        return std::get<k>(self); 
                        // return this(const_cast<u128 &>(self)); 
                    }
                }; 
        }; 
    }
}

// #include "realize/operator_u128/operator_plus.hpp"
// #include "realize/operator_u128/operator_cmp.hpp"

#include "realize/u128/reverse_bits.hpp"
#include "realize/u128/addition.hpp"
#include "realize/u128/partial_eq.hpp"
#include "realize/u128/type_cast.hpp"