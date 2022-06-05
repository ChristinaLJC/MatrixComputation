#pragma once 

namespace matrix::inline prelude {

    u128::operator std::string() const noexcept(!logical_error_detected) {
        u128 temporary = *this; 
        char numbers[40]; 
        size_t index {}; 
        while (temporary) {
            u32 result; 
            temporary.divide_and_then_eq<1000000000u>(&result); 
            size_t small_index {}; 
            while (result) {
                auto divide_ten = std::div(result, 10); 
                numbers[index++] = '0' + divide_ten.rem; 
                ++small_index; 
                result = divide_ten.quot;  
            }
            if (temporary) {
                while (small_index < 9) {
                    lassert (index < 40); 
                    numbers[index++] = '0'; 
                    small_index++; 
                }
            }
        }
        std::string result; 
        if (index == 0) {
            result = "0"; 
        } else {
            result.reserve(40); 
            while (index--) {
                result += numbers[index]; 
            }
        }
        return result; 
    }

}