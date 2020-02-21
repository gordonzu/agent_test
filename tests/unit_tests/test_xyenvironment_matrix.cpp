// gordon zuehlke 2/20/20
// Test class for XYEnvironment

#include "gtest/gtest.h"
//#include "test_xyenvironment.cpp"
#include "environment/xyenv/xy_environment.h"
#include "environment/xyenv/wall.h"
//#include "mock_agent.h"


using namespace::testing;
using EnvPtr = std::shared_ptr<EnvironmentObj>;

class TestXYEnvironmentMatrix: public Test {
public:
    TestXYEnvironmentMatrix() {
        //agent1 = std::make_shared<MockAgent>();
        //wall1 = std::make_shared<Wall>();
        //env.add_to(agent1, loc); 
    }

    XYEnvironment env{10,12};
    //XYLocation loc{3,4};
    //EnvPtr agent1;
    //EnvPtr wall1;
};

TEST_F(TestXYEnvironmentMatrix, test_matrix_size) {
    //EXPECT_EQ(env.matrix_size(), size_t(120));   
}




