#pragma once 

#include "cache/std.hpp"

namespace Matrix::HighPrecision::uint128_t {

    class uint128_t; 

    using u128 = uint128_t; 

    class uint128_t {
        std::array<u32, 4> values {}; 
        public: 
        
        // Constructor 

        /** 
         * The basic empty parameter constructor. 
         */ 
        uint128_t() {}; 

        /** 
         * The u32 value constructor, it can give a better optimization because we can reduce 
         *   one time of the right shift operations. 
         */ 
        uint128_t(u32 val): values({val, }) {
        }

        /** 
         * The u64 value constructor. 
         * 
         * It's a normal constructor to use for us. 
         */ 
        uint128_t(u64 val): values({val, val >> 32, }) {
        }

        /** 
         * The copy constructor! 
         * 
         * Because this structure is pure data but not memory allocation in other place. The other operations are no need! 
         */ 
        uint128_t(u128 const &) = default; 

        // The changing methods. 

        template <bool overflow_detect = false> 
        u128 add(u128 other) const ; 
        
    }; 
}