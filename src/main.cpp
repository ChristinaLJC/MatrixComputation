#include "def/MBasicPrecision.hpp"

class BaseClass {
    public: 
    std::string name = "BaseClass."; 
}; 

class DerivedClass: public BaseClass {
    public: 
    int age = 21; 
    DerivedClass() {
        name = "DerviedClass"; 
    }
}; 


int main() {
    BaseClass &&c = DerivedClass(); 
    std::cout << "Get the address of the class instance: " 
        << &c << '\n'; 
    std::cout << "My name is " << c.name << '\n'; 
    int x = 2; 
    int y = 3; 
    auto && z = true ? x : y; 
    std::cout << x << " " << y << '\n'; 
    ++z; 
    std::cout << x << " " << y << '\n'; 
}