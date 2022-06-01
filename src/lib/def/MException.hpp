#pragma once 

#include "std.hpp" 

namespace matrix::exception {

    /** 
     * MatrixBaseException is the base exception for us to use. 
     * Every custom exception in Matrix Lib must extends it to keep a better throw-catch exception handling support. 
     */ 
    struct MatrixBaseException : public std::runtime_error {
        using std::runtime_error::runtime_error; 
    }; 

    /** 
     * MatrixAssertError is specifc exception class for assert tests. 
     * It would only happens when you meet a test error according to the rule. 
     */ 
    struct MatrixAssertError : public MatrixBaseException {
        using MatrixBaseException::MatrixBaseException; 
    };

    /** 
     * MatrixLogicalError only happens when you execute commands followed by some mathematical theorem or hypothesis but fails after checking the result constraints.  
     * 
     * Use 'NDEBUG' macro to skip all the logical examinations. 
     */ 
    struct MatrixLogicalError : public MatrixBaseException {
        using MatrixBaseException::MatrixBaseException;
    }; 

    /** 
     * This exception would appears when attempt to invoke safe_add / safe_mul series methods. 
     * 
     * Which means we want a correct number addition but fails! 
     */ 
    struct MatrixOverflowException : public MatrixBaseException {
        using MatrixBaseException::MatrixBaseException; 
    }; 
}

#define STRING_INNER(x) #x
#define STRING(x) STRING_INNER(x)

#define LASSERT(expression) \
    do { \
        auto &&v = (expression); \
        if (!v) { \
            throw matrix::exception::MatrixLogicalError( __FILE__ ":" STRING(__LINE__) " logical-correct bool expression {" #expression "} fails! " ); \
        } \
    } while (0); 

#define lassert LASSERT

#define BASSERT(expression) \
    do { \
        auto &&v = (expression); \
        if (!v) { \
            throw matrix::exception::MatrixAssertError( __FILE__ ":" STRING(__LINE__) " assert expression {" #expression "} fails! " ); \
        } \
    } while (0); 

#define bassert BASSERT 

namespace matrix::type_traits {
    template <typename T> 
    struct HasStdToString {
        private: 
            template <typename V = T, typename = std::void_t<decltype(std::to_string(std::declval<V>()))>> 
            std::true_type static test(nullptr_t ); 
            std::false_type static test(...); 
        public: 
            static bool constexpr value = decltype(test(nullptr))::value; 
    }; 

    template <typename T> 
    auto constexpr has_std_to_string = HasStdToString<T>::value; 
}

namespace matrix {
    template <typename T> 
    std::string stringizing (T &&v) {
        if constexpr (type_traits::has_std_to_string<T>) {
            return std::to_string(v); 
        } else {
            return to_string(v); 
        }
    }
}

#define BASSERT_EQ(lhs, rhs) \
    do { \
        auto &&l = (lhs); \
        auto &&r = (rhs); \
        if (l != r) { \
            std::string tmp = __FILE__ ":" STRING(__LINE__) " assert equation fails! lhs{" #lhs "} is '" + matrix::stringizing(l) \
                + "' but rhs{" #rhs "} is '" + matrix::stringizing(r) + "'. "; \
            throw matrix::exception::MatrixAssertError(std::move(tmp)); \
        } \
    } while (0); 

#define bassert_eq BASSERT_EQ