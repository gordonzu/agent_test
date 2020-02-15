// gordon zuehlke 2/11/20
// Test class for XYEnvironment

#include "gtest/gtest.h"
#include "environment/xyenv/xy_environment.h"

using namespace::testing;

class TestXYEnvironment: public Test {
public:
    TestXYEnvironment() {}

    XYEnvironment env{10, 12};
    Agent agent1;
    Agent agent2;
};
    //TODO: code method that increases matrix in the event of adding xy location with only one 
    // dimension larger than existing matrix
    //TODO: test duplicate agents
    //TODO: test multiple agents at one location
    
TEST_F(TestXYEnvironment, test_matrix_size) {
    ASSERT_EQ(env.map_size(), size_t(120));   
}

TEST_F(TestXYEnvironment, test_negative_matrix) {
    try {
        XYEnvironment env2{3,-6};
        FAIL() << "Expected std::runtime_error";
    }
    catch(const std::runtime_error& err) {
        EXPECT_EQ(err.what(), std::string("Invalid parameter values"));
    }
    catch(...) {
        FAIL() << "Expected std::runetime_error";
    }
}

TEST_F(TestXYEnvironment, test_add_withinbounds) { 
    Agent ag;
    XYLocation xy{8,9};
    ASSERT_EQ(env.inner_vector_size(xy), size_t(0));
    
    env.add_agent(ag, xy);
    ASSERT_EQ(env.inner_vector_size(xy), size_t(1));
}

TEST_F(TestXYEnvironment, test_add_outofbounds) {
    Agent ag;
    XYLocation xy{12,14};
    ASSERT_EQ(env.inner_vector_size(xy), size_t(0));
 
    env.add_agent(ag, xy);
    ASSERT_EQ(env.inner_vector_size(xy), size_t(1));
    ASSERT_EQ(env.map_size(), size_t(168));   
}
























 
