#include "def/mexception.hpp"
#include "def/mconstraints.hpp"
#include "def/uint128_t.hpp"

int main() {
    bassert ("Hello World" != nullptr); 
    bassert_eq (1 + 2 + 3 + 4 + 5, 15); 
    bassert_in (9 * 11 * 13, lower_bound(1000) && upper_bound(2000) ); 
    using namespace std::literals; 
    bassert ("Cutie Deng"s == "Cutie"s); 
    bassert_eq (37 * 37, 1396); 
    bassert_in(999, upper_bound(1000) && upper_bound(600) && lower_bound(400)); 
    std::cout << "Pass!\n"; 
}