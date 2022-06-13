#pragma once 

#include "std.hpp" 

namespace matrix::algorithm {
    template <typename ResultMatrix = Matrix, typename Matrix> 
    ResultMatrix inverse (Matrix const &self) {
        auto len = self.row(); 
        if (len != self.col()) {
            abort(); 
        }

        Matrix identity = Matrix::with_identity_size(len); 
        Matrix elimination = gaussian_elimination(self, identity); 

        ResultMatrix result = ResultMatrix::with_size(len); 

        for (size_t i = 0; i < len; ++i) {
            auto pivot = elimination[i][i]; 
            if (pivot) {
                for (size_t j = 0; j < len; ++j) {
                    result[i][j] = elimination[i][j + len] / pivot; 
                }
            } else {
                abort(); 
            }
        }

        return result; 
    }
}