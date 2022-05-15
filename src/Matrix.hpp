#include <cstdint> 
#include <vector> 
#include <type_traits> 
#include <string> 
#include <exception> 

namespace Matrix {

    template <typename A, typename B> 
    struct FundamentalAdd {
        using type = decltype(std::declval<A>() + std::declval<B>()); 
    }; 

    template <typename T> 
    using DefaultAllocatorVector = std::vector<T, std::allocator<T>>; 

    template <typename T, typename V> 
    concept CanCompSize = requires {
        { std::declval<T>().size() != std::declval<V>().size() } -> std::convertible_to<bool>; 
    }; 

    template <template <typename, typename> typename ResultTypeImpl = FundamentalAdd, 
        template <typename...> typename Container = std::vector, 
        typename LhsType, typename RhsType, 
        template <typename... > typename LhsContainer, template <typename...> typename RhsContainer, 
        typename... Useless1, nullptr_t = nullptr, typename... Useless2> 
    auto add(LhsContainer<LhsType, Useless1...> const &lhs_matrix, RhsContainer<RhsType, Useless2...> const &rhs_matrix) -> 
        std::enable_if_t< 
            CanCompSize<LhsContainer<LhsType, Useless1...>, RhsContainer<RhsType, Useless2...>>, Container<typename ResultTypeImpl<LhsType, RhsType>::type>> 
    {
        auto result = Container<typename ResultTypeImpl<LhsType, RhsType>::type>{}; 
        if (bool(lhs_matrix.size() != rhs_matrix.size())) {
            using namespace std::literals; 
            throw std::runtime_error("Left Handside Matrix's size = "s + std::to_string(lhs_matrix.size()) + ", but right handside is " 
                + std::to_string(rhs_matrix.size()) + ". "); 
        }
        size_t size = lhs_matrix.size(); 
        if constexpr (requires {result.reserve(std::declval<size_t>()); }) {
            result.reserve(size); 
        }
        for (size_t i = 0; i < size; ++i) {
            result.push_back(lhs_matrix[i] + rhs_matrix[i]); 
        }
        return result; 
    }

    // template <template <typename...> typename A, template <typename ...> typename B, typename DataTypeA, typename DataTypeB, typename... AArgs, typename... BArgs, 
    // template <typename> typename S = DefaultAllocatorVector > 
    // auto add(A<DataTypeA, AArgs...>, B<DataTypeB, BArgs...>) {
    //     std::cout << "add! \n"; 
    // }

}
