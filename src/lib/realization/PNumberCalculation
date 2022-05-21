namespace Matrix::HighPrecision {

    // calculation of high precision number
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
            lassert (false, "PNumber add a u32 but meets a overflow remain cache: "s + std::to_string(cache) + ". ");
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
            lassert (false, "PNumber multiply a u32 but meets a overflow remain cache: "s +
                            std::to_string(cache) + ". ");
        }
        return self;
    }

    inline PNumber &add_pn_then_eq(PNumber &self, PNumber const &rhs) {
        size_t i {};
        uint64_t cache {};
        if (self.size() <= rhs.size()) {
            for (; i < self.size(); ++i) {
                cache += self.at(i);
                cache += rhs.at(i);
                self.at(i) = cache;
                cache >>= 32;
            }
            for (; i < rhs.size(); ++i) {
                cache += rhs.at(i);
                self.push_back(cache);
                cache >>= 32;
            }
            if (cache) {
                lassert (cache <= 0xFFFFFFFF, "Cache shouldn't larger than 0xFFFFFFFF in addition pn operation. ");
                self.push_back(cache);
            }
            return self;
        } else {
            for (; i < rhs.size(); ++i) {
                cache += self.at(i);
                cache += rhs.at(i);
                self.at(i) = cache;
                cache >>= 32;
            }
            for (; i < self.size() && cache; ++i) {
                cache += self.at(i);
                self.at(i) = cache;
                cache >>= 32;
            }
            if (cache) {
                lassert (cache <= 0xFFFFFFFF, "Cache shouldn't larger than 0xFFFFFFFF in addition pn operation. ");
                self.push_back(cache);
            }
            return self;
        }
    }

    inline PNumber mul_pn (PNumber const &lhs, PNumber const &rhs) {
        PNumber result ;
        size_t lhs_top = lhs.size();
        size_t rhs_top = rhs.size();
        while (lhs_top && !lhs.at(lhs_top - 1)) {
            --lhs_top;
        }
        while (rhs_top && !rhs.at(rhs_top - 1)) {
            --rhs_top;
        }
        if (!lhs_top || !rhs_top) {
            return result;
        }
        result.reserve(lhs_top + rhs_top);
        size_t now_position = 0;
        size_t const plus = lhs_top + rhs_top;
        // Consider the plus data would get overflow?
        uint64_t cache{};
        for (; now_position < plus; ++now_position) {
            for (size_t k = ((now_position >= rhs_top) ?
                             (now_position - rhs_top + 1): (0)); k < std::min(now_position + 1, lhs_top); ++k) {
                using std::literals::operator""s;
                lassert (k >= 0, "k is larger than or equal to 0. ");
                lassert (k < lhs_top, "k is less than "s + std::to_string(lhs_top));
                lassert (now_position - k >= 0,
                         "now_position{"s + std::to_string(now_position)
                         + "} + k{" + std::to_string(k) + "} should larger than or equal to 0. ");
                lassert (now_position - k < rhs_top,
                         "now_position{"s + std::to_string(now_position)
                         + "} + k{" + std::to_string(k) + "} should less than rhs_top{"
                         + std::to_string(rhs_top) + "}. ");
                cache += (uint64_t ) lhs.at(k) * rhs.at(now_position - k);
            }
            result.push_back(cache);
            cache >>= 32;
        }
        if (cache) {
            lassert (cache <= 0xFFFFFFFF,
                     "Cache shouldn't be larger than uint32_t maximum! ");
            result.push_back(cache);
        }
        return result;
    }

    inline PNumber &mul_pn_then_eq(PNumber &self, PNumber const &other) {
        return self = mul_pn(self, other);
    }

    inline uint32_t mod_v_2 (PNumber const &self) {
        return (self.size() && (self.at(0) & 1)); 
    }

}