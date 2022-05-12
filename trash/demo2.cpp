#include <map> 
#include <iostream> 

template <typename K, typename T> 
class MyMap: public std::map<K, T> {

}; 

template <typename... T> 
class MyClass: public T... {
    
}; 

int main() {

}