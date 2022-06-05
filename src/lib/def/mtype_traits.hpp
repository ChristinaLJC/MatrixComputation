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
        
        if constexpr (decltype(type_traits::is_impl(to_string_op_trait)(v))::value) {
            return to_string_op_trait(v); 
        } else if constexpr (decltype(type_traits::is_impl(to_string_trait_invoke)(v))::value) {
            // std::clog << "Enter the first branch! \n"; 
            return to_string_trait_invoke(v); 
        } else if constexpr (decltype(type_traits::is_impl(std_to_string_output)(v))::value) {
            // std::clog << "Enter the second branch! \n"; 
            return std_to_string_output(v); 
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

}