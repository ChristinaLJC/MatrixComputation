# MatrixComputation
a lib for Matrix Computation, from CS205

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

