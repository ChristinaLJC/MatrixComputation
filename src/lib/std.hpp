#pragma once 

#include <array>
#include <bitset> 
#include <cassert> 
#include <chrono>
#include <cmath> 
#include <codecvt> 
#include <complex>
#include <cstddef>
#include <cstdint> 
#include <exception> 
#include <functional> 
#include <future>
#include <iomanip>
#include <iostream> 
#include <locale> 
#include <map>
#include <numeric>
#include <optional> 

#ifdef __cpp_lib_source_location
#include <source_location> 
#endif

#include <stdexcept>
#include <string> 
#include <sstream> 
#include <thread>
#include <tuple>
#include <type_traits> 
#include <utility> 
#include <valarray>
#include <variant> 
#include <vector> 

using std::nullptr_t; 

using i16 = int16_t; 
using i32 = int32_t;  
using i64 = int64_t; 
using u16 = uint16_t;  
using u32 = uint32_t;  
using u64 = uint64_t;  
using isize = ptrdiff_t; 
using usize = size_t;  

/** 
 * todo: 
 * i128 & u128 are needed to realize! 
 */ 

/** 
 * The const expression in compiling time for a detect & check operations. 
 * 
 * Use -D NDEBUG flag would open it and we can see everything! 
 */ 
namespace matrix {
    constexpr bool logical_error_detected = 
        #ifndef NDEBUG 
            true
        #else 
            false 
        #endif 
    ; 
}

/** 
 * Though it quitely make sense to put these syntax grammar in 'Alias.hpp', but it's not enough convenient for us to use it. 
 * 
 * The better choice is that let's just include it everywhere! 
 * 
 * Similarly, be careful about the redefinition of this syntax macro. 
 */ 
#define Use using namespace 

/** 
 * If void_t trait isn't defined in std, we just supplement for it. 
 */ 
#ifndef __cpp_lib_void_t 
namespace std {
    template <typename...> 
    using void_t = void; 
}
#endif