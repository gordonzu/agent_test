// gordon zuehlke 2/11/20
// Test class for XYEnvironment

#include "gtest/gtest.h"
#include "environment/xyenv/xy_environment.h"

using namespace::testing;

class TestXYEnvironment: public Test {
public:
    TestXYEnvironment() {
        env.add_agent(agent, loc);
    }

    Agent agent;
    XYLocation loc{3,4};
    XYEnvironment env{10, 12};
};

TEST_F(TestXYEnvironment, test_data_structures) {
    ASSERT_EQ(env.map_size(), size_t(120));
    ASSERT_EQ(env.inner_vector_size(loc), size_t(1));
}

TEST_F(TestXYEnvironment, test_new_insertions) { 
    //TODO: test new instertion in the allotted matrix
    //TODO: test new insertion rows and columns beyond the existing matrix
    //TODO: test duplicate agents
    //TODO: test multiple agents at one location 
}

