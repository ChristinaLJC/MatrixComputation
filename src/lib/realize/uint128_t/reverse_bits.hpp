namespace matrix::inline prelude {

    namespace helper {
        template <typename F, size_t up_index> 
        void reverse_bits(u128 &self) noexcept (!logical_error_detected) {
            auto &&n = F{}.template operator()<up_index>(self); 
            n = ~n; 
            if constexpr (up_index) {
                reverse_bits<F, up_index - 1>(self); 
            }
        } 
    }

    u128 u128::operator~() const noexcept (!logical_error_detected) {
        u128 result = *this; 
        helper::reverse_bits<GetByIndex, 3>(result); 
        return result; 
    }
}