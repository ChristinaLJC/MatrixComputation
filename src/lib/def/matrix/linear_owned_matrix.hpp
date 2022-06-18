#pragma once

#include "std.hpp"
#include "def/mexception.hpp"

namespace matrix::exception {
    struct MatrixStructureException : public MatrixBaseException {
        using MatrixBaseException::MatrixBaseException;
        ~MatrixStructureException() = 0;
    };

    MatrixStructureException::~MatrixStructureException() {}

    struct MatrixStructureMismatchingException : public MatrixStructureException {
        using MatrixStructureException::MatrixStructureException;
    };

    struct MatrixStructureNullException : public MatrixStructureException {
        using MatrixStructureException::MatrixStructureException;
    };

    struct MatrixStructureInvalidSizeException : public MatrixStructureException {
        using MatrixStructureException::MatrixStructureException;
    };

    struct MatrixStructureDeterminantEqualsZeroException : public MatrixStructureException {
        using MatrixStructureException::MatrixStructureException;
    };

    struct MatrixNonSquareException : public MatrixStructureException {
        using MatrixStructureException::MatrixStructureException; 
    }; 
}

namespace matrix::type_traits {
    template <typename T>
    struct TypeUpgrade {
        using type = double;
    };

    template <typename T>
    struct TypeUpgrade <std::complex<T>> {
        using type = std::complex<typename TypeUpgrade<T>::type>;
    };
}

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
                // if (!size()) {
                //     throw MatrixStructureNullException
                // }
            }
        private:
            void row_col_upperbound_check(size_t row, size_t col) {
                if (!row || !col) {
                    throw matrix::exception::MatrixStructureNullException ("LinearOwnedMatrix cannot be initialized as empty size. ");
                } else if (std::numeric_limits<size_t>::max() / row < col) {
                    throw matrix::exception::MatrixStructureInvalidSizeException ("LinearOwnedMatrix cannot occupy a size larger than size_t type. ");
                }
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

        LinearOwnedMatrix adjacent_cal(size_t size) const{
            This ans (size, size);
            if (size == 1){
                ans[0][0] = 1;
            } else {
                This temp(size-1, size-1);
                for (size_t i = 0; i < size; ++i) {
                    for (size_t j = 0; j < size; ++j) {
                        for (size_t k = 0; k < size - 1; ++k) {
                            for (size_t t = 0; t < size - 1; ++t) {
                                temp[k][t] = (*this)[k >= i ? k + 1 : k][t >= j ? t + 1 : t];
                            }
                        }
                        ans[j][i] = determinant_calculate(temp, size - 1) * ((i + j) % 2 == 1 ? -1 : 1);
                    }
                }
            }
            return ans;
        }

        public:
            LinearOwnedMatrix(size_t r, size_t c):
                ContainerType<ValueType>(r * c), m_row(r) {
                    row_col_upperbound_check(r, c);
                }

            template <typename T, template <typename ...> typename Container>
            LinearOwnedMatrix(LinearOwnedMatrix<T, Container> const &self): Super(self.size()), m_row(self.row()) {
                for (size_t i{}; i < self.size(); ++i) {
                    ((Super&)*this)[i] = self[i / self.row()][i % self.row()];
                }
            }

            struct Visiter{
                LinearOwnedMatrix &self;
                size_t row;
                Visiter(LinearOwnedMatrix &self, size_t row): self(self), row(row) {}
                ValueType &operator[] (size_t index) {
                    lassert (index < self.size() / self.row());
                    return ((Super&)self)[row * (self.size() / self.row()) + index];
                }
            };
            struct ConstVisitor {
                LinearOwnedMatrix const &self;
                size_t row;
                ConstVisitor(LinearOwnedMatrix const &self, size_t row): self(self), row(row) {}
                ValueType const &operator[] (size_t index) {
                    lassert (index < self.size() / self.row());
                    return ((Super const &)self)[row * (self.size() / self.row()) + index];
                }
            };

            Visiter operator[] (size_t index) {
                lassert (index < m_row);
                return Visiter(*this, index);
            }

            ConstVisitor operator[] (size_t index) const {
                lassert (index < m_row);
                return ConstVisitor(*this, index);
            }

            size_t row() const noexcept {
                return m_row;
            }

            size_t col() const noexcept {
                return this->size() / m_row;
            }

            size_t size() const noexcept {
                return this->Super::size();
            }

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

            LinearOwnedMatrix operator*(ValueType const &rhs) const {
                return LinearOwnedMatrix ((Super&)*this * rhs, row());
            }

            LinearOwnedMatrix operator/(ValueType const &rhs) const {
                return LinearOwnedMatrix ((Super&)*this / rhs, row());
            }

            LinearOwnedMatrix transposition() const {
                This ans (size() / row(), row());
                for (size_t r = 0; r < size() / row(); ++r) {
                    for (size_t c = 0; c < row(); ++c) {
                        ans[r][c] = (*this)[c][r];
                    }
                }
                return ans;
            }

            using Super::max;
            using Super::min;
            using Super::sum;

            ValueType avg() const {
                return sum() / size();
            }

            ValueType determinant() const {
                Use matrix::exception;
                size_t row = m_row;
                if (row != (size() / row)){
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix determinant with non-square matrix. ");
                }
                return determinant_calculate(*(this), row);
            }

            ValueType trace() const {
                Use matrix::exception;
                auto row = m_row;
                if (row != (size() / row)){
                    throw MatrixStructureMismatchingException("LinearOwnedMatrix trace with non-square matrix. ");
                }
                ValueType trace{};
                for (size_t i = 0; i < row; i++){
                    trace = trace + (*this)[i][i];
                }
                return trace;
            }

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

            static LinearOwnedMatrix with_size(size_t k) {
                // if (std::numeric_limits<size_t>::max() / k < k) {
                //     abort();
                //     // Cannot construct such a large value!
                // }
                return LinearOwnedMatrix(k, k);
            }

            static LinearOwnedMatrix with_identity_size(size_t k) {
                This ans (k, k);
                for (size_t i = 0; i < k; ++i) {
                    ans[i][i] = 1;
                }
                return ans;
            }

            This operator~ () const {
                return (this->apply(std::conj), col()); 
            }
    };
    
}