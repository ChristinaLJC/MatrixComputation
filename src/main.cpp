#include "def/mexception.hpp"
#include "def/mconstraints.hpp"

int main() {
    bassert ("Hello World" != nullptr); 
    bassert_eq (1 + 2 + 3 + 4 + 5, 15); 
    bassert_in (9 * 11 * 13, LOWER_BOUND(1000) && UPPER_BOUND(2000) ); 
    std::cout << "Pass!\n"; 
}