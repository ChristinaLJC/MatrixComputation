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

        std::string to_string(PNumber const &); 

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
    }
}