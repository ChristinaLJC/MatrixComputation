namespace matrix::algorithm {
    
    template <typename ResultMatrix = typename type_traits::DefaultInverseMatrixType<OriginMatrix>::type, 
            typename OriginMatrix>
    ResultMatrix inverse(OriginMatrix const &self) {
        if (self.row() != self.col()) {
            // throw exception
        }

        auto n = self.row(); // the size of the matrix is n*n

        OriginMatrix identity = identity_matrix(n); // make an identity matrix with origin's size

        OriginMatrix elimination = gaussian_elimination(self, identity);  // 高斯消元，包括向上回溯

        ResultMatrix result = new_matrix(n, n); // use new_matrix to new a matrix

        for (int i = 0; i < n; ++i) {
            auto pivot = elimination[i][i];
            if (pivot != 0) {
                for (int j = 0; j < n; ++j) {
                    result[i][j] = elimination[i][j+n] / pivot;
                }
            }
            else {
                // throw exception
            }
        }
        return result;
    }
}

