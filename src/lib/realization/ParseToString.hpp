#pragma once 

namespace Matrix::BigNumber {
    std::string to_string(uint128_t const &val) {
        std::array<char, 30> cache; 
        size_t index {}; 
        u128 tmp = val; 
        while (tmp) {
            // cache[index] = tmp % 10
            u32 remain; 
            div_u32_then_eq(tmp, 10, &remain); 
            cache.at(index++) = remain + '0'; 
        }
        size_t start {}; 
        while (start + 1 < index) {
            std::swap(cache.at(start++), cache.at(index---1)); 
        }
        return std::string (reinterpret_cast<char*>(&cache)); 
    }
}