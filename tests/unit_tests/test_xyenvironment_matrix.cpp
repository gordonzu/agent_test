// gordon zuehlke 2/20/20
// Test class for XYEnvironment

#include "gtest/gtest.h"
#include "environment/xyenv/xy_environment.h"
#include "environment/xyenv/wall.h"
#include "mock_agent.h"


using namespace::testing;
using EnvPtr = std::shared_ptr<EnvironmentObj>;

class TestXYEnvironmentMatrix: public Test {
public:
    TestXYEnvironmentMatrix() {
        agent1 = std::make_shared<MockAgent>();
        wall1 = std::make_shared<Wall>();
        env.add_to(agent1, loc); 
    }

    XYEnvironment env{10,12};
    XYLocation loc{3,4};
    EnvPtr agent1;
    EnvPtr wall1;
};

TEST_F(TestXYEnvironmentMatrix, test_matrix_size) {
    EXPECT_EQ(env.matrix_size(), size_t(120));   
}

TEST_F(TestXYEnvironmentMatrix, test_negative_matrix) {
    try {
        XYEnvironment xyFail2{3,-6};
        FAIL() << "Expected std::runtime_error";
    }
    catch(const std::runtime_error& err) {
        EXPECT_EQ(err.what(), std::string("Invalid parameter values"));
    }
    catch(...) {
        FAIL() << "Expected std::runetime_error";
    }
}

TEST_F(TestXYEnvironmentMatrix, test_add_withinbounds) { 
    EnvPtr a = std::make_shared<MockAgent>();
    XYLocation xy{8,9};
    env.add_to(a, xy);
    EXPECT_EQ(env.objects_at_location(xy), size_t(1));
}

TEST_F(TestXYEnvironmentMatrix, test_add_both_dimensions_outofbounds) {
    EnvPtr a = std::make_shared<MockAgent>();
    XYLocation xy{12,14};
    env.add_to(a, xy);
    EXPECT_EQ(env.objects_at_location(xy), size_t(1));
    EXPECT_EQ(env.matrix_size(), size_t(168));   
}

TEST_F(TestXYEnvironmentMatrix, test_add_outofbounds_height) {
    EnvPtr a = std::make_shared<MockAgent>();
    XYLocation xy{10,14};
    env.add_to(a, xy);
    EXPECT_EQ(env.objects_at_location(xy), size_t(1));
    EXPECT_EQ(env.matrix_size(), size_t(140));   
}

TEST_F(TestXYEnvironmentMatrix, test_add_outofbounds_width) {
    EnvPtr a = std::make_shared<MockAgent>();
    XYLocation xy{12,12};
    env.add_to(a, xy);
    EXPECT_EQ(env.objects_at_location(xy), size_t(1));
    EXPECT_EQ(env.matrix_size(), size_t(144));   
}

TEST_F(TestXYEnvironmentMatrix, test_state_of_object_move) {
    EXPECT_EQ(env.get_location(agent1), loc);

}
    //TODO: test Environment's agent and object vectors
    //TODO: test duplicate agents and agent equality
    //TODO: test multiple agents at one location
    //TODO: test multiple locations for one agent
 



