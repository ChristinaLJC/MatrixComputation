#pragma once 

#include <iostream> 
#include <cstdint> 
#include <memory> 
#include <array> 

template <typename T> 
struct IdentityValue {
    static constexpr T value = T{1}; 
}; 

template <typename T, size_t row_, size_t col_> 
class line_matrix {
    public: 
        static size_t constexpr row = row_; 
        static size_t constexpr col = col_; 
    private: 
        // Check the overflows situation. 
        static size_t constexpr ele_nums {row * col}; 

    private: 
        // std::shared_ptr<T[]> val = std::make_shared<T[]>(ele_nums); 
        std::shared_ptr<std::array<T, ele_nums>> val = std::make_shared<std::array<T, ele_nums>>(); 
    public: 

    public: 
    line_matrix static identity() {
        line_matrix l; 
        for (int i = 0; i < row; ++i) 
            for (int j = 0; j < col; ++j) {
                if (i == j) {
                    (T&)l[i][j] = IdentityValue<T>::value; 
                } else {
                    (T&)l[i][j] = T{}; 
                }
            } 
        return l; 
    }
    line_matrix() {
        for (int i = 0; i < row; ++i) 
            for (int j = 0; j < col; ++j) 
                (T&)((*this)[i][j]) = T{}; 
    } 
    line_matrix(line_matrix &other): val(other.val) {}
    line_matrix(line_matrix &&other): val(std::move(other.val)) {}
    private: 
    template <typename T_>
    struct val_map: private std::function<std::reference_wrapper<T_> (size_t )> {
        struct iterator {
            size_t val {} ; 
            val_map map; 
            auto operator *() {
                return map[val];
            }
            bool operator !=(iterator const &o) {
                return val != o.val; 
            }
            iterator &operator++() {
                ++val; 
                return *this; 
            }
        }; 
        static_assert(std::is_same_v<T, std::remove_const_t<T_>>);
        val_map(std::function<std::reference_wrapper<T_> (size_t )> f): std::function<std::reference_wrapper<T_> (size_t )>(std::move(f)) {} 
        std::reference_wrapper<T_> operator[] (size_t v) {
            return this->operator()(v); 
        }
        iterator begin() {
            return {0, *this}; 
        }
        iterator end() {
            return {col, *this}; 
        }
    }; 
    public:  
    val_map<T> constexpr operator[](size_t v) {
        return (std::function<std::reference_wrapper<T> (size_t )> )[val = this->val, v](size_t v_) -> std::reference_wrapper<T> { return (*val)[v * col + v_]; } ; 
    } 
    val_map<T const> constexpr operator[] (size_t v) const {
        return (std::function<std::reference_wrapper<T const> (size_t )> )[val = this->val, v](size_t v_) -> std::reference_wrapper<T const> { return (*val)[v * col + v_]; } ; 
    }
}; 

template <typename T, size_t r, size_t w, typename matrix_t = line_matrix<T, r, w>> 
matrix_t operator+ (line_matrix<T, r, w> const &a, line_matrix<T, r, w> const &b) {
    static_assert(std::is_same_v<line_matrix<T, r, w>, matrix_t>); 

    matrix_t ans; 
    for (int i = 0; i < matrix_t::row; ++i) 
        for (int j = 0; j < matrix_t::col; ++j) 
            ans[i][j] = a[i][j] + b[i][j]; 
    
    return ans;
}

template <typename T, size_t r, size_t w, typename V, typename matrix_t = line_matrix<T, r, w>> 
matrix_t operator* (line_matrix<T, r, w> const &a, V val) {
    static_assert(std::is_same_v<line_matrix<T, r, w>, matrix_t>); 

    matrix_t ans; 
    for (int i = 0; i < matrix_t::row; ++i) 
        for (int j = 0; j < matrix_t::col; ++j) 
            //(decltype(ans[i][j])::type &)
            (T&) ans[i][j] = a[i][j] * val; 
    return ans; 
}

template <typename T, size_t r, size_t w> 
std::ostream &operator << (std::ostream &o, line_matrix<T, r, w> const &m) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < w; ++j) 
        {
            if (j) 
                o << " "; 
            o << m[i][j]; 
        }
        o << "\n"; 
    }
    return o; 
}

template <typename T, size_t r, size_t w, size_t c> 
line_matrix<T, r, c> operator* (line_matrix<T, r, w> const &a, line_matrix<T, w, c> const &b) {
    line_matrix<T, r, c> ans; 
    for (int i = 0; i < r; ++i) 
        for (int j = 0; j < c; ++j) 
            for (int k = 0; k < w; ++k) 
                ans[i][j] += a[i][k] * b[k][j]; 
    return ans; 
}