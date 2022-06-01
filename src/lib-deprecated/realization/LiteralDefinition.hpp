namespace Matrix::HighPrecision {
    
    template <char... numbers>
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
                            lassert (!is_capitalize.has_value() || is_capitalize.value(), "Attempt to parse a hexdecimal value but meets a error character: "s
                                                                                          + v + ". ");
                            is_capitalize = true;
                            v = v - 'A' + 10;
                            continue;
                        }
                        if (v >= 'a' && v <= 'f') {
                            lassert (!is_capitalize.has_value() || !is_capitalize.value(),
                                     "Attempt to parse a hexdecimal value but meets a error character: "s
                                     + v + ". ");
                            is_capitalize = false;
                            v = v - 'a' + 10;
                            continue;
                        }
                        if (v == '\'') {
                            v = 16;
                            continue;
                        }
                        lassert (false, "Attempt to parse a hexdecimal value but meets a error character: "s
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
                        lassert (false, "Attempt to parse a binary value, but meets an error character: "s +
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
                        lassert (false, "Attempt to parse a octal value, but meets an error character: "s +
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
                    lassert (false, "Meets a confusing char in literal: "s + v + ". ");
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