#pragma once 

#include <array>
#include <bitset> 
#include <chrono>
#include <codecvt> 
#include <cstddef>
#include <cstdint> 
#include <exception> 
#include <functional> 
#include <future>
#include <iomanip>
#include <iostream> 
#include <locale> 
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
#include <variant> 
#include <vector> 

using std::nullptr_t; 

using i16 = int16_t; 
using i32 = int32_t;  
using i64 = int64_t; 
using u16 = uint16_t;  
using u32 = uint32_t;  
using u64 = uint64_t;  

constexpr bool logical_error_detected = 
    #ifdef RELEASE 
        true
    #else 
        false 
    #endif 
; 

