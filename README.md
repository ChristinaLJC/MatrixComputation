# MatrixComputation
a lib for Matrix Computation, from CS205



## Library Support

### Integral Type Support

In this library, except the basic integral types, we also define some other arithmetic types to better support the calculations. 

#### uint128_t

#### uint_t

#### integral_t

### Assertion Support

As you know that, assertion is a significantly important component in our developing. A good assertion support can effectively help us DEBUG the logical errors and other typos. 

Therefore, we now define three types branch assertions for convenience when using in the testing framework. 



#### bassert

The command `bassert` is a simple assertion command for us to test the assertion is correct or not at this moment. 

It just simply receive only one bool expression and examine this value is `true` or not. 



#### bassert_eq

The command `bassert_eq` seems like the combination function invocations `bassert (lhs_exp == rhs_exp)`. 

However, we determine to add this extra assert statement not because we're boring but we specify this assertion condition. 

There are 2 important reasons for us to do it: 

1. This situation is frequently happening so that a special grammar for it is important. 
2. Determining a small case to implement is beneficial to us to have a deeper peek of the failure situation when it happens than the original assert statement. 



#### bassert_in

The command `bassert_in` is an assert statement to make sure some value in a bound! 

Of course this assert statement would base on the comparing operators. 

The limitation about the data type is quite loose, which means if you can make sure the comparison about them, you can use this command smoothly! 



## Suggested Reference

- https://docs.opencv.org/3.4/d3/d63/classcv_1_1Mat.html
- https://en.cppreference.com/w/cpp/utility/forward
- https://en.cppreference.com/w/cpp/container/vector
- https://en.cppreference.com/w/cpp/concepts

## High Precision Class Type

High precision operation is the very fundamental achievement for us to use. 

In almost every situation, when we use `int` data type to do arithmetic operation, we suffer a lot from the worry about the overflow situations. 
However, the *C++ Program Language* does not give a guarantee for us to protect the correctness of our program or detect this situation from it! 
To deal with this shortcoming, we have to define our calculation method, especially make fully use of the standard library. 

The provisional prototype for the high precision prototype is: `std::vector<uint32_t>`. 

### To Do List
Below is #todo list. 

- [ ] Support the addition operation between high-precision instances, or some fundamental arithmetical instances. 
- [ ] Support the multiplication operation between a high-precision instance and some other fundatmental arithmetical instance. 
- [ ] Support the multiplication operation between high-precision instances. 
- [ ] Support the division operation between high-precisions. (Including fundamental arithmetical instances) 
- [ ] Support the string-format method for a high-precision class type. 
- [ ] Support the `Rational` type, using the high-precision custom class.  

## Test Branch 

The file *TestBench.cpp* is the core test file for you to test something working well or not. 

Using this format to write your codes: 

```C++
TEST_METHOD {
    // todo: write your codes. 
    // This method do not have any incoming parameters, you have also no need to return anything in it. 
    // The assert method: bassert(bool expression, the error message); 
    // You can use it smoothly and do some assertions. 
}
```

The specific command for you to run is like that: `g++ -std=c++?? -D TEST_FILD=\"(Please enter your file path! )\" TestBench.cpp` 

And run the output executable file *a.out* or *a.exe*. 

The demo command is provided for WSL: `g++ -std=c++2a -fconcepts -D TEST_FILE=\"test.cpp\" TestBench.cpp && ./a.out` 

---

## Terminal Code Change 

If you invoke this command but meet a mass code display, you can refer to these below to fix it. 

- `chcp 65001`: Change your code in utf-8 format. 
- `chcp 936`: Change your code in gbk format. (Maybe) 

## Windows Support

If you are using powershell, maybe the program would not be executed correctly with '-D' flag. 
You can use the command: `cmd.exe /c 'g++ -std=c++2a -D TEST_FILE=\"test.cpp\" TestBench.cpp'` to reach you aim indirectly. 



## Matrix Prelude Library



### Literal Support

In the *BasicCal.hpp*, the related high precision class literal is supported now! 

You can easily use high precision operations with it. 

The related test is written in **TestLiteral.cpp**. 


### Function Explanation 

Actually, the name of the function is quitely explansive. The function named `add` shows the addition of two high precision instance, and of course return a new instance to express the sum. If you rejects this operation, *maybe considering it as a cumbersome thing*, the other choice for you is `add_pn_then_eq`. 

Obviously, the substitution of them two are: `result = op_lhs + op_rhs`, and the second is `op_lhs += op_rhs`. 
