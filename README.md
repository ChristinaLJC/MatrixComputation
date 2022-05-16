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