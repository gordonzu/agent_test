// gordon zuehlke 2/11/20
// Test class for XYEnvironment

#include "gtest/gtest.h"
#include "environment/xyenv/xy_environment.h"

using namespace::testing;

class TestXYEnvironment: public Test {
public:
    TestXYEnvironment() {}

    //XYEnvironment env{10, 12};
    //XYEnvironment env;
};

TEST_F(TestXYEnvironment, Equals) {
    //ASSERT_EQ(env.get_map_size(), size_t(120));
    ASSERT_EQ(1, 1); 
}

