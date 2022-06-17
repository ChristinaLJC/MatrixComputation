#include "std.hpp" 

namespace matrix::algorithm {

    template <typename Matrix> 
    typename Matrix::MatrixOfType<typename type_traits::TypeUpgrade<Matrix::ValueType>> gauss_elimination(Matrix const &); 

}