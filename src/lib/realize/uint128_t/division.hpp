#pragma once 

namespace matrix::inline prelude {

    namespace helper {

        template <typename F, size_t left_shift, size_t index = 3>  
        constexpr void left_shift_recursively(u128 &self) noexcept {
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
        constexpr void left_shift(u128 &self) noexcept {
            // std::clog << "Before leftshift {} with step {}. \n"_format(self, left_shift_v); 
            left_shift_recursively<F, left_shift_v>(self); 
            // std::clog << "After: {}.\n"_format(self); 
        }

        template <typename F, size_t high_val> 
        constexpr u32 divide_with_same_level(u128 &lhs, u128 const &rhs) noexcept(!logical_error_detected) {
            // std::clog << __FUNCTION__ << " call, high-val = " << high_val << '\n'; 
            lassert (F{}.template operator()<high_val>(rhs)); 
            u32 attempt_val = ({
                u64 cached  = F{}.template operator()<high_val>(lhs); 
                if constexpr (high_val < 3) 
                    cached |= (u64)(F{}.template operator()<high_val + 1>(lhs)) << 32; 
                // if (F{}.template operator()<high_val>(rhs) != 0xFFFFFFFF) 
                // lassert (F{}.template operator()<high_val>(rhs) != 0xFFFFFFFF) 
                
                // It's a bad solution for it. 
                // cached /= (u64)F{}.template operator()<high_val>(rhs) + 1; 

                cached /= (u64)F{}.template operator()<high_val>(rhs); 
                lassert (cached <= 0xFFFFFFFF); 

                cached; 
            }); 
            // std::clog << "The attempt val now is: " << attempt_val << '\n'; 
            // std::clog << "lhs = {}, rhs = {}, so the directly attempt value init = {}\n"_format(lhs, rhs, attempt_val); 
            // std::clog << "high-val: " << high_val << '\n'; 
            
            // Obviously, it means it's even not enough for you to deal with it! 
            if (!attempt_val)
                return 0; 
            --attempt_val; 

            u128 attempt_subtract = rhs.template operator*<logical_error_detected>(attempt_val); 
            lassert (lhs >= rhs); 
            while (lhs < attempt_subtract) {
                --attempt_val; 
                attempt_subtract -= rhs; 
            }
            // lassert (lhs >= attempt_subtract); 
            lhs -= attempt_subtract;
            // std::clog << "then, lhs = {}, rhs = {}, so the directly attempt value init = {}, attempt_subtract: {}\n"_format(lhs, rhs, attempt_val, 
                // attempt_subtract); 
            // todo: optimize this operation for a better solution. 
            while (lhs >= rhs) {
                // std::clog << "lhs = {}, rhs = {}, attempt_val = {}. \n"_format(lhs, rhs, attempt_val); 
                ++attempt_val; 
                // std::clog << "attempt-val: " << attempt_val << '\n'; 
                lhs -= rhs; 
            }
            return attempt_val; 
        }

        template <typename F, size_t i> 
        constexpr u32 divide_with_same_level_recursively (u128 &lhs, u128 const &rhs) {
            if (F{}.template operator()<i>(rhs)) {
                return divide_with_same_level<F, i>(lhs, rhs); 
            } else if constexpr (i) {
                return divide_with_same_level_recursively<F, i-1>(lhs, rhs); 
            } else {
                // throw exception::MatrixZeroDividedException("Value divided by zero. "); 
                abort(); 
            }
        }

        template <typename F, size_t left_shift_possible = 3> 
        constexpr void divide(u128 &ans, u128 &lhs, u128 const &rhs) {
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
            // auto lhs_str = "{}"_format(lhs); 
            // auto rhs_str = "{}"_format(rhs); 
            // std::clog << "left_shift_possible: " << left_shift_possible << "\n"; 
            auto &&result = divide_with_same_level_recursively<F, 3>(lhs, rhs); 
            // std::clog << "divide from {} / {}, the result: {}\n"_format(lhs_str, rhs_str, result); 
            F{}.template operator()<3 - left_shift_possible>(ans) = result; 
        }
    }

    constexpr u128 u128::operator/(u128 const &rhs) const {
        u128 result; 
        u128 cached = *this; 
        if (!rhs) {
            throw exception::MatrixZeroDividedException ("uint128_t divided by zero. "); 
        }
        helper::divide<GetByIndex>(result, cached, rhs); 
        return result; 
    }

    constexpr u128 &u128::operator/= (u128 const &rhs) {
        // u128 ans = *this / rhs; 
        return *this = *this / rhs; 
    }
}