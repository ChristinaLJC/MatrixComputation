#pragma once 

#include "division.hpp"

namespace matrix::inline prelude {
    constexpr u128 u128::operator%(u128 const &rhs) const {
        u128 result; 
        u128 cached = *this; 
        if (!rhs) {
            throw exception::MatrixZeroDividedException("uint128_t has a mod value {zero}. "); 
        }
        helper::divide<GetByIndex>(result, cached, rhs); 
        // std::clog << "Finish the mod calculation. \n"; 
        return cached; 
    }

    constexpr u128 &u128::operator%= (u128 const &rhs) {
        // u128 ans = *this % rhs; 
        return *this = *this % rhs; 
    }
}