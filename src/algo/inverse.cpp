template <typename T>
T inverse(T const & origin) {
    if (origin.row() != origin.col()) {
        // throw exception
    }

    auto n = origin.row(); // the size of the matrix is n*n
    
    T identity = identity_matrix(n); // make an identity matrix with origin's size

    T elimination = gaussian_elimination(origin, identity);  // 高斯消元，包括向上回溯

    T result = new_matrix(n, n); // use new_matrix to new a matrix
    
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