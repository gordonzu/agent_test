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
    //TODO: test flag set back to true after returning false
    //TODO: test duplicate agents and agent equality
    //TODO: test multiple agents at one location
    //TODO: test multiple locations for one agent
    
TEST_F(TestXYEnvironment, test_matrix_size) {
    ASSERT_EQ(env.matrix_size(), size_t(120));   
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
    Agent a;
    XYLocation xy{8,9};
    ASSERT_EQ(env.inner_vector_size(xy), size_t(0));
    
    env.add_agent(a, xy);
    EXPECT_EQ(env.inner_vector_size(xy), size_t(1));
}

TEST_F(TestXYEnvironment, test_add_both_dimensions_outofbounds) {
    Agent a;
    XYLocation xy{12,14};
    ASSERT_EQ(env.inner_vector_size(xy), size_t(0));
    ASSERT_EQ(env.matrix_size(), size_t(120));   
 
    env.add_agent(a, xy);
    EXPECT_EQ(env.inner_vector_size(xy), size_t(1));
    EXPECT_EQ(env.matrix_size(), size_t(168));   
    ASSERT_EQ(env.get_width(), unsigned(12));  
    ASSERT_EQ(env.get_height(), unsigned(14));  
}

TEST_F(TestXYEnvironment, test_add_outofbounds_height) {
    Agent a;
    XYLocation xy{10,14};
    EXPECT_EQ(env.inner_vector_size(xy), size_t(0));
    ASSERT_EQ(env.matrix_size(), size_t(120));   

    env.add_agent(a, xy);
    EXPECT_EQ(env.inner_vector_size(xy), size_t(1));
    EXPECT_EQ(env.matrix_size(), size_t(140)); 
    ASSERT_EQ(env.get_width(), unsigned(10));  
    ASSERT_EQ(env.get_height(), unsigned(14));
}

TEST_F(TestXYEnvironment, test_add_outofbounds_width) {
    Agent a;
    XYLocation xy{12,12};
    EXPECT_EQ(env.inner_vector_size(xy), size_t(0));
    ASSERT_EQ(env.matrix_size(), size_t(120));   

    env.add_agent(a, xy);
    EXPECT_EQ(env.inner_vector_size(xy), size_t(1));
    EXPECT_EQ(env.matrix_size(), size_t(144)); 
    ASSERT_EQ(env.get_width(), unsigned(12));  
    ASSERT_EQ(env.get_height(), unsigned(12));
}



















 
