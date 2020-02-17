// gordon zuehlke 2/11/20
// Test class for XYEnvironment

#include "gtest/gtest.h"
#include "environment/xyenv/xy_environment.h"
#include "environment/xyenv/wall.h"

using namespace::testing;

class TestXYEnvironment: public Test {
public:
    TestXYEnvironment() {
        agent1 = std::make_shared<MockAgent>();
        wall1 = std::make_shared<Wall>();
        env.add_to(agent1,loc); 
    }

    XYEnvironment env{10, 12};
    XYLocation loc{3,4};
    std::shared_ptr<EnvironmentObject> agent1;
    std::shared_ptr<EnvironmentObject> wall1;
};


TEST_F(TestXYEnvironment, testAddObjects) {
    XYLocation xyloc{9,9};
    env.add_to(wall1, xyloc);
    ASSERT_EQ(env.object_total(xyloc), size_t(1));
}

/*

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
*/
    //TODO: test duplicate agents and agent equality
    //TODO: test multiple agents at one location
    //TODO: test multiple locations for one agent
 











/*################################################################################################*/ 
/*void compare(MockAgent eo) {
    std::vector<MockAgent> vec;
    MockAgent mock2;

    vec.push_back(eo);
    auto it = vec.begin();
    if (!(*it == mock2)) std::cout << "Not equal." << std::endl;    
}
  
TEST_F(TestXYEnvironment, testAddObjects) {
    MockAgent mock1;
    compare(mock1);
}

void compare1(EnvironmentObject* eo) {
    std::vector<EnvironmentObject*> vec;
    EnvironmentObject* mock2 = new MockAgent();

    vec.push_back(eo);
    auto it = vec.begin();
    if (!((**it) == *mock2)) std::cout << "Not equal." << std::endl;

    delete mock2;
    mock2 = 0;    
}
  
TEST_F(TestXYEnvironment, testAddObjects1) {
    EnvironmentObject* mock1 = new MockAgent();
    compare1(mock1);

    delete mock1;
    mock1 = 0;
}*/

/*void compare2(std::shared_ptr<EnvironmentObject> eo) {
    std::vector<std::shared_ptr<EnvironmentObject>> vec;
    std::shared_ptr<EnvironmentObject> mock2 = std::make_shared<MockAgent>();

    vec.push_back(eo);
    auto it = vec.begin();
    if (!(**it == *mock2)) std::cout << "Not equal." << std::endl;    
}
  
TEST_F(TestXYEnvironment, testAddObjects2) {
    std::shared_ptr<EnvironmentObject> mock1 = std::make_shared<MockAgent>();
    compare2(mock1);
}*/

/*##############################################################################################*/







 
