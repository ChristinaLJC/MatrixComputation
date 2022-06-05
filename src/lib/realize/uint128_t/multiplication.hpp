#pragma once 

namespace matrix::inline prelude {

    namespace helper {
        template <typename F, size_t lhs_index, size_t rhs_index, bool secure> 
        constexpr void multiply(u128 &ans, u128 const &lhs, u128 const &rhs, u64 cached = 0) noexcept (!secure && !logical_error_detected) {
            auto &&lhs_v = F{}.template operator()<lhs_index>(lhs); 
            auto &&rhs_v = F{}.template operator()<rhs_index>(rhs); 
            // std::clog << "multiply left value {}(i:{}) and right value {}(i:{}). \n"_format(lhs_v, lhs_index, rhs_v, rhs_index); 
            if constexpr (lhs_index + rhs_index > 3) {
                if constexpr (secure) {
                    if ((lhs_v && rhs_v)||cached) {
                        throw exception::MatrixOverflowException("Multiply between index {} and {} would meet a overflow. "_format(lhs_index, rhs_index)); 
                    }
                }
            } else {
                auto &&ans_v = F{}.template operator()<lhs_index + rhs_index>(ans); 
                cached += ans_v; 
                cached += (u64)lhs_v * rhs_v; 
                ans_v = cached; 
                cached >>= 32; 
                // std::clog << "Now ans is: {}\n"_format(ans); 
                if constexpr (rhs_index < 3) {
                    multiply<F, lhs_index, rhs_index + 1, secure>(ans, lhs, rhs, cached); 
                } else if constexpr(secure) {
                    if (cached) 
                        throw exception::MatrixOverflowException("Multiply between index {} and {} would meet a overflow. "_format(lhs_index, rhs_index)); 
                }
            }
        }

        template <typename F, size_t lhs_index, bool secure> 
        constexpr void multiply(u128 &ans, u128 const &lhs, u128 const &rhs) noexcept (!secure && !logical_error_detected) {
            multiply<F, lhs_index, 0, secure>(ans, lhs, rhs); 
            if constexpr (lhs_index < 3) {
                multiply<F, lhs_index + 1, secure>(ans, lhs, rhs); 
            }
        }

        // template <typename F, size_t index, bool secure> 
        // void specific_index_addition(u128 &self, u32 val) noexcept (!secure && !logical_error_detected) {
        // }
    }

    template <bool secure> 
    constexpr u128 u128::operator* (u128 const &rhs) const noexcept(!secure && !logical_error_detected) {
        u128 result; 
        helper::multiply<GetByIndex, 0, secure>(result, *this, rhs); 
        return result; 
    }

    template <bool secure> 
    constexpr u128 &u128::operator*= (u128 const &rhs) noexcept (!secure && !logical_error_detected) {
        u128 result = this->template operator*<secure>(rhs); 
        return *this = result; 
    }
}