#include "def/mexception.hpp"
#include "def/mconstraints.hpp"
#include "def/uint128_t.hpp"

template <typename, typename> 
class AutoMatrix; 

template <typename A, typename B> 
std::ostream &operator<< (std::ostream &, AutoMatrix<A, B> const &); 

// ContainerType : add dec 

class Counter {
    private: 
        size_t cnt{}; 
    protected: 
        void inc() {
            ++cnt; 
        }
        void dec() {
            assert (cnt); 
            --cnt; 
        }
        ~Counter() {
            assert (!cnt); 
        }
}; 

class DoNothing {
    protected: 
        void inc() {} 
        void dec() {} 
}; 

template <typename DataType, typename ContainerType> 
class AutoMatrix: private ContainerType {
    private: 
        std::string name; 
    public: 
        AutoMatrix(std::string name): name(name) {} 
        class Visitor {
            private: 
                AutoMatrix &self; 
            public: 
                Visitor(AutoMatrix &self): self(self) {
                    self.inc(); 
                } 
                Visitor(Visitor const &o): self(o.self) {
                    self.inc(); 
                }
                operator AutoMatrix<DataType, ContainerType> &() const noexcept {
                    return self; 
                }
                AutoMatrix<DataType, ContainerType> &view() const noexcept {
                    return self; 
                }
                ~Visitor() {
                    self.dec(); 
                }
        }; 
        friend std::ostream &operator<< <DataType, ContainerType> (std::ostream &o, AutoMatrix<DataType, ContainerType> const &v) {
            return o << v.name; 
        }
        Visitor visit() {
            return Visitor(*this); 
        }
        // operator Visitor() noexcept {
        //     return Visitor(*this); 
        // }
}; 

// template <typename T>
// void output (T v) {
//     std::cout << v << std::endl; 
// }

template <typename A, typename B> 
struct Output {
    Output(typename AutoMatrix<A, B>::Visitor v) {
        std::cout << v.view() << std::endl; 
    }
}; 

template <typename A, typename B>
using output = Output<A, B>; 

template <typename A, typename B>
Output(AutoMatrix<A, B>) -> Output<A, B>; 

int main() {
    // AutoMatrix<void, Counter> x ("I have name"); 
    // Output{x}; 
    // auto p = x.visit(); 
    // {
    //     AutoMatrix<void, Counter> y ("I have no name! "); 
    //     p = y.visit(); 
    // }
    auto x = std::make_shared<AutoMatrix<void, DoNothing>>("I have name"); 
    auto p = std::make_shared<decltype(x->visit())>(x->visit()); 
    x.reset(); 
    std::cout << sizeof(AutoMatrix<void, DoNothing>) << '\n' 
        << sizeof(AutoMatrix<void, Counter>) << '\n'; 
}