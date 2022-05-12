#include <iostream> 

class MyClass {
    public: 
    void operator() {
        std::cout << "Invoke me! \n"; 
    }
}; 

using std::ostream; 

ostream &operator<<(ostream &o, MyClass &) {
    return o << "MyClass{instance}";
}

void test1_question(); 
void test2(); 

int main() {
    test2(); 
}

void test2() {
    MyClass ins; 
    ins(); 
}

void test1_question() {
    MyClass ins; 
    std::cout << ins << std::endl; 
    // Choose: A
    // operator<<(std::cout, ins); 
    // Choose: B 
    // std::cout.operator<<(ins); 
}