#pragma once 

namespace Matrix::HighPrecision {
    
    // to_string for uint128_t
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


    // to_string for PNumber
    inline std::string to_string (PNumber const &self) {
        PNumber val = self;
        std::vector<char> strs {};
        uint32_t wait;
        while (val.size() > 0) {
            div_u32_then_eq(val, 10, &wait);
            if (wait > 10) {
                using std::literals::operator""s;
                lassert (false, "Parse a high precision number meets a number out of domain: "s + std::to_string(wait));
            }
            strs.push_back(wait + '0');
        }
        if (!strs.size())
            strs.push_back('0');
        std::string result;
        result.reserve(strs.size());
        for (auto it = strs.crbegin(); it != strs.crend(); ++it) {
            result += *it;
        }
        return result;
    }

    inline std::string to_hex_string (PNumber const &self) {
        size_t effect_position = self.size();
        for (; effect_position && !self.at(effect_position-1); --effect_position) {
        }
        if (!effect_position) {
            return "0x0";
        }
        std::stringstream result;
        result << std::hex;
        result << "0x" << self.at(--effect_position);
        result << std::setfill('0');
        while (effect_position) {
            result << std::setw(8);
            result << self.at(--effect_position);
        }
        return result.str();
    }

    inline std::string to_bin_string(PNumber const &self) {
        size_t effect_position = self.size();
        for (; effect_position && !self.at(effect_position-1); --effect_position) {
        }
        if (!effect_position) {
            return "0b0";
        }
        std::stringstream result;
        result << "0b" << std::bitset<32>(self.at(--effect_position));
        result << std::setfill('0');
        while (effect_position) {
            result << std::setw(32);
            result << std::bitset<32>(self.at(--effect_position));
        }
        return result.str();
    }
}