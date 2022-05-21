namespace Matrix::HighPrecision::uint128_t {

    namespace Helper {

        template <size_t val> 
        u32 div_u32_then_eq_recursively(u128 &self, u32 to_div) { 
            // using std::get; 
            // cache_val = (cache_val << 32) | get<val>(self); 
            // get<val>(self) = cache_val / to_div; 
            // cache_val %= to_div; 
            // if constexpr (val) {
            //     return div_u32_then_eq_recursively<val-1>(self, to_div, cache_val); 
            // } else {
            //     return cache_val; 
            // }
            return div_u32_recursively(self, self, to_div); 
        }

        template <size_t val> 
        u32 mod_u32_recursively(u128 const &self, u32 to_div, u64 cache_val = 0) {
            using std::get; 
            cache_val = (cache_val << 32) | get<val>(self); 
            cache_val %= to_div; 
            if constexpr (val) {
                return div_u32_then_eq_recursively<val-1>(self, to_div, cache_val); 
            } else {
                return cache_val; 
            }
        }

        template <size_t val> 
        u32 div_u32_recursively(u128 const &self, u128 &result, u32 to_div, u64 cache_val = 0) {
            using std::get; 
            cache_val = (cache_val << 32) | get<val>(self); 
            get<val>(result) = cache_val / to_div; 
            cache_val %= to_div; 
            if constexpr (val) 
                return div_u32_recursively<val-1>(self, result, to_div, cache_val); 
            else 
                return cache_val; 
        }

    }

    class uint128_t : public std::array<uint32_t, 4> {
    }; 

    [[maybe_unused]] u128 &div_u32_then_eq(u128 &self, u32 to_div, u32 *mod_ptr = nullptr) {
        auto mod_remain = div_u32_then_eq_recursively<3>(self, to_div); 
        if (mod_ptr) 
            *mod_ptr = mod_remain; 
        return self; 
    }

    u128 div_u32 (u128 const &self, u32 to_div, u32 *mod_ptr = nullptr) {
        u128 result; 
        auto mod_remain = div_u32_recursively<3>(self, result, to_div); 
        if (mod_ptr) 
            *mod_ptr = mod_remain; 
        return result; 
    }

    u32 mod_u32 (u128 const &self, u32 to_div) {
        return mod_u32_recursively<3>(self, to_div); 
    }
}