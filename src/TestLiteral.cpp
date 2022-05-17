#include "BasicCal.hpp"

namespace Mx = Matrix; 

TEST_METHOD {
    using namespace Mx; 
    auto v = 1233211234567_pn; 
    bassert_eq_actual_expect(to_string(v), "1233211234567");
}

TEST_METHOD {
    using namespace Mx; 
    auto v = 0xf_pn; 
    bassert_eq_actual_expect(to_string(v), "15");
}

TEST_METHOD {
    using namespace Mx; 
    auto v = 0b1111'1111_pn;
    bassert_eq_actual_expect(to_string(v), "255");
}

TEST_METHOD {
    using namespace Mx; 
    auto v = 077_pn; 
    bassert_eq_actual_expect(to_string(v), "63");
}

TEST_METHOD {
    using namespace Mx; 
    auto v = 777_pn; 
    for (auto i = 0; i < 19; ++i)
        mul_u32_then_eq(v, 777); 
    bassert_eq_actual_expect(to_string(v), ""); 
}