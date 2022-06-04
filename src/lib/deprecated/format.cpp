#include "std.hpp"
#include "def/mtype_traits.hpp"

namespace matrix::inline prelude {
    namespace deprecated_realization {
        namespace helper {

            // enum class Situation {
            //     NORMAL, PLACER, LEFT_BRACE, RIGHT_BRACE
            // }; 
            
            template <char... chars> 
            struct FormatHelper {
            }; 

            template <> 
            struct FormatHelper<> {
                protected: 
                    template <typename F> 
                    void output(F &) const {} 
            }; 

            template <char c, char... chars> 
            struct FormatHelper<c, chars...> : private FormatHelper<chars...> {
                protected: 
                    static_assert (c != '{' && c != '}'); 
                    template <typename F, typename... Args> 
                    void output(F &f, Args const &...args) const {
                        f(c);  
                        FormatHelper<chars...>::output(f, args...); 
                    }
            }; 
            
            template <char... chars> 
            struct FormatHelper<'{', '}', chars...> : private FormatHelper<chars...> {
                protected: 
                    template <typename F, typename Argu, typename... Args> 
                    void output(F &f, Argu const &a, Args const &...args) const {
                        // f(a); 
                        f(a); 
                        FormatHelper<chars...>::output(f, args...); 
                    }
            }; 

            template <char... chars> 
            struct FormatHelper<'{', '{', chars...> : private FormatHelper<chars...> {
                protected: 
                    template <typename F, typename... Args> 
                    void output(F &f, Args const &...args) const {
                        f('{');  
                        FormatHelper<chars...>::output(f, args...); 
                    }
            }; 

            template <char... chars> 
            struct FormatHelper<'}', '}', chars...> {
                protected: 
                    template <typename F, typename... Args> 
                    void output(F &f, Args const &...args) const {
                        f('}');  
                        FormatHelper<chars...>::output(f, args...); 
                    }
            }; 

        }

        template <char... chars> 
        class FormatLiteral : private helper::FormatHelper<chars...>{
            public: 
                template <typename... Args> 
                std::string operator() (Args const &...args) const {
                    std::string output; 
                    output.reserve(sizeof...(Args) * 2); 
                    auto append_op = [&output](auto const &v) {
                        if constexpr (std::is_same_v<std::decay_t<decltype(v)>, char>) {
                            output += v; 
                        } else {
                            output += matrix::type_traits::Into<std::string>{}.into(v); 
                        }
                    }; 
                    helper::FormatHelper<chars...>::output(append_op, args...); 
                }
        }; 

        template <char... chars> 
        FormatLiteral<chars...> operator ""_format () {
            return FormatHelper<chars...>(); 
        }
    }

    class FormatLiteral: private std::vector<std::string_view> {
        private: 
        using Super = std::vector<std::string_view>; 
        friend FormatLiteral operator ""_format (char const *, size_t ); 
    }; 

    FormatLiteral operator ""_foramt (char const *p, size_t length) {
        FormatLiteral ans; 
        // ans.Super::reserve(20); 
        return ans; 
    }
}

int main() {
    Use matrix; 
    auto p = "{} {}"_format; 
    // std::cout << p << '\n'; 
}