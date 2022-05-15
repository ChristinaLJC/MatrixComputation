#include <iostream> 
#include "Matrix.hpp" 


int main() {
    std::vector<int> x {1, 2, 3, 4}; 
    std::vector<float> y {2.5, 3.4, 4.3, .1}; 
    using namespace Matrix; 
    auto &&v = add(x, y); 
    for (auto s: v) {
        std::cout << s << " "; 
    }
    endl(std::cout); 
    if constexpr (std::same_as<typename std::decay_t<decltype(v)>::value_type, float>) {
        std::cout << "v is a vector with float elements! "; 
    } else {
        std::cout << "v is a vector with " << typeid(typename std::decay_t<decltype(v)>::value_type).name() << " type. ";
    }
    endl(std::cout);
}
