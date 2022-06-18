#pragma once 

namespace matrix::type_traits {
    template <typename F, typename... Args, typename = decltype(std::declval<F>()(std::declval<Args&&>()...))> 
    std::true_type IsImpl(nullptr_t ); 

    template <typename...> 
    std::false_type IsImpl(...); 

    inline auto constexpr is_impl = [] (auto f) constexpr {
        return [] (auto &&... args) constexpr {
            return decltype(IsImpl<decltype(f), decltype(args)&&...>(nullptr)){}; 
        }; 
    }; 

    template <typename T> 
    std::string stringizing (T const &v) {

        auto constexpr to_string_trait_invoke = [](auto &&a) constexpr -> decltype(to_string(a)) {
            return to_string(a); 
        }; 
        auto constexpr std_to_string_output = [](auto &&a) constexpr -> decltype(std::to_string(a)) {
            return std::to_string(a); 
        }; 
        auto constexpr to_string_op_trait = [](auto &&a) constexpr -> decltype(std::string(a)) {
            return std::string(a); 
        }; 
        auto constexpr fetch_name_trait = [] (auto &&a) constexpr -> std::enable_if_t<std::is_same_v<decltype(a.name()), char const *>, std::string> {
            return std::string(a.name()); 
        }; 
        // auto constexpr complex_trait = [] (auto &&a) constexpr -> 
        
        if constexpr (decltype(type_traits::is_impl(to_string_op_trait)(v))::value) {
            return to_string_op_trait(v); 
        } else if constexpr (decltype(type_traits::is_impl(to_string_trait_invoke)(v))::value) {
            // std::clog << "Enter the first branch! \n"; 
            return to_string_trait_invoke(v); 
        } else if constexpr (decltype(type_traits::is_impl(std_to_string_output)(v))::value) {
            // std::clog << "Enter the second branch! \n"; 
            return std_to_string_output(v); 
        } else if constexpr (decltype(type_traits::is_impl(fetch_name_trait)(v))::value) {
            return fetch_name_trait(v); 
        } else if constexpr (requires {
            // v.real; 
            // v.imag; 
            { stringizing(v.real()) + " + " + stringizing(v.imag()) + "i" } -> std::string; 
        }) {
            return stringizing(v.real()) + " + " + stringizing(v.imag()) + "i"; 
        }
        return "[Not Realize String Trait]"; 
    }

    template <typename F> 
    struct From {
        template <typename T> 
        T from (F const &) const;  
    }; 

    template <typename T> 
    struct Into {
        template <typename F> 
        T into (F const &) const; 
    }; 

    template <typename F> 
    template <typename T> 
    T From<F>::from (F const &f) const {
        return Into<T>{}.into(f); 
    }

    template <> 
    template <typename F> 
    std::string Into<std::string>::into (F const &f) const {
        return stringizing(f); 
    }

    template <>
    template <> 
    std::string Into<std::string>::into (std::string const &f) const {
        return f; 
    }

    // template <typename Lhs, typename Rhs> 
    // bool is_nearly_same (Lhs const &, Rhs const &); 

}

namespace matrix::algorithm {
    template <typename NumberType> 
    bool is_nearly_zero(NumberType const &v) {
        constexpr auto abs_transform = [](auto const &v) -> std::enable_if_t<std::is_same_v<void, std::void_t<decltype(abs(v))>>, typename std::decay_t<decltype(v)>::value_type> {
            // return std::abs(v); 
            return abs(v); 
        }; 
        if constexpr (std::numeric_limits<std::decay_t<NumberType>>::is_integer) {
            return !v; 
        } else if constexpr (decltype(type_traits::is_impl(abs_transform)(v))::value) {
            // std::cout << __FILE__ << ":" << __LINE__ << '\n'; 
            // static_assert (std::is_same_v<decltype(abs_transform(v)), typename NumberType::value_type>); 
            return is_nearly_zero(abs_transform(v)); 
            // return v <= std::numeric_limits<std::decay_t<NumberType>>::epsilon() && 
            //     v >= - std::numeric_limits<std::decay_t<NumberType>>::epsilon(); 
        } else {
            return v <= 1e-6 && v >= -1e-6; 
        }
    }
}

namespace matrix::type_traits {
    template <typename Lhs, typename Rhs> 
    bool is_nearly_same(Lhs const &lhs, Rhs const &rhs) {
        if constexpr (!std::numeric_limits<Lhs>::is_integer || 
            !std::numeric_limits<Rhs>::is_integer) {
            return algorithm::is_nearly_zero(lhs - (Lhs)rhs); 
        } else {
            return lhs == rhs; 
        }
    }
}