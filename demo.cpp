#include <iostream> 

class MyClass {
}; 

using std::ostream; 

ostream &operator<<(ostream &o, MyClass &) {
    return o << "MyClass{instance}";
}

int main() {
    test1_question();
}

void test1_question() {
    MyClass ins; 
    std::cout << ins << std::endl; 
    // Choose: A
    // operator<<(std::cout, ins); 
    // Choose: B 
    // std::cout.operator<<(ins); 
}