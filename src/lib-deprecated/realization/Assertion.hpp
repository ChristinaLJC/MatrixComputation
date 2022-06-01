namespace Matrix::Assertion {
    
    template <typename T>
    void lassert (bool expression, T &&info) {
        if (!expression)
            throw LAssertError(std::forward<T>(info));
    }

}