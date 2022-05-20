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

    class PrecisionNumber; 

    enum class PNSymbol: unsigned char {
        POSITIVE, NEGATIVE, ZERO
    };

    typedef std::vector<uint32_t> PNumber; 

    // all basic calculations of PNumber

    PNumber add_pn(PNumber const &, PNumber const &); 
    std::pair<PNumber, PNSymbol> minus_pn(PNumber const &, PNumber const &); 
    PNumber mul_pn(PNumber const &, PNumber const &); 
    std::pair<PNumber, PNumber> div_pn(PNumber const &, PNumber const &); 

    PNumber &mul_pn_then_eq(PNumber &, PNumber const &);

    PNumber &div_u32_then_eq(PNumber &, uint32_t, uint32_t * = nullptr); 
    PNumber &add_u32_then_eq(PNumber &, uint32_t); 
    PNumber &mul_u32_then_eq(PNumber &, uint32_t); 

    uint32_t mod_v_2(PNumber const &); 

    PNumber &trim(PNumber &); 

    PNumber &add_pn_then_eq(PNumber &, PNumber const &);
    PNumber &mut_pn_then_eq(PNumber &, PNumber const &); 
    PNumber &div_pn_then_eq(PNumber &, PNumber const &, PNumber * = nullptr); 

    bool is_zero(PNumber const &); 
        
    std::string to_string(PNumber const &); 
    std::string to_hex_string(PNumber const &); 
    std::string to_bin_string(PNumber const &); 

    template <char...> 
    PNumber operator "" _pn(); 




}

#include "realization/ParseToString.hpp"
#include "realization/u128Calculation.hpp"