#pragma once 

#include "std.hpp"
#include "def/mexception.hpp"
#include "def/mtype_traits.hpp"

namespace matrix::inline prelude {
    class FormatLiteral; 

    namespace helper {
        void append(std::string &, FormatLiteral const &, size_t ); 
        template <typename T, typename... Args> 
        void append(std::string &, FormatLiteral const &, size_t, T const &, Args const &... ); 
    } 

    class FormatLiteral: private std::vector<std::string_view> {
        private: 
        using Super = std::vector<std::string_view>; 
        friend FormatLiteral operator ""_format (char const *, size_t ); 
        template <typename T, typename... Args> 
        friend void matrix::prelude::helper::append(std::string &, FormatLiteral const &, size_t, T const &, Args const &...); 
        friend void matrix::prelude::helper::append(std::string &, FormatLiteral const &, size_t ); 
        public: 
        template <typename... Args> 
        std::string operator () (Args const &... args) const {
            std::string ans; 
            helper::append(ans, *this, 0, args...); 
            return ans; 
        }
    }; 

    namespace helper {

        void append(std::string &to_append, FormatLiteral const &literal_format, size_t index) {
            while (index < literal_format.size()) {
                // std::clog << "[INFO] index = " << index << '\n'; 
                lassert (!literal_format[index].empty()); 
                to_append += literal_format[index]; 
                ++index; 
            }
        }

        template <typename T, typename... Args> 
        void append(std::string &to_append, FormatLiteral const &literal_format, size_t index, T const &t, Args const &... args) {
            while (index < literal_format.size()) {
                // std::clog << "Args with, index = " << index << '\n'; 
                if (literal_format[index].empty()) {
                    to_append += type_traits::Into<std::string>{}.into(t); 
                    ++index; 
                    break; 
                } else {
                    to_append += literal_format[index++]; 
                }
            }
            if constexpr (sizeof...(Args)) {
                lassert (index < literal_format.size()); 
            }    
            if (index < literal_format.size()) {
                append(to_append, literal_format, index, args...); 
            }
        }

    }
    FormatLiteral operator ""_format (char const *p, size_t len) {
        FormatLiteral ans; 
        // ans.reserve(20); 
        // No need to reserve it. 
        size_t now_index = 0; 
        size_t left_bound = 0; 
        std::string_view basic_view = p; 
        // std::clog << "[INFO] " << basic_view << '\n'; 
        while (now_index < len) {
            if (basic_view[now_index] != '{' && basic_view[now_index] != '}') {
                // std::clog << "[INFO] catch char: " << basic_view[now_index] << '\n'; 
                ++now_index; 
                continue; 
            } else if (basic_view[now_index] == '{') {
                lassert (now_index + 1 < len); 
                lassert (basic_view[now_index + 1] == '{' || basic_view[now_index + 1] == '}'); 
                if (now_index > left_bound) {
                    // std::clog << "Push {" << basic_view.substr(left_bound, now_index - left_bound) << "}\n"; 
                    ans.push_back(basic_view.substr(left_bound, now_index - left_bound)); 
                }
                if (basic_view[now_index + 1] == '{') {
                    ans.push_back("{"); 
                } else {
                    ans.push_back(""); 
                }
            } else {
                lassert (basic_view[now_index] == '}'); 
                lassert (now_index + 1 < len); 
                lassert (basic_view[now_index + 1] == '}'); 
                if (now_index > left_bound) 
                    ans.push_back(basic_view.substr(left_bound, now_index - left_bound)); 
                ans.push_back("}"); 
            }
            left_bound = now_index + 2; 
            now_index += 2; 
        }
        if (now_index > left_bound) 
            ans.push_back(basic_view.substr(left_bound, now_index - left_bound)); 
        return ans; 
    }
}