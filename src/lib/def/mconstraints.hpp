#pragma once 

#include "std.hpp"

#include "def/mexception.hpp"

namespace matrix::constraints {

    struct IsUpperBound {
        private: 
            bool m_bool; 
            static bool constexpr bool_default {true}; 
        public: 
            constexpr IsUpperBound(): m_bool(bool_default) {} 
            constexpr IsUpperBound(bool v) : m_bool(v) {} 
            constexpr operator bool() const noexcept {
                return m_bool; 
            }
    }; 

    template <typename T> 
    using ValueLimit = std::tuple<IsUpperBound, T, std::string_view>; 

    template <typename T, size_t v> 
    struct ValueBound : private std::array<ValueLimit<T>, v> {
        public: 
        ValueBound(): std::array<ValueLimit<T>, v>({{}}) {} 
        using ValueType = T; 
        static size_t constexpr LENGTH = v; 
        template <size_t i> 
        ValueLimit<T> &get() &{
            return std::get<i>(*this); 
        }
        template <size_t i> 
        ValueLimit<T> &&get() &&{
            return std::move(std::get<i>(*this));  
        }
        template <size_t i> 
        ValueLimit<T> const &get() const {
            return std::get<i>(*this); 
        }
    }; 

    namespace helper {
        template <typename T> 
        void debug(ValueLimit<T> const &self) {
            std::clog.setf(std::ios::boolalpha);
            std::clog << "Output: " << "(" << bool(std::get<0>(self)) << ", " << std::get<1>(self) << ", " << std::get<2>(self) << ")\n"; 
        }

        template <typename T, size_t l, size_t r, size_t v = 0> 
        void merge (ValueBound<T, l> &&lhs, ValueBound<T, r> &&rhs, ValueBound<T, l + r> &ans) {
            if constexpr (v < l) {
                ans.template get<v>() = std::move(lhs.template get<v>()); 
                merge<T, l, r, v+1>(std::move(lhs), std::move(rhs), ans); 
            } else if constexpr (v < l + r) {
                ans.template get<v>() = std::move(rhs.template get<v - l>()); 
                merge<T, l, r, v+1>(std::move(lhs), std::move(rhs), ans); 
            } 
        } 

        template <typename O, typename V, size_t len, size_t v = 0> 
        void check (O const &origin, ValueBound<V, len> const &to_check) {
            if constexpr (v < len) {
                auto &&condition_info = to_check.template get<v>(); 
                static_assert (std::is_same_v<std::decay_t<decltype(condition_info)>, ValueLimit<V>>); 
                if (std::get<IsUpperBound>(condition_info)) { 
                    // This value is a upper bound! 
                    if (origin >= std::get<V>(condition_info)) {
                        throw matrix::exception::MatrixAssertError {std::string(std::get<std::string_view>(condition_info)) += matrix::type_traits::Into<std::string>{}.into(std::get<V>(condition_info))}; 
                    }
                } else {
                    // This value is a down bound! 
                    if (origin < std::get<V>(condition_info)) {
                        throw matrix::exception::MatrixAssertError {std::string(std::get<std::string_view>(condition_info)) += matrix::type_traits::Into<std::string>{}.into(std::get<V>(condition_info))}; 
                    }
                }
                check<O, V, len, v + 1>(origin, to_check); 
            }
        }

    }

    template <typename V, size_t l, size_t r> 
    ValueBound<V, l + r> operator && (ValueBound<V, l> &&lhs, ValueBound<V, r> &&rhs) {
        ValueBound<V, l + r> ans; 
        helper::merge(std::move(lhs), std::move(rhs), ans); 
        return ans; 
    }

    template <typename V> 
    ValueBound<std::decay_t<V>, 1> with_upper_bound (V &&v, std::string_view sv) {
        ValueBound<std::decay_t<V>, 1> ans; 
        ans.template get<0>() = {IsUpperBound(true), std::forward<V>(v), sv}; 
        return ans; 
    }

    template <typename V> 
    ValueBound<std::decay_t<V>, 1> with_lower_bound (V &&v, std::string_view sv) {
        ValueBound<std::decay_t<V>, 1> ans; 
        ans.template get<0>() = {IsUpperBound(false), std::forward<V>(v), sv}; 
        return ans; 
    }

}

#define LOWER_BOUND(expression) matrix::constraints::with_lower_bound(expression, "Fails with the lower bound constraints in " __FILE__ ":" STRING(__LINE__) "  the lower bound:'" #expression "' is ")
#define UPPER_BOUND(expression) matrix::constraints::with_upper_bound(expression, "Fails with the upper bound constraints in " __FILE__ ":" STRING(__LINE__) "  the upper bound:'" #expression "' is ")

#define lower_bound LOWER_BOUND
#define upper_bound UPPER_BOUND 