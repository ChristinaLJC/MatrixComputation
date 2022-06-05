#pragma once 

namespace matrix::inline prelude {

    namespace helper {

        template <typename F, size_t left_shift, size_t index = 3>  
        void left_shift_recursively(u128 &self) noexcept {
            // std::clog << "Repeat line:" STRING(__LINE__) "\n"; 
            if constexpr (index >= left_shift) {
                F{}.template operator()<index>(self) = F{}.template operator()<index - left_shift>(self); 
            } else {
                F{}.template operator()<index>(self) = 0u; 
            }
            if constexpr (index > 0) 
                left_shift_recursively<F, left_shift, index - 1>(self); 
        }

        template <typename F, size_t left_shift_v> 
        void left_shift(u128 &self) noexcept {
            // std::clog << "Before leftshift {} with step {}. \n"_format(self, left_shift_v); 
            left_shift_recursively<F, left_shift_v>(self); 
            // std::clog << "After: {}.\n"_format(self); 
        }

        template <typename F, size_t high_val> 
        u32 divide_with_same_level(u128 &lhs, u128 const &rhs) noexcept(!logical_error_detected) {
            lassert (F{}.template operator()<high_val>(rhs)); 
            u32 attempt_val = ({
                u64 cached  = F{}.template operator()<high_val>(lhs); 
                if constexpr (high_val < 3) 
                    cached |= (u64)(F{}.template operator()<high_val + 1>(lhs)) << 32; 
                cached /= F{}.template operator()<high_val>(rhs); 
                lassert (cached <= 0xFFFFFFFF); 
                cached; 
            }); 
            std::clog << "lhs = {}, rhs = {}, so the directly attempt value init = {}\n"_format(lhs, rhs, attempt_val); 
            if (!attempt_val)
                return 0; 
            --attempt_val; 
            u128 attempt_subtract = rhs.template operator*<logical_error_detected>(attempt_val); 
            lhs -= attempt_subtract;
            std::clog << "then, lhs = {}, rhs = {}, so the directly attempt value init = {}, attempt_subtract: {}\n"_format(lhs, rhs, attempt_val, 
                attempt_subtract); 
            // todo: optimize this operation for a better solution. 
            while (lhs >= rhs) {
                // std::clog << "lhs = {}, rhs = {}, attempt_val = {}. \n"_format(lhs, rhs, attempt_val); 
                ++attempt_val; 
                lhs -= rhs; 
            }
            return attempt_val; 
        }

        template <typename F, size_t i> 
        u32 divide_with_same_level_recursively (u128 &lhs, u128 const &rhs) noexcept(!logical_error_detected) {
            if (F{}.template operator()<i>(rhs)) {
                return divide_with_same_level<F, i>(lhs, rhs); 
            } else if constexpr (i) {
                return divide_with_same_level_recursively<F, i-1>(lhs, rhs); 
            } else {
                lassert (false); 
                abort(); 
            }
        }

        template <typename F, size_t left_shift_possible = 3> 
        void divide(u128 &ans, u128 &lhs, u128 const &rhs) noexcept (!logical_error_detected) {
            if constexpr (left_shift_possible) {
                if (!F{}.template operator()<3>(rhs)) {
                    divide<F, left_shift_possible - 1>(ans, lhs, 
                    ({
                        u128 tmp = rhs; 
                        left_shift<F, 1>(tmp); 
                        tmp; 
                    })); 
                }
            }
            auto lhs_str = "{}"_format(lhs); 
            auto rhs_str = "{}"_format(rhs); 
            auto &&result = divide_with_same_level_recursively<F, 3>(lhs, rhs); 
            std::clog << "divide from {} / {}, the result: {}\n"_format(lhs_str, rhs_str, result); 
            F{}.template operator()<3 - left_shift_possible>(ans) = result; 
        }
    }

    u128 u128::operator/(u128 const &rhs) const {
        u128 result; 
        u128 cached = *this; 
        if (!rhs) {
            throw false; 
        }
        helper::divide<GetByIndex>(result, cached, rhs); 
        return result; 
    }

    u128 &u128::operator/= (u128 const &rhs) {
        u128 ans = *this / rhs; 
        return *this = ans; 
    }
}