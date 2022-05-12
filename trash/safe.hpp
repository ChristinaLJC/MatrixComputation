// As we all know that, the exception safety is an important thing for us to deal with the problem! 
// Therefore, let's have a peek about the exception consideration! 

#include <exception> 
#include <stdexcept> 
#include <variant> 
#include <functional>

namespace matrix {

    inline namespace preposition {
        template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
        template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>; 
    }

    namespace exception {
        class MatrixException: public std::runtime_error {
            using std::runtime_error::runtime_error; 
        }; 
    }

    inline namespace preposition {
        
        template <typename T> 
        concept valid_t = !std::is_reference_v<T>; 

        template <typename T> 
        concept valid_option_t = valid_t<T> && !std::is_same_v<T, std::monostate>; 

        template <typename T> 
        concept error_t = valid_t<T> && std::is_base_of_v<std::exception, T>; 

        template <valid_option_t T> 
        class Option: public std::variant<std::monostate, T> {
            typedef T value_type; 
            using std::variant<std::monostate, T>::variant; 
        }; 

        template <valid_t T, error_t E> 
        class Result: public std::variant<T, E> {
            typedef T value_type; 
            typedef E error_type; 
            using std::variant<T, E>::variant;
            public: 
            auto try_what() {
                if (this->index() == 1)
                    return std::get<E>(*this).what(); 
                else 
                    return ""; 
            }
        }; 

        template <typename > 
        bool constexpr is_result_v = false; 
        
        template <valid_option_t T, error_t E> 
        bool constexpr is_result_v<Result<T, E>> = true; 
    }

    #define $(x) ({auto &&result = (x); static_assert (matrix::is_result_v<std::decay_t<decltype(result)>>); if (result.index() == 1) return std::move(std::get<1>(result)); std::move(std::get<0>(result));})

    namespace exception_deprecated_0507 {

        enum class unwrap_t {} unwrap;

        template <typename V, typename E> 
        V operator, (std::variant<V, E> &v, unwrap_t ) noexcept (false) {
            return std::get<V>(v); 
        }

        template <typename V, typename R> 
        std::variant<R, std::monostate> operator| (std::variant<V, std::monostate> &&src, std::function<R (V)> &&f) {
            return std::visit(overloaded {
                [](std::monostate ) {return std::monostate{}; }, 
                [&](V &origin) { return (f(origin)); } }, 
                src
            ); 
        } 

    }

    namespace exception_deprecated_0507 {

        template <typename T, typename V> 
        class Result: public std::variant<T, V> {
            T &unwrap() noexcept (false) {
                return std::get<T>(*this); 
            }
        }; 

        template <typename T> 
        class Option: public Result<T, std::monostate> {
            using Result<T, std::monostate>::Result; 
            T &unwrap() noexcept (false) {
                return std::get<T>(*this); 
            }
        }; 

        template <typename T, typename V> 
        T operator, (Result<T, V> &result, nullptr_t ) {
            return std::move(result.unwrap()); 
        }

        template <typename T, typename V> 
        Option<T> operator, (Result<T, V> &result, std::function<Option<T> (V)> deal_with) {
            return std::visit(overloaded {
                [] (T &val) {return std::move(val); }, 
                [&] (V &err) {return deal_with(err); }
            }, result);
        }
    }
}
