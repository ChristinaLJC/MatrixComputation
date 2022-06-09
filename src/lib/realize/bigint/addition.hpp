#pragma once 

namespace matrix::inline prelude::big_integer {

    using RawInt = std::vector<u32>; 

    RawInt &expand(RawInt &self, size_t len) {
        bool is_negative = self.back() & 0x8000'0000u; 
        self.reserve(len); 
        for (size_t i = self.size(); i < len; ++i) 
            self.push_back(is_negative ? 0xffff'ffffu : 0u); 
        return self; 
    }

    RawInt &trim(RawInt &self) {
        bool is_negative = self.back() & 0x8000'0000u; 
        if (is_negative) {
            if (self.size() > 1 && self[self.size() - 1] == 0xffff'ffffu && (self[self.size() - 2] & 0x8000'0000u)) {
                self.pop_back(); 
            }
        } else {
            if (self.size() > 1 && self.back() == 0u && !(self[self.size() - 2] & 0x8000'0000u)) {
                self.pop_back(); 
            }
        }
    }

    RawInt add(RawInt const &lhs, RawInt const &rhs) {
        RawInt ans = lhs; 
        add_then_eq(ans, rhs); 
        return ans;  
    }

    void add_then_eq(RawInt &lhs, RawInt const &rhs) {
        // if (lhs.size() < rhs.size() + 1)
        lassert (lhs.size() == rhs.size()); 
        lhs.reserve(rhs.size() + 1); 
        u64 cached{}; 
        size_t index {}; 
        for (size_t minimum = std::min(lhs.size(), rhs.size()); index < minimum; ++index) {
            cached += lhs[index]; 
            cached += rhs[index]; 
            lhs[index] = cached; 
            cached >>= 32; 
        }
        if (index < lhs.size()) {
            lassert (index == rhs.size()); 
            for (size_t maximum = lhs.size(); cached && index < maximum; ++index) {
                cached += lhs[index];
                lhs[index] = cached; 
                cached >>= 32; 
            }
        } else if (index < rhs.size()) {
            lassert (index == lhs.size());
            for (size_t maximum = rhs.size(); index < maximum; ++index) {
                cached += rhs[index]; 
                lhs.push_back(cached); 
                cached >>= 32; 
            }
        } 
        if (cached) {
            lassert (index >= lhs.size()); 
            lhs.push_back(cached); 
            // Cache would make a two-distance-carrying. 
            lassert (cached <= 0xffffffffu); 

            // Protect the positive rule. 
            if (cached & 0x8000'0000u) {
                lhs.push_back(0); 
            }
        }
    }
}