#include <iostream> 

class MyClass {
    public: 
    void operator()() {
        std::cout << "Invoke me! \n"; 
    }
}; 

class MyClassPtr {
    public: 
    MyClass *ptr; 
    MyClass *operator->() {
        return ptr; 
    }
}; 

using std::ostream; 

ostream &operator<<(ostream &o, MyClass &) {
    return o << "MyClass{instance}";
}

void test1_question(); 
void test2(); 
void test3(); 

int main() {
    test3(); 
}

void test3() {
    MyClass ins;
    MyClassPtr p = {.ptr = &ins}; 
    p->operator()(); 
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