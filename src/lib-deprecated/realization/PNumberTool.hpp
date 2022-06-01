namespace Matrix::HighPrecision {
    
    inline PNumber &trim(PNumber &self) {
        if (auto s = self.size(); s) {
            while (s && !self.at(s-1)) {
                self.pop_back();
                --s;
            }
        }
        return self;
    }

    inline bool is_zero (PNumber const &self) {
        auto &&mut_self = const_cast<PNumber &>(self);
        trim(mut_self);
        return !mut_self.size();
    }
}