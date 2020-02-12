// gordon zuehlke 2/11/20
// Test class for XYEnvironment

#include "gtest/gtest.h"
#include "environment/xyenv/xy_environment.h"

using namespace::testing;

class TestXYEnvironment: public Test {
public:
    TestXYEnvironment() {}

    Agent agent;
    XYEnvironment env{10, 12};
};

TEST_F(TestXYEnvironment, Equals) {
    ASSERT_EQ(env.map_size(), size_t(120));
}

