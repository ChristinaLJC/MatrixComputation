#pragma once 

#include "cache/std.hpp"

namespace Matrix::Exception {

    /** 
     * MatrixBaseException is the base exception for us to use. 
     * Every custom exception in Matrix Lib must extends it to keep a better throw-catch exception handling support. 
     */ 
    struct MatrixBaseException : public std::runtime_error {
        using std::runtime_error::runtime_error; 
        /** 
         * what_as_string method: 
         * The core method to describes the error situations. 
         * Use this method you can directly get a string and at the same time, obtain the total life cycle of it. 
         * This method is determined as pure virtual, which means we have to describes the achievemnet of it!. 
         */ 
        virtual std::string what_as_string() const = 0; 
    }; 

    /** 
     * MatrixInstanceBaseException is similar as MatrisBaseException. 
     * But the only different is that you can use MatrixInstanceBaseException to avoid the redefine virutal method. 
     * It's quitely easier to use in almost frequently situations. 
     * No need to describes it as a good job. 
     */ 
    struct MatrixInstanceBaseException : public MatrixBaseException {
        using MatrixBaseException::MatrixBaseException; 

        std::string what_as_string() const override {
            return what(); 
        }
    }; 

    /** 
     * MatrixAssertError is specifc exception class for assert tests. 
     * It would only happens when you meet a test error according to the rule. 
     */ 
    struct MatrixAssertError : public MatrixBaseException {
        using MatrixBaseException::MatrixBaseException; 
    };

    /** 
     * MatrixLogicalError only happens when you execute commands followed by some mathematical theorem or hypothesis. 
     * Use 'RELEASE' macro to skip all the logical examinations. 
     */ 
    struct MatrixLogicalError : public MatrixBaseException {
        using MatrixBaseException::MatrixBaseException;
    }; 

    /** 
     * This exception would appears when attempt to invoke safe_add / safe_mul series methods. 
     * Especially, sometimes it's obviously, 
     */ 
    struct MatrixOverflowException : public MatrixBaseException {
        using MatrixBaseException::MatrixBaseException; 
    }; 

}