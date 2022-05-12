#include <iostream> 

class MyClass {
}; 

using std::ostream; 

ostream &operator<<(ostream &o, MyClass &) {
    return o << "MyClass{instance}";
}

int main() {
    MyClass ins; 
    std::cout << ins << std::endl; 
}