#include "std.hpp" 

namespace matrix::algorithm {
    template <typename NumberType> 
    bool is_nearly_zero(NumberType const &v) {
        if constexpr (std::numeric_limits<std::decay_t<NumberType>>::is_integer) {
            return !v; 
        } else {
            return v <= std::numeric_limits<std::decay_t<NumberType>>::epsilon() && 
                v >= - std::numeric_limits<std::decay_t<NumberType>>::epsilon(); 
        }
    }

    // template <> 
    // bool is_nearly_zero(float const &v) {
    //     return 
    // }
}