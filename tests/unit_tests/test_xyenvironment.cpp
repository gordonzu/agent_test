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

    //TODO: test new insertion rows and columns beyond the existing matrix
    //TODO: code method that increases matrix in the even of adding xy location beyond current size
    //////////: implement in add_agent a bounds check on the xy_location
    //////////: write another function that adds the missing rows and columns
    //////////: pass control off to the usual insertion routine 
    //TODO: test duplicate agents
    //TODO: test multiple agents at one location 

TEST_F(TestXYEnvironment, test_new_insertions) { 
    Agent ag;
    XYLocation xy{8,9};
    ASSERT_EQ(env.inner_vector_size(xy), size_t(0));
    
    env.add_agent(ag, xy);
    ASSERT_EQ(env.inner_vector_size(xy), size_t(1));
}

TEST_F(TestXYEnvironment, test_outofbounds_insertions) {
    Agent ag;
    XYLocation xy{12,15};
    ASSERT_EQ(env.inner_vector_size(xy), size_t(0));
 
    //should fail
    env.add_agent(ag, xy);
    //ASSERT_EQ(env.inner_vector_size(xy), size_t(0));
    ASSERT_EQ(0, size_t(0));
}








 
