#include "BasicCal.hpp" 

TEST_METHOD {
    std::vector<uint32_t> vals {1}; 
    bassert (vals.size() == 1 && vals.at(0) == 1, "vals == [1]");

    auto multi = [&vals] (uint32_t val) {
        uint64_t cache {}; 
        for (auto &&tmp: vals) {
            uint64_t cal = (uint64_t) tmp * val + cache;
            tmp = cal & 0xFFFFFFFF; 
            cache = cal >> 32; 
        }
        if (cache > 0)
            vals.push_back(cache); 
        bassert (cache <= 0xFFFFFFFF, "cache should less than the normal val. "); 
    }; 

    for (uint32_t i = 1; i < 60; ++i) 
        multi(i); 

    using std::literals::operator ""s; 

    auto correct_str = "138683118545689835737939019720389406345902876722687432540821294940160000000000000"s; 
    bassert (Matrix::to_string(vals) == correct_str, "1 * 2 * ... * 59 = "s + correct_str + ",\n\tbut actually: " + Matrix::to_string(vals)); 
}