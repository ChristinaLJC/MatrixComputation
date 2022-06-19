#include "def/uint128_t.hpp"

/** 
 * In this part, we should test the module operations. 
 */ 

Use matrix; 

TEST_METHOD {
    try {
        u128 d = 123_u128 % 0u; 
        bassert(false); 
    } catch (exception::MatrixZeroDividedException const &) {
        bassert(true); 
    }
}

/** 
 * Below are some simple tests for the small numbers calculation. 
 */ 
TEST_METHOD {
    u128 d = 1234u; 
    u128 f = 2u; 
    d = d % f; 
    bassert_eq(d, 0u); 
}

TEST_METHOD {
    u128 d = 107u; 
    u128 d2 = 7u; 
    bassert_eq(d2 % d, 7u); 
}

TEST_METHOD {
    u128 d = 107u; 
    u128 d2 = 7u; 
    bassert_eq(d % d2, 2u); 
}

/** 
 * Then we just consider normal uint32_t calculation. 
 */ 
TEST_METHOD {
    u128 v = 846550675u; 
    u128 v2 = 3336612905u; 
    bassert_eq (v2 % v, 796960880u); 
}

TEST_METHOD {
    u128 v = 927194889u; 
    u128 v2 = 12981347u; 
    bassert_eq (v % v2, 5519252u);    
}

/** 
 * Then consider the uint64_t calculation. 
 */ 
TEST_METHOD {
    u128 v = 1961609784233940386ull; 
    u128 m = 5859596991808492354ull; 
    bassert_eq (m % v, 1936377423340611582ull); 
}

TEST_METHOD {
    u128 v = 6197310069830761922ull; 
    u128 m = 8473987210226878ull; 
    bassert_eq (v % m, 2825419154914104ull); 
}

TEST_METHOD {
    u128 v = 8527086668290765688ull; 
    v %= 122634163245680ull; 
    bassert_eq (v, 88029492143928ull); 
}

TEST_METHOD {
    u128 v = 4376801050501152072ull; 
    v %= 2u; 
    bassert_eq (v, 0u); 
    v %= 2u; 
    bassert_eq (v, 0u); 
}

TEST_METHOD { 
    u128 v = 189598397382435909247799291393751693504_u128; 
    v %= 145773144329826350720115393386175104674_u128; 
    bassert_eq (v, 43825253052609558527683898007576588830_u128); 
}

TEST_METHOD {
    u128 v = 4376801050501152072ull; 
    v %= 2u; 
    bassert_eq (v, 0u); 
    v %= 2u; 
    bassert_eq (v, 0u); 
}

TEST_METHOD {
    u128 v = 182321562620898875226044379843818010452_u128; 
    v %= 290494433935045354198955647088790054_u128; 
    bassert_eq (v, 181552543625438143299189119146646594_u128); 
}