#include "def/format.hpp"

TEST_METHOD {
    Use matrix; 
    bassert_eq("{} {}"_format("Hello", "World"), "Hello World"); 
}

TEST_METHOD {
    Use matrix; 
    bassert_eq("{} + {} = {}"_format(15, 25, 15 + 25), "15 + 25 = 40"); 
}

TEST_METHOD {
    Use matrix; 
    bassert_eq("{}"_format(7), "7"); 
}

TEST_METHOD {
    Use matrix; 
    bassert_eq("My name is {}, nice to meet you! "_format("Cutie Deng"), 
        "My name is Cutie Deng, nice to meet you! "); 
}

TEST_METHOD {
    Use matrix; 
    bassert_eq("Hello Kitty"_format(), "Hello Kitty"); 
}

TEST_METHOD {
    Use matrix; 
    bassert_eq("{}!"_format("RUN"), "RUN!"); 
}

TEST_METHOD {
    Use matrix; 
    bassert_eq("{}!={}"_format(1.5, std::numeric_limits<double>::infinity()), "1.500000!=inf"); 
}

TEST_METHOD {
    Use matrix; 
    bassert_eq("{{}}"_format(), "{}"); 
}

TEST_METHOD {
    Use matrix; 
    bassert_eq("{}"_format("{}"_format("{}"_format("{{}}"))), "{{}}"); 
}

TEST_METHOD {
    Use matrix; 
    bassert_eq ("{{{}}}"_format("Good night!"), "{Good night!}");
}