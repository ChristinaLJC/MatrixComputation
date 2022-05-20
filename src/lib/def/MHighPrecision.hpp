#pragma once 

namespace Matrix::HighPrecision {

    namespace uint128_t {

        class uint128_t; 
        using u128 = uint128_t; 

        u128 mul(u128 const &, u128 const &);

        [[maybe_unused]] u128 &div_u32_then_eq(u128 &, u32, u32 * = nullptr); 

        std::string to_string (uint128_t const &); 

    }

    using uint128_t::u128; 

    namespace HighPrecision {

        class BigNumber; 


    }

}

#include "realization/ParseToString.hpp"
#include "realization/u128Calculation.hpp"