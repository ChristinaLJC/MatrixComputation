#include "std.hpp" 

namespace matrix::algorithm {

    template <typename Matrix, typename ResultType = typename Matrix::template MatrixOfType<typename type_traits::TypeUpgrade<typename Matrix::ValueType>>> 
    std::pair<ResultType, ResultType> gauss_elimination(Matrix const &self) {
        todo(""); 
    }

}