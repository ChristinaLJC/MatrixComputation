namespace matrix::inline prelude {

    namespace helper {
        template <typename F, typename K, size_t up_bound = 3>
        constexpr void op_bit(u128 &ans, u128 const &lhs, u128 const &rhs) {
            K{}(F{}.template operator()<up_bound>(ans), 
                F{}.template operator()<up_bound>(lhs), 
                F{}.template operator()<up_bound>(rhs)); 
            if constexpr (up_bound) {
                op_bit<F, K, up_bound - 1>(ans, lhs, rhs); 
            }
        }
    }

    constexpr u128 u128::operator& (u128 const &rhs) const noexcept (!logical_error_detected) {
        constexpr auto and_op = [](auto &a, auto const &b, auto const &c) {
            a = b & c; 
        }; 
        u128 ans; 
        helper::op_bit<GetByIndex, decltype(and_op)>(ans, *this, rhs);  
        return ans; 
    }
    constexpr u128 u128::operator^ (u128 const &rhs) const noexcept (!logical_error_detected) {
        constexpr auto xor_op = [](auto &a, auto const &b, auto const &c) {
            a = b ^ c; 
        }; 
        u128 ans; 
        helper::op_bit<GetByIndex, decltype(xor_op)>(ans, *this, rhs); 
        return ans; 
    }
    constexpr u128 u128::operator| (u128 const &rhs) const noexcept (!logical_error_detected) {
        constexpr auto or_op = [](auto &a, auto const &b, auto const &c) {
            a = b | c; 
        }; 
        u128 ans; 
        helper::op_bit<GetByIndex, decltype(or_op)>(ans, *this, rhs); 
        return ans; 
    }
}