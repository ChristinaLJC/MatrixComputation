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

#include "def/mtype_traits.hpp"
#include "def/mconstraints.hpp"

#define STRING_INNER(x) #x
#define STRING(x) STRING_INNER(x)

// Use NDEBUG to drop all logical assertion in program. 
#ifdef NDEBUG
#define LASSERT(e) \
    do { (void) sizeof (e); } while (0); 
#else 
#define LASSERT(expression) \
    do { \
        auto &&_v = (expression); \
        if (!_v) { \
            throw matrix::exception::MatrixLogicalError( __FILE__ ":" STRING(__LINE__) " logical-correct bool expression {" #expression "} fails! " ); \
        } \
    } while (0); 
#endif 

#define lassert LASSERT

#define BASSERT(expression) \
    do { \
        auto &&_v = (expression); \
        if (!_v) { \
            throw matrix::exception::MatrixAssertError( __FILE__ ":" STRING(__LINE__) " assert expression {" #expression "} fails! " ); \
        } \
    } while (0); 

#define bassert BASSERT 

#define BASSERT_EQ(lhs, rhs) \
    do { \
        auto &&_l = (lhs); \
        auto &&_r = (rhs); \
        if (_l != _r) { \
            std::string _tmp = __FILE__ ":" STRING(__LINE__) " assert equation fails! lhs{" #lhs "} is " + matrix::type_traits::From<std::decay_t<decltype(_l)>>{}.from<std::string>(_l) \
                + " but rhs{" #rhs "} is " + matrix::type_traits::From<std::decay_t<decltype(_r)>>{}.from<std::string>(_r) + ". "; \
            throw matrix::exception::MatrixAssertError(std::move(_tmp)); \
        } \
    } while (0); 

#define bassert_eq BASSERT_EQ

#define BASSERT_IN(lhs, rhs) \
    do { \
        auto &&_l = (lhs); \
        decltype(auto) _r = (rhs); \
        matrix::constraints::helper::check(_l, _r); \
    } while (0) 

#define bassert_in BASSERT_IN 