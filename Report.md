# Report

member: 李佳纯 黄昊南 邓植仁

-------

## Designing

We design that the data structure is completely divided with the algorithm invocation. The data part is mainly described as OwnedMatrix. Actually, if it's allowed, the better realization would be the automatic matrix types. But the ownership controlling system must base on the OwnedMatrix series. 

The second core part is the algorithm part. In this part, we just need to describe the algorithm itself but do not care about the concrete algorithm type. Then we can use the template type information to describe it then realize the generic algorithm like get inverse or get the sum. 

To make full usage of the matrix access, we define the new type as proxy to temporary cache the index, and after that we can easily visit our element value by this. 

--------

## Highlights

- Test Framework 
  We build a private test framework system which can efficiently test our lib codes in a synchronously and asynchronously way. 
- The advanced integral type 
  We make a more wide integral type `int128_t` to use. Some more convenience techniques including the literals are used. Also the related `uint128_t` type is supported. 
- Stringizing operator: Intelligently stringize an object. Make full use of the compiling rules to transfer an object as a string. 
- Type Traits: Define quite a lot of type traits methods and operators for different types and for the future and unknown types. 
- The exception inheriting system. Different exception are defined as an inheriting tree, and the core abstract exception classes cannot be instantiated. 
- Assert Rule also is designed well in the inheriting system. Some more specific information would be given altogether with the context information. 
- Format Library Support. It's convenient to construct a string in the format basic rule. 
- Proxy Class for the visit control. 
- Meta-Programming in the `uint128_t` and `int128_t` design. 
- Type Upgrade automatically and intelligently. 
- The algorithm design is divided completely with the matrix structure. It's open to design a better matrix based on the `OwnedMatrix` designs. For example the auto-owning matrixes and the inertia matrixes. 

---------------

## Difficulties

- Eigenvalue is hard to compute
- Hard to cope with complex in Eigenvalue computation
- OpenCV
- It needs hard thoughts to comparing different basic data types. 
- Complex is quite difficult to deal with, because it seems a normal data type but completely different from other normal data types. 

--------------

## Core Codes & Tests

Class Matrix:

==**We use template class to implement the matrix. It supports numeric types and arbitrary size. And it is easy to extend.**==

```cpp
namespace matrix {
    template <typename ValueType_, template <typename ...> typename ValueContainer_ = std::valarray>
    class LinearOwnedMatrix : ValueContainer_<ValueType_> {
        private:
            size_t m_row;
        public:
            using ValueType = ValueType_;
            template <typename... Args>
            using ContainerType = ValueContainer_<Args...>;
            using Super = ContainerType<ValueType>;
            using This = LinearOwnedMatrix;
            template <typename OtherDataType>
            using MatrixOfType = LinearOwnedMatrix<OtherDataType>;

            constexpr static bool is_fixed = false;

        private:
            LinearOwnedMatrix(Super &&self, size_t row): Super(std::move(self)), m_row(row) {
                lassert (size());
            }
    }
}
```

### Small Fixed-Size Matrix

<img src="D:\SUSTech\2022Spring\CPP\Project\res\small_fixed.png" style="zoom:50%;" />

### Arbitrarily Large Dense Matrix

![](D:\SUSTech\2022Spring\CPP\Project\res\large.png)

![](D:\SUSTech\2022Spring\CPP\Project\res\large2.png)

### Sparse Matrix

```cpp
			ValueType sum() const {
                ValueType result = 0;
                for (auto &&v: *this) {
                    result += v.second; 
                }
                return result;
            }
```

```cpp
template <typename T, template <typename ...> typename container = std::map> 
    struct SparseOwnedMatrix : private container<std::size_t, T> {
        private: 
            size_t row, col; 
        public: 
            using ValueType = T; 
            template <typename O> 
            using MatrixOfType = SparseOwnedMatrix<O, container>; 
            using This = SparseOwnedMatrix;
            using Super = container<std::size_t, T>;  
            
            SparseOwnedMatrix(size_t row, size_t col): row(row), col(col) {} 
    }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\sparse.png" style="zoom:50%;" />

<img src="D:\SUSTech\2022Spring\CPP\Project\res\sparse2.png" alt="sparse2" style="zoom:50%;" />

###Numeric Types Support

<img src="D:\SUSTech\2022Spring\CPP\Project\res\numeric_test.png" style="zoom:50%;" />

<img src="D:\SUSTech\2022Spring\CPP\Project\res\numeric_test2.png" style="zoom:50%;" />

<img src="D:\SUSTech\2022Spring\CPP\Project\res\custom.png" style="zoom:67%;" />

### Matrix and Vector Addition

```cpp
LinearOwnedMatrix operator+(LinearOwnedMatrix const &rhs) const {
                auto row = m_row;
                // Throw an exception describes the mismatching of the matrix.
                Use matrix::exception;
                if (rhs.row() != row) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix addition with the mismatched row value. ");
                } else if (size() != rhs.size()) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix addition with the mismatched col value. ");
                }
                return LinearOwnedMatrix ((Super&)*this + (Super&)rhs, row);
            }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\addition_test.png" style="zoom: 50%;" />

<img src="D:\SUSTech\2022Spring\CPP\Project\res\addition_test2.png" style="zoom:50%;" />

### Matrix and Vector Subtraction

```cpp
            LinearOwnedMatrix operator-(LinearOwnedMatrix const &rhs) const {
                Use matrix::exception;
                auto row = m_row;
                if (rhs.row() != row) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix addition with the mismatched row value. ");
                } else if (size() != rhs.size()) {
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix addition with the mismatched col value. ");
                }
                return LinearOwnedMatrix ((Super&)*this - (Super&)rhs, row);
            }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\subtraction_test.png" style="zoom:50%;" />

<img src="D:\SUSTech\2022Spring\CPP\Project\res\subtraction_test2.png" alt="subtraction_test2" style="zoom:50%;" />

### Matrix and Vector Scalar Multiplication

```cpp
        LinearOwnedMatrix operator*(ValueType const &rhs) const {
            return LinearOwnedMatrix ((Super&)*this * rhs, row());
        }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\scalar_mul.png" alt="scalar_mul" style="zoom:50%;" />

### Matrix and Vector Scalar Division

```cpp
    LinearOwnedMatrix operator/(ValueType const &rhs) const {
        return LinearOwnedMatrix ((Super&)*this / rhs, row());
    }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\scalar_div.png" style="zoom:50%;" />

### Matrix and Vector Transposition

```cpp
LinearOwnedMatrix transposition() const {
                This ans (size() / row(), row());
                for (size_t r = 0; r < size() / row(); ++r) {
                    for (size_t c = 0; c < row(); ++c) {
                        ans[r][c] = (*this)[c][r];
                    }
                }
                return ans;
            }

```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\transposition.png" style="zoom:50%;" />

### Matrix and Vector Conjugation

```cpp
        This operator~ () const {
            return This(this->apply(std::conj), row()); 
        }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\conju.png" style="zoom:50%;" />

<img src="D:\SUSTech\2022Spring\CPP\Project\res\conju1.png" alt="conju1" style="zoom:50%;" />

### Matrix and Vector Element-Wise Multiplication

```cpp
        LinearOwnedMatrix element_wise_product(LinearOwnedMatrix const &rhs) const {
            Use matrix::exception;
            auto row = m_row;
            if (rhs.row() != row) {
                throw MatrixStructureMismatchingException("LinearOwnedMatrix element_wise_product with the mismatched row value. ");
            } else if (size() != rhs.size()) {
                throw MatrixStructureMismatchingException("LinearOwnedMatrix element_wise_product with the mismatched col value. ");
            }
            return LinearOwnedMatrix ((Super&)*this * (Super&)rhs, row);
        }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\wise1.png" style="zoom: 50%;" />

### Matrix-Matrix Multiplication

```cpp
            This operator * (This const &rhs) const {
                return cross_product(rhs); 
            }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\mat_mat_mul.png" style="zoom:50%;" />

### Matrix-Vector Multiplication

<img src="D:\SUSTech\2022Spring\CPP\Project\res\mat_vec_mul.png" style="zoom:50%;" />

### Matrix and Vector Dot Product

```cpp
        LinearOwnedMatrix dot_product(LinearOwnedMatrix const &rhs) const {
            Use matrix::exception;
            auto row = m_row;
            if (rhs.row() != row) {
                throw MatrixStructureMismatchingException("LinearOwnedMatrix dot_product with the mismatched row value. ");
            } else if (size() != rhs.size()) {
                throw MatrixStructureMismatchingException("LinearOwnedMatrix dot_product with the mismatched col value. ");
            }
            This temp = element_wise_product(rhs);
            This ans(1, size()/row);
            for (size_t r = 0; r < row; ++r){
                for (size_t c = 0; c < size()/row; ++c) {
                    ans[0][c] += temp[r][c];
                }
            }
            return ans;
        }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\dot_product.png" style="zoom: 50%;" />

### Matrix and Vector Cross Product

```cpp
        LinearOwnedMatrix cross_product(LinearOwnedMatrix const &rhs) const {
            Use matrix::exception;
            auto row = m_row;
            if (size() / row != rhs.row()) {
                throw MatrixStructureMismatchingException("LinearOwnedMatrix cross product with the mismatched matrix size. ");
            }
            This ans(row, rhs.size() / rhs.row());
            for (size_t r = 0; r < row; ++r){
                for (size_t c = 0; c < rhs.size() / rhs.row(); ++c) {
                    for (size_t k = 0; k < size() / row; ++k){
                        ans[r][c] += ((*this)[r][k] * rhs[k][c]);
                    }
                }
            }
            return ans;
        }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\cross_pro.png" style="zoom:50%;" />

<img src="D:\SUSTech\2022Spring\CPP\Project\res\cross_pro2.png" alt="cross_pro2" style="zoom:50%;" />

### Max Min Sum Avg

```cpp
			ValueType max(size_t r0, size_t r1, size_t c0, size_t c1) const {
                Use matrix::exception;
                if (r1 < r0 || c1 < c0 || r0 > row() || r1 > row() || c0 > col() || c1 > col()){
                    throw MatrixStructureInvalidSizeException("LinearOwnedMatrix max with invalid size");
                }
                return slice(r0, r1, c0, c1).max();
            }
                        
            ValueType min(size_t r0, size_t r1, size_t c0, size_t c1) const {
                Use matrix::exception;
                if (r1 < r0 || c1 < c0 || r0 > row() || r1 > row() || c0 > col() || c1 > col()){
                    throw MatrixStructureInvalidSizeException("LinearOwnedMatrix min with invalid size");
                }
                return slice(r0, r1, c0, c1).min();
            }

            ValueType sum(size_t r0, size_t r1, size_t c0, size_t c1) const {
                Use matrix::exception;
                if (r1 < r0 || c1 < c0 || r0 > row() || r1 > row() || c0 > col() || c1 > col()){
                    throw MatrixStructureInvalidSizeException("LinearOwnedMatrix sum with invalid size");
                }
                return slice(r0, r1, c0, c1).sum();
            }

            ValueType avg(size_t r0, size_t r1, size_t c0, size_t c1) const {
                Use matrix::exception;
                if (r1 < r0 || c1 < c0 || r0 > row() || r1 > row() || c0 > col() || c1 > col()){
                    throw MatrixStructureInvalidSizeException("LinearOwnedMatrix avg with invalid size");
                }
                return slice(r0, r1, c0, c1).avg();
            }

            using Super::max;
            using Super::min;
            using Super::sum;

            ValueType avg() const {
                return sum() / size();
            }
```

![](D:\SUSTech\2022Spring\CPP\Project\res\max_min_sum_avg.png)

### Eigenvalues and Eigenvectors

```cpp
template <typename Matrix> 
    auto eigenvalue(Matrix const &self) {

        constexpr int attempt_cnt = 100; 

        using DataType = typename type_traits::template TypeUpgrade<typename Matrix::ValueType>::type; 
        using ResultType = std::vector<DataType>; 
        
        typename Matrix::template MatrixOfType<DataType> temp = self; 
        for (int i = 0; i < attempt_cnt; ++i) {
            auto [q, r] = qr_factorization(temp);
            temp = r * q;
        }

        ResultType result; 
        result.reserve(temp.row()); 

        for (int i = 0; i < temp.row(); ++i) {
            result.push_back(temp[i][i]); 
        }

        sort(result.begin(), result.end(), helper::ComplexComp{});

        return result;
    }

    template <typename Matrix> 
    auto gaussian_elimination_as_mut(Matrix &self) {
        size_t row = self.row(); 
        for (size_t i = 0; i < row; ++i) {
            auto col = self.col(); 
            if (i >= col) 
                break; 
            
            auto pivot = self[i][i]; 

            if (is_nearly_zero(pivot)) {
                size_t j; 
                for (j = i + 1; j < row; ++j) {
                    if (!is_nearly_zero(self[j][i])) {
                        for (size_t k {}; k < col; ++k) {
                            std::swap(self[i][k], self[j][k]); 
                        }
                        break; 
                    } 
                }
                if (j == row) {
                    return i; 
                }
            }

            for (size_t j = i + 1; j < row; ++j) {
                auto divisor = self[j][i] / pivot; 
                self[j][i] = {}; 
                for (size_t k = i + 1; k < col; ++k) {
                    self[j][k] -= self[i][k] * divisor; 
                    if (algorithm::is_nearly_zero(self[j][k])) {
                        self[j][k] = 0; 
                    }
                }

            }
        }

        return row; 
    }

    template <typename Matrix, typename ResultDataType = typename type_traits::template TypeUpgrade<typename Matrix::ValueType>::type> 
    auto eigenvector (Matrix const &self) {
        auto len = self.row(); 
        if (len != self.col()) {
            throw matrix::exception::MatrixNonSquareException( __FILE__ ":" STRING(__LINE__) " " STRING(__FUNCTION__) ": the matrix is not a square matrix. "); 
        }

        typename Matrix::template MatrixOfType<ResultDataType> ans(len, len);

        size_t cnt = 0; 
        auto eigenvalues = eigenvalue(self); 

        auto last = eigenvalues[0]; 
        for (size_t i = 0; i < len; ++i) {
            lassert (i < eigenvalues.size());
            auto value = eigenvalues[i]; 

            if (i != 0 && type_traits::is_nearly_same(last, value)) {
                continue; 
            }
                
            typename Matrix::template MatrixOfType<ResultDataType> temp = self; 
            for (size_t j = 0; j < len; ++j) {
                temp[j][j] -= value; 
            }

            gaussian_elimination_as_mut(temp); 

            for (size_t j = 0; j < len; ++j) {

                if (!is_nearly_zero(temp[j][j])) {
                    auto pivot = temp[j][j]; 
                    for (size_t k = j; k < len; ++k) {
                        temp[j][k] /= pivot; 
                    }
                } else {
                    for (size_t k = 0; k < len; ++k){
                        ans[k][cnt] = -temp[k][j];
                    }
                    ans[j][cnt] = 1;
                    cnt++;
                }

            }
            last = value;
        } 
        return ans; 
    } 

    template <typename Matrix, typename ResultDataType = typename type_traits::template TypeUpgrade<typename Matrix::ValueType>::type> 
    auto eigenvector_depreacated (Matrix const &self) {
        auto len = self.row(); 
        if (len != self.col()) {
            throw matrix::exception::MatrixNonSquareException( __FILE__ ":" STRING(__LINE__) " " STRING(__FUNCTION__) ": the matrix is not a square matrix. "); 
        }

        using ResultType = std::vector<std::pair<ResultDataType, std::vector<ResultDataType>>>; 

        using SuggestedMatrix = typename Matrix::template MatrixOfType<ResultDataType>; 

        ResultType ans; 
        ans.reserve(len); 

        size_t cnt = 0; 
        auto eigenvalues = eigenvalue(self); 

        auto last = eigenvalues[0]; 
        for (size_t i = 0; i < len; ++i) {
            lassert (i < eigenvalues.size());
            auto value = eigenvalues[i]; 

            if (i != 0 && last == value) 
                continue; 
            
            Matrix temp = self; 
            for (size_t j = 0; j < len; ++j) {
                temp[j][j] -= value; 
            }

            gaussian_elimination_as_mut(temp); 

            for (size_t j = 0; j < len; ++j) {
                if (!is_nearly_zero(temp[j][j])) {
                    auto pivot = temp[j][j]; 
                    for (size_t k = j; k < len; ++k) {
                        temp[j][k] /= pivot; 
                    }
                } else {
                    std::vector<ResultDataType> t; 
                    t.resize(len); 
                    for (size_t k = 0; k < len; ++k) 
                        t[k] = temp[k][j]; 
                    ans.push_back({value, std::move(t)}); 
                }
            }
        } 
        return ans; 
    } 
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\eigen.png" style="zoom:50%;" />

<img src="D:\SUSTech\2022Spring\CPP\Project\res\eigen2.png" style="zoom:50%;" />

### Traces

```cpp
        ValueType trace() const {
            Use matrix::exception;
            auto row = m_row;
            if (row != (size() / row)){
                throw MatrixNonSquareException("LinearOwnedMatrix trace with non-square matrix. ");
            }
            ValueType trace{};
            for (size_t i = 0; i < row; i++){
                trace = trace + (*this)[i][i];
            }
            return trace;
        }
```

![](D:\SUSTech\2022Spring\CPP\Project\res\trace.png)

### Inverse

```cpp
        LinearOwnedMatrix adjacent() const {
            Use matrix::exception;
            size_t row = m_row;
            if (size() / row != row){
                throw MatrixStructureMismatchingException("LinearOwnedMatrix adjacent with non-square matrix. ");
            }
            return adjacent_cal(row);
        }

        LinearOwnedMatrix inverse() const {
            Use matrix::exception;
            auto row = m_row;
            if (size() / row != row){
                throw MatrixStructureMismatchingException("LinearOwnedMatrix inverse with non-square matrix. ");
            }
            ValueType det = determinant();
            // if (is_nearly_zero(det)){
                // throw MatrixStructureDeterminentEqualsZeroException("LinearOwnedMatrix inverse with determinent-equals-zero matrix.");
            // }
            This ans(row, row);
            This adj = adjacent();
            for (size_t i = 0; i < row; ++i){
                for (size_t j = 0; j < row; ++j){
                    ans[i][j] = adj[i][j] / det;
                }
            }
            return ans;
        }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\inverse.png" style="zoom:50%;" />

### Determinant

```cpp
        ValueType determinant_calculate(LinearOwnedMatrix const &matrix, size_t size) const { 
            if (size == 1){
                return matrix[0][0];
            }
            ValueType ans{};
            for (size_t i = 0; i < size; ++i){
                ans = ans + matrix[0][i] * determinant_calculate(determinant_cut(matrix, size - 1, i),size - 1) * (i % 2 ? -1 : 1);
            }
            return ans;
        }

        LinearOwnedMatrix determinant_cut(LinearOwnedMatrix const &matrix, size_t size, size_t i) const {
            This temp (size, size);
            for (size_t r = 0; r < size; ++r) {
                for (size_t c = 0; c < size; ++c) {
                    temp[r][c] = matrix[r + 1][c + (c >= i)];
                }
            }
            return temp;
        }
```

<img src="D:\SUSTech\2022Spring\CPP\Project\res\determinant.png" style="zoom:50%;" />

### Reshape

```cpp
        LinearOwnedMatrix reshape(size_t r, size_t c) const {
            Use matrix::exception;
            if (r * c != size()){
                throw MatrixStructureMismatchingException("LinearOwnedMatrix reshape with not matching size");
            }
            
            Super base = *this; 
            return (std::move(base), r);  
        }
```

![](D:\SUSTech\2022Spring\CPP\Project\res\reshape.png)

### Slicing

```cpp
        LinearOwnedMatrix slice(size_t r0, size_t r1, size_t c0, size_t c1) const {
            Use matrix::exception;
            if (r1 < r0 || c1 < c0 || r0 > row() || r1 > row() || c0 > col() || c1 > col()){
                throw MatrixStructureInvalidSizeException("LinearOwnedMatrix slice with invalid size");
            }
            This ans(r1-r0+1, c1-c0+1);
            for (size_t i = 0; i < r1-r0+1; ++i){
                for (size_t j = 0; j < c1-c0+1; ++j){
                    ans[i][j] = (*this)[r0+i][c0+j];
                }
            }
            return ans;
        }
```

![](D:\SUSTech\2022Spring\CPP\Project\res\slice.png)

### Convolution

```cpp
        LinearOwnedMatrix convolution(LinearOwnedMatrix & rhs) const {
            Use matrix::exception;
            if (row() < rhs.row() || col() < rhs.col()){
                throw MatrixStructureMismatchingException("LinearOwnedMatrix convolution with bigger core");
            }
            auto ans_row = row() + rhs.row() - 1, ans_col = col() + rhs.col() - 1;
            This ans(ans_row, ans_col);
            for (size_t i = 0; i < ans_row; ++i) {
                for (size_t j = 0; j < ans_col; ++j) {
                    for (size_t m = 0; m < rhs.row(); ++m) {
                        for (size_t n = 0; n < rhs.col(); ++n) {
                            if (i - m < row() && j - n < col())
                                ans[i][j] += (*this)[i - m][j - n] * rhs[m][n];
                        }
                    }
                }
            }
            return ans;
        }
```

![](D:\SUSTech\2022Spring\CPP\Project\res\convolution.png)

### OpenCV Transfer

```C++
            template <typename InnerType = ValueType, typename CV_Mat> 
            static This from_cv_mat(CV_Mat const &self) {
                This ans (self.rows, self.cols); 
                for (size_t i = 0; i < self.rows; ++i) {
                    for (size_t j = 0; j < self.cols; ++j) {
                        ans[i][j] = self.template at<InnerType>(i, j); 
                    }
                }
            }
```



### Exceptions

![](D:\SUSTech\2022Spring\CPP\Project\res\exception1.png)

![exception2](D:\SUSTech\2022Spring\CPP\Project\res\exception2.png)

![exception3](D:\SUSTech\2022Spring\CPP\Project\res\exception3.png)

