// gordon zuehlke 2/11/20
// Test class for XYEnvironment

#include "gtest/gtest.h"
#include "environment/xyenv/xy_environment.h"
#include "environment/xyenv/wall.h"

using namespace::testing;

class TestXYEnvironment: public Test {
public:
    TestXYEnvironment() {}

    XYEnvironment env{10, 12};
    MockAgent agent1;
    MockAgent agent2;
    Wall wall;
};
    //TODO: test duplicate agents and agent equality
    //TODO: test multiple agents at one location
    //TODO: test multiple locations for one agent
    
TEST_F(TestXYEnvironment, testAddObjects) {
    //XYLocation xyloc{9,9};
    //env.add_to(wall, xyloc);
    //ASSERT_EQ(env.get_agents().size(), size_t(1));
    //ASSERT_EQ(env.get_objects().size(), size_t(2));

    //XYLocation xy{9,9};
    //ASSERT_EQ(env.inner_vector_size(xy), size_t(1));
}

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
    MockAgent a;
    XYLocation xy{8,9};
    ASSERT_EQ(env.inner_vector_size(xy), size_t(0));
    
    env.add_to(a, xy);
    EXPECT_EQ(env.inner_vector_size(xy), size_t(1));
}

TEST_F(TestXYEnvironment, test_add_both_dimensions_outofbounds) {
    MockAgent a;
    XYLocation xy{12,14};
 
    env.add_to(a, xy);
    EXPECT_EQ(env.inner_vector_size(xy), size_t(1));
    ASSERT_EQ(env.get_width(), unsigned(12));  
    ASSERT_EQ(env.get_height(), unsigned(14));  
}

TEST_F(TestXYEnvironment, test_add_outofbounds_height) {
    MockAgent a;
    XYLocation xy{10,14};

    env.add_to(a, xy);
    EXPECT_EQ(env.inner_vector_size(xy), size_t(1));
    ASSERT_EQ(env.get_width(), unsigned(10));  
    ASSERT_EQ(env.get_height(), unsigned(14));
}

TEST_F(TestXYEnvironment, test_add_outofbounds_width) {
    MockAgent a;
    XYLocation xy{12,12};

    env.add_to(a, xy);
    EXPECT_EQ(env.inner_vector_size(xy), size_t(1));
    ASSERT_EQ(env.get_width(), unsigned(12));  
    ASSERT_EQ(env.get_height(), unsigned(12));
}



















 
