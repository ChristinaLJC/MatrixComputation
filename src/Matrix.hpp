#pragma once 

#include "std.hpp"

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
        { std::declval<T>().size() == std::declval<V>().size() } -> std::convertible_to<bool>; 
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
        if (bool(lhs_matrix.size() != rhs_matrix.size())) {
            using namespace std::literals; 
            throw std::runtime_error("Left Handside Matrix's size = "s + std::to_string(lhs_matrix.size()) + ", but right handside is " 
                + std::to_string(rhs_matrix.size()) + ". "); 
        }
        auto result = Container<typename ResultTypeImpl<LhsType, RhsType>::type>{}; 
        size_t size = lhs_matrix.size(); 
        result.resize(size); 
        auto add_op_method = [&result](auto &&this_vector) {
            size_t poi {}; 
            for (auto &&t: this_vector) {
                result.at(poi) += t; 
                ++poi; 
            } 
        }; 
        add_op_method(lhs_matrix); 
        add_op_method(rhs_matrix);
        return result; 
    }
}
