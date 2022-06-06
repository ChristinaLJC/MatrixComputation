#pragma once 

#include "std.hpp" 

namespace matrix {
    inline namespace prelude {
        class uint128_t; 
        using u128 = uint128_t; 
        class uint128_t : private std::array<u32, 4> {
            public: 

                inline static size_t constexpr DECIMAL_LENGTH = 39; 

                constexpr uint128_t(): std::array<u32, 4>({}) {} 
                constexpr uint128_t(u32 v): std::array<u32, 4>({v}) {} 
                constexpr uint128_t(u64 v): std::array<u32, 4>({(u32)(v & 0xFFFFFFFF), (u32)(v >> 32)}) {} 
                constexpr uint128_t(u128 const &) = default; 

                template <bool secure = false> 
                constexpr u128 operator+ (u128 const &) const noexcept(!secure && !logical_error_detected);  

                template <bool secure = false, typename Other> 
                constexpr u128 operator+ (Other const &rhs) const noexcept (!secure && !logical_error_detected) {
                    return this->template operator+ <secure>(u128(rhs)); 
                }

                template <bool secure = false> 
                constexpr u128 &operator+= (u128 const &) noexcept (!secure && !logical_error_detected); 

                template <bool secure = false, typename Other> 
                constexpr u128 &operator+= (Other const &rhs) noexcept (!secure && !logical_error_detected) {
                    return this->template operator+= <secure>(u128(rhs)); 
                }

                template <bool secure = false> 
                constexpr u128 operator- (u128 const &) const noexcept(!secure && !logical_error_detected);  

                template <bool secure = false, typename Other> 
                constexpr u128 operator- (Other const &rhs) const noexcept (!secure && !logical_error_detected) {
                    return this->template operator- <secure>(u128(rhs)); 
                }

                template <bool secure = false> 
                constexpr u128 &operator-= (u128 const &) noexcept (!secure && !logical_error_detected); 

                template <bool secure = false, typename Other> 
                constexpr u128 &operator-= (Other const &rhs) noexcept (!secure && !logical_error_detected) {
                    return this->template operator-= <secure>(u128(rhs)); 
                }

                template <bool secure = false> 
                constexpr u128 operator* (u128 const &) const noexcept(!secure && !logical_error_detected);  

                template <bool secure = false, typename Other> 
                constexpr u128 operator* (Other const &rhs) const noexcept (!secure && !logical_error_detected) {
                    return this->template operator* <secure>(u128(rhs)); 
                }

                template <bool secure = false> 
                constexpr u128 &operator*= (u128 const &) noexcept (!secure && !logical_error_detected); 

                template <bool secure = false, typename Other> 
                constexpr u128 &operator*= (Other const &rhs) noexcept (!secure && !logical_error_detected) {
                    return this->template operator*= <secure>(u128(rhs)); 
                }

                constexpr inline u128 operator/ (u128 const &) const; 

                template <typename Other> 
                constexpr u128 operator/ (Other const &rhs) const {
                    return *this / u128(rhs); 
                }

                constexpr inline u128 &operator/= (u128 const &); 

                template <typename Other> 
                constexpr u128 &operator/= (Other const &rhs) {
                    return *this /= u128(rhs); 
                }

                constexpr inline u128 operator% (u128 const &) const; 
                constexpr inline u128 &operator%= (u128 const &) ; 

                template <typename Other> 
                constexpr u128 operator% (Other const &rhs) const {
                    return *this % u128(rhs); 
                }
                template <typename Other> 
                constexpr u128 &operator%= (Other const &rhs) {
                    return *this %= u128(rhs); 
                }
                // constexpr inline u128 operator-() const noexcept (!logical_error_detected); 

                constexpr inline u128 operator& (u128 const &) const noexcept (!logical_error_detected); 
                template <typename Other> 
                constexpr u128 operator& (Other const &rhs) const noexcept (!logical_error_detected) {
                    return *this & u128(rhs); 
                }
                constexpr inline u128 operator^ (u128 const &) const noexcept (!logical_error_detected); 
                template <typename Other> 
                constexpr u128 operator^ (Other const &rhs) const noexcept (!logical_error_detected) {
                    return *this ^ u128(rhs); 
                }
                constexpr inline u128 operator| (u128 const &) const noexcept (!logical_error_detected); 
                template <typename Other> 
                constexpr u128 operator| (Other const &rhs) const noexcept(!logical_error_detected) {
                    return *this | u128(rhs); 
                }

#define BUILD_OPERATOR_WITH_THEN_EQ(symbol) \
    constexpr inline u128 &operator symbol##= (u128 const &rhs) noexcept (!logical_error_detected) { \
        return *this = *this symbol rhs; \
    } \
    template <typename _Other> \
    constexpr u128 &operator symbol##= (_Other const &rhs) noexcept (!logical_error_detected) { \
        return *this symbol##= u128(rhs); \
    } 

                BUILD_OPERATOR_WITH_THEN_EQ(&)
                BUILD_OPERATOR_WITH_THEN_EQ(^)
                BUILD_OPERATOR_WITH_THEN_EQ(|)

#undef BUILD_OPERATOR_WITH_THEN_EQ

                constexpr inline u128 operator~() const noexcept (!logical_error_detected); 
                
                template <u32 > 
                constexpr u128 &divide_and_then_eq(u32 * = nullptr) noexcept(!logical_error_detected); 

                template <typename T> 
                constexpr T into() const; 

                template <> 
                std::string into() const {
                    return std::string(*this); 
                }

                constexpr inline operator bool() const noexcept; 

                template <bool secure = false> 
                constexpr u128 &operator++() noexcept (!secure && !logical_error_detected); 

                inline operator std::string() const noexcept(!logical_error_detected); 

                constexpr inline bool operator ==(u32 ) const noexcept; 
                constexpr inline bool operator ==(u64 ) const noexcept; 
                constexpr inline bool operator ==(u128 const &) const noexcept; 

                constexpr inline bool operator< (u128 const &) const noexcept; 
                constexpr inline bool operator<= (u128 const &) const noexcept; 
                constexpr bool operator> (u128 const &rhs) const noexcept {
                    return rhs < *this; 
                }

                constexpr bool operator>= (u128 const &rhs) const noexcept {
                    return rhs <= *this; 
                }

                template <typename T> 
                constexpr bool operator< (T const &rhs) const noexcept {
                    return *this < u128(rhs); 
                }
                
                template <typename T> 
                constexpr bool operator> (T const &rhs) const noexcept {
                    return *this > u128(rhs); 
                }

                template <typename T> 
                constexpr bool operator<= (T const &rhs) const noexcept {
                    return *this <= u128(rhs); 
                }

                template <typename T> 
                constexpr bool operator>= (T const &rhs) const noexcept {
                    return *this >= u128(rhs); 
                }

                template <bool secure = true> 
                constexpr operator u64() const noexcept (!secure && !logical_error_detected) {
                    if constexpr (secure) {
                        if (std::get<2>(*this) || std::get<3>(*this)) {
                            throw exception::MatrixBadCastException("Cast to uint64_t but it's out of range! "); 
                        }
                    }
                    return std::get<0>(*this) + ((u64)std::get<1>(*this) << 32); 
                }

                template <bool secure = true> 
                constexpr operator u32() const noexcept (!secure && !logical_error_detected) {
                    if constexpr (secure) {
                        if (std::get<1>(*this) || std::get<2>(*this) || std::get<3>(*this)) {
                            throw exception::MatrixBadCastException("Cast to uint32_t but it's out of range! "); 
                        }
                    }
                    return std::get<0>(*this); 
                }
            
            private: 
                struct GetByIndex {
                    template <size_t k> 
                    constexpr u32 &operator()(u128 &self) const noexcept {
                        return std::get<k>(self); 
                    }
                    template <size_t k> 
                    constexpr u32 const &operator()(u128 const &self) const noexcept {
                        return std::get<k>(self); 
                        // return this(const_cast<u128 &>(self)); 
                    }
                }; 
        }; 

        // Realize some symmetric operators: 

#define REALIZE4OP(symbol) \
    template <typename _Other> \
    constexpr u128 operator symbol (_Other const &lhs, u128 const &rhs) noexcept { \
        return u128(lhs) symbol rhs; \
    }
        // template <typename Other> 
        REALIZE4OP(+)
        REALIZE4OP(-)
        REALIZE4OP(*)
        REALIZE4OP(/)
        REALIZE4OP(^)
        REALIZE4OP(&)
        REALIZE4OP(|)

#undef REALIZE4OP


        template <char...> 
        constexpr u128 operator""_u128 () noexcept; 

        template <char...> 
        constexpr u128 operator""_uint128_t() noexcept; 
    }
}

// #include "realize/operator_u128/operator_plus.hpp"
// #include "realize/operator_u128/operator_cmp.hpp"

#include "realize/uint128_t/reverse_bits.hpp"
#include "realize/uint128_t/addition.hpp"
#include "realize/uint128_t/partial_eq.hpp"
#include "realize/uint128_t/type_cast.hpp"
#include "realize/uint128_t/total_order.hpp"
#include "realize/uint128_t/subtraction.hpp"
#include "realize/uint128_t/simple_division.hpp" 
#include "realize/uint128_t/stringlize.hpp"
#include "realize/uint128_t/multiplication.hpp"
#include "realize/uint128_t/division.hpp"
#include "realize/uint128_t/opbit.hpp"
#include "realize/uint128_t/modulus.hpp"
#include "realize/uint128_t/literal.hpp"