#include "line_matrix.hpp" 

#include <iostream> 

int main() {

    // std::cout << (2 <=> 3) << std::endl; 

    line_matrix<int, 3, 2> first; 
    (int& )first[0][0] = 3; (int& )first[0][1] = 2; 
    (int& )first[1][0] = 1; (int& )first[1][1] = 8; 
    (int& )first[2][0] = 6; (int& )first[2][1] = -2; 

    line_matrix<int, 2, 1> second; 
    (int& )second[0][0] = 1; (int& )second[1][0] = 2; 

    auto ans = first * second; 

    std::cout << "ans: \n" << ans; 

    for (auto v: first[0]) 
        ++v; 
    
    std::cout << "first: \n" << first; 

    std::cout << "ans: \n" << (first * second); 
    
}

// Consider the formula: 
// 3x + 2y = 7
// x + 8y = 17 
// 6x - 2y = 2 
// It's easily to know that: 
// The matrix A: 
// [3, 2] 
// [1, 8] 
// [6, -2] 

// The matrix B: 
// [x = 1] 
// [y = 2]

// Then get the result: A * B! 
