#include "std.hpp"

namespace Matrix {
    inline namespace Prelude {

        enum class PNSymbol: unsigned char {
            POSITIVE, NEGATIVE, ZERO
        };

        typedef std::vector<uint32_t> PNumber; 

        PNumber add(PNumber const &, PNumber const &); 
        std::pair<PNumber, PNSymbol> minus(PNumber const &, PNumber const &); 
        PNumber multi(PNumber const &, PNumber const &); 
        std::pair<PNumber, PNumber> div(PNumber const &, PNumber const &); 

        PNumber &div_u32_then_eq(PNumber &, uint32_t, uint32_t *); 
        PNumber &add_u32_then_eq(PNumber &, uint32_t); 
        PNumber &mul_u32_then_eq(PNumber &, uint32_t); 

        std::string to_string(PNumber const &); 
        std::string to_hex_string(PNumber const &); 

        inline PNumber &div_u32_then_eq(PNumber &self, uint32_t to_div, uint32_t *remainder) {
            auto length = self.size(); 
            uint64_t cache {}; 
            bool can_pop = true; 
            for (auto k = length; k; --k) {
                cache = (cache << 32) + self.at(k-1); 
                self.at(k-1) = cache / to_div; 
                if (can_pop) {
                    if (self.at(k-1)) {
                        can_pop = false; 
                    } else {
                        self.pop_back(); 
                    }
                } 
                cache %= to_div;
            }
            if (remainder)
                *remainder = cache;  
            return self; 
        }

        inline PNumber &add_u32_then_eq(PNumber &self, uint32_t to_add) {
            if (self.size() == 0) {
                if (to_add)
                    self.push_back(to_add); 
                return self; 
            }
            uint64_t cache {to_add};
            for (auto &&v: self) {
                cache += v; 
                v = cache & 0xFFFFFFFF; 
                cache >>= 32; 
                if (!cache)     
                    break; 
            }
            if (cache) 
                self.push_back(cache); 
            if (cache >> 32) {
                using std::literals::operator""s; 
                throw std::logic_error("PNumber add a u32 but meets a overflow remain cache: "s + std::to_string(cache) + ". ");
            }
            return self; 
        }

        inline PNumber &mul_u32_then_eq(PNumber &self, uint32_t to_multiply) {
            if (self.size() == 0) 
                return self; 
            if (to_multiply == 0) {
                self.clear(); 
                return self; 
            }
            uint64_t cache {}; 
            for (auto &&v: self) {
                cache += (uint64_t ) v * to_multiply; 
                v = cache & 0xFFFFFFFF; 
                cache >>= 32; 
            }
            if (cache) 
                self.push_back(cache); 
            if (cache >> 32) {
                using std::literals::operator""s; 
                throw std::logic_error("PNumber multiply a u32 but meets a overflow remain cache: "s + 
                    std::to_string(cache) + ". ");
            }
            return self; 
        }

        inline std::string to_string (PNumber const &self) {
            PNumber val = self; 
            std::vector<char> strs {}; 
            uint32_t wait; 
            while (val.size() > 0) {
                div_u32_then_eq(val, 10, &wait); 
                if (wait > 10) {
                    using std::literals::operator""s; 
                    throw std::logic_error("Parse a high precision number meets a number out of domain: "s + std::to_string(wait)); 
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

        template <char ...numbers> 
        inline PNumber operator "" _pn () {
            using std::literals::operator""s; 
            auto ar = std::array<char, sizeof...(numbers)> {numbers...};
            PNumber result; 
            result.reserve(1 + sizeof...(numbers) / 9);
            // Do a security check for the value. 
            if (ar.size() >= 2 && ar.at(0) == '0') {
                switch (ar.at(1)) {
                    case 'x': 
                    case 'X': 
                    {
                        size_t len_index = 0; 
                        std::optional<bool> is_capitalize; 
                        for (auto &&v: ar) {
                            if (len_index++ < 2) 
                                continue; 
                            if (v >= '0' && v <='9') {
                                v = v - '0'; 
                                continue; 
                            }
                            if (v >= 'A' && v <= 'F') {
                                if (is_capitalize.has_value() && !is_capitalize.value()) {
                                    throw std::logic_error("Attempt to parse a hexdecimal value but meets a error character: "s 
                                        + v + ". ");
                                }
                                is_capitalize = true; 
                                v = v - 'A' + 10; 
                                continue; 
                            }
                            if (v >= 'a' && v <= 'f') {
                                if (is_capitalize.has_value() && is_capitalize.value()) {
                                    throw std::logic_error("Attempt to parse a hexdecimal value but meets a error character: "s 
                                        + v + ". "); 
                                }
                                is_capitalize = false; 
                                v = v - 'a' + 10; 
                                continue; 
                            }
                            if (v == '\'') {
                                v = 16; 
                                continue; 
                            }
                            throw std::logic_error("Attempt to parse a hexdecimal value but meets a error character: "s 
                                + v + ". ");
                        }

                        len_index = 0; 
                        for (auto &&v: ar) {
                            if (len_index++ < 2) 
                                continue;
                            if (v >= 0 && v < 16) {
                                mul_u32_then_eq(result, 16); 
                                add_u32_then_eq(result, v);
                            }
                        }
                    }
                    break; 
                    case 'b': 
                    case 'B': 
                    {
                        size_t len_index = 0; 
                        for (auto &&v: ar) {
                            if (len_index ++ < 2) 
                                continue; 
                            if (v == '0' || v == '1') {
                                v = v - '0'; 
                                continue; 
                            }
                            if (v == '\'') {
                                v = 2; 
                                continue; 
                            }
                            throw std::logic_error("Attempt to parse a binary value, but meets an error character: "s + 
                                v + ". ");
                        }

                        len_index = 0; 
                        for (auto &&v: ar) {
                            if (len_index ++ < 2) 
                                continue; 
                            if (v == 0 || v == 1) {
                                mul_u32_then_eq(result, 2); 
                                add_u32_then_eq(result, v);
                            }
                        }
                    }
                    break; 
                    default: 
                    {
                        bool flag = false; 
                        for (auto &&v: ar) {
                            if (!flag) {
                                flag = true; continue; 
                            }
                            if (v >= '0' && v < '8') {
                                v = v - '0'; 
                                continue; 
                            }
                            if (v == '\'') {
                                v = 8; 
                                continue; 
                            }
                            throw std::logic_error("Attempt to parse a octal value, but meets an error character: "s + 
                                v + ". ");
                        }
                        flag = false; 
                        for (auto &&v: ar) {
                            if (!flag) {
                                flag = true; 
                                continue;  
                            }
                            if (v >= 0 && v < 8) {
                                mul_u32_then_eq(result, 8); 
                                add_u32_then_eq(result, v);
                            }
                        }
                    }
                }
            } else {

                for (auto &&v: ar) {
                    if (!(v >= '0' && v <= '9')) {
                        if (v == '\'') {
                            v = 10; 
                            continue; 
                        }
                        throw std::logic_error("Meets a confusing char in literal: "s + v + ". "); 
                    } else {
                        v = v - '0'; 
                    }
                }

                for (auto &&v: ar) {
                    if (v >= 0 && v < 10) {
                        mul_u32_then_eq(result, 10); 
                        add_u32_then_eq(result, v); 
                    }
                }
            }

            return result; 
        }
    }
}