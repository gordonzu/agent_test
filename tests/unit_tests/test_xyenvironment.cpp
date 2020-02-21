// gordon zuehlke 2/11/20
// Test class for XYEnvironment

#include "gtest/gtest.h"
#include "environment/xyenv/xy_environment.h"
#include "environment/xyenv/wall.h"
#include "mock_agent.h"

using namespace::testing;
using EnvPtr = std::shared_ptr<EnvironmentObj>;

class TestXYEnvironment: public Test {
public:
    TestXYEnvironment() {
        agent1 = std::make_shared<MockAgent>();
        wall1 = std::make_shared<Wall>();
        env.add_to(agent1, loc); 
    }

    XYEnvironment env{10,12};
    XYLocation loc{3,4};
    EnvPtr agent1;
    EnvPtr wall1;
};


TEST_F(TestXYEnvironment, testAddObject) {
    EXPECT_EQ(env.get_location(agent1), loc);
    EXPECT_EQ(env.objects_at_location(loc), size_t(1));
}

TEST_F(TestXYEnvironment, testAddObject2) {
    XYLocation yy{9,9};
    env.add_to(wall1, yy);
    EXPECT_EQ(env.objects_at_location(yy), size_t(1));
    EXPECT_EQ(env.get_num_objects(), size_t(2));
    EXPECT_EQ(env.get_num_agents(), size_t(1));
}

TEST_F(TestXYEnvironment, test_add_object_twice) {
    EXPECT_EQ(env.objects_at_location(loc), size_t(1));
    XYLocation xy{5,5};
    env.add_to(agent1, xy);
    EXPECT_EQ(env.objects_at_location(xy), size_t(1));
    EXPECT_EQ(env.get_location(agent1), xy);
}

TEST_F(TestXYEnvironment, test_objects_are_unique) {
    EnvPtr agent2 = std::make_shared<MockAgent>();
    EXPECT_NE(agent1, agent2);
}

TEST_F(TestXYEnvironment, test_add_two_objects_one_location) {
    XYLocation xy{9,8};
    env.move_to_absolute_location(agent1,xy);
    EXPECT_EQ(env.objects_at_location(xy), size_t(1));
    EnvPtr agent2 = std::make_shared<MockAgent>();
    env.move_to_absolute_location(agent2,xy);
    EXPECT_EQ(env.objects_at_location(xy), size_t(2));
}

TEST_F(TestXYEnvironment, change_object_location) {
    XYLocation xy{5,6};
    env.add_to(agent1, xy);
    EXPECT_EQ(env.objects_at_location(xy), size_t(1));
    EXPECT_EQ(env.objects_at_location(loc), size_t(0));
}

TEST_F(TestXYEnvironment, test_get_current_location) {
    XYLocation xy{3,4};
    EXPECT_EQ(env.get_location(agent1), xy);
    XYLocation xy2{12,5};
    EXPECT_NE(env.get_location(agent1), xy2);
}

TEST_F(TestXYEnvironment, test_move_to_absolute_location) {
    XYLocation xy{5,3};
    env.move_to_absolute_location(agent1, xy);
    EXPECT_EQ(env.get_location(agent1), xy);
    EXPECT_NE(env.get_location(agent1), loc); 
}

TEST_F(TestXYEnvironment, test_move_object) {
    XYLocation xy{5,5};
    env.add_to(agent1, xy);
    EXPECT_EQ(env.get_location(agent1), xy);

    XYLocation loc54{5,4};
    XYLocation loc64{6,4};
    XYLocation loc65{6,5};

    env.move_object(agent1, XYLocation::Direction::NORTH);
    EXPECT_EQ(env.get_location(agent1), loc54);
    env.move_object(agent1, XYLocation::Direction::EAST);
    EXPECT_EQ(env.get_location(agent1), loc64);
    env.move_object(agent1, XYLocation::Direction::SOUTH);
    EXPECT_EQ(env.get_location(agent1), loc65);
    env.move_object(agent1, XYLocation::Direction::WEST);
    EXPECT_EQ(env.get_location(agent1), xy);
}

TEST_F(TestXYEnvironment, test_is_blocked) {
    XYLocation xy{5,5};
    env.add_to(agent1, xy);
    EXPECT_EQ(env.blocked(xy), false);
    env.add_to(wall1, xy);
    EXPECT_EQ(env.blocked(xy), true);
}

TEST_F(TestXYEnvironment, test_move_with_blocking_walls) {
    XYLocation xy{5,5};
    env.add_to(agent1, xy);

    XYLocation xyNorth{5,6};
    XYLocation xySouth{5,4};
    XYLocation xyWest{4,5};
    XYLocation xyEnd{6,5};

    EnvPtr northwall = std::make_shared<Wall>();
    EnvPtr southwall = std::make_shared<Wall>();
    EnvPtr westwall = std::make_shared<Wall>();
    env.add_to(northwall, xyNorth);
    EXPECT_EQ(env.blocked(xyNorth), true);
   
    env.add_to(southwall, xySouth);
    env.add_to(westwall, xyWest);
    EXPECT_EQ(env.get_num_objects(), size_t(4));
    
    env.move_object(agent1, XYLocation::Direction::NORTH); // should not move
    env.move_object(agent1, XYLocation::Direction::SOUTH); // should not move
    env.move_object(agent1, XYLocation::Direction::WEST);  // should not move
    env.move_object(agent1, XYLocation::Direction::EAST);  // SHOULD move
    EXPECT_EQ(env.get_location(agent1), xyEnd);
}

TEST_F(TestXYEnvironment, test_get_objects_near) {
    XYLocation loc{5,5};
    XYLocation loc2{7,4};
    XYLocation loc3{5,7};
    XYLocation loc4{3,10};
    XYLocation loc5{3,11};

    env.add_to(agent1, loc);

    EnvPtr b = std::make_shared<MockAgent>();
    EnvPtr c = std::make_shared<MockAgent>();
    EnvPtr w = std::make_shared<MockAgent>();

    env.add_to(b, loc2);
    env.add_to(c, loc3);
    env.add_to(w, loc4);

    std::vector<EnvPtr> avec = env.get_objects_near(agent1, 3);
    ASSERT_EQ(avec.size(), size_t(2));

    //std::vector<EnvironmentObject> bvec = env.get_objects_near(b, 3);
    //ASSERT_EQ(bvec.size(), size_t(1));

    //env.move_object(b, XYLocation::Direction::SOUTH);

    //bvec = env.get_objects_near(b, 3);
    //ASSERT_EQ(bvec.size(), size_t(2));

    //env.add_to(c, loc5);
    //std::vector<EnvironmentObject> cvec = env.get_objects_near(c, 4);
    //ASSERT_EQ(cvec.size(), size_t(1));



/*
    XYLocation loc{5,5};
    XYLocation loc2{7,4};
    XYLocation loc3{5,7};
    XYLocation loc4{3,10};
    XYLocation loc5{3,11};
    EnvPtr agent2 = std::make_shared<MockAgent>();
    EnvPtr agent3 = std::make_shared<MockAgent>();
    
    env.add_to(agent1, loc);
    env.add_to(agent2, loc2);

    EXPECT_EQ(env.get_objects_near(agent1, 3).size(), size_t(2));
    EXPECT_EQ(env.get_objects_near(agent2, 3).size(), size_t(1));

    env.move_object(agent2, XYLocation::Direction::SOUTH);
    EXPECT_EQ(env.get_objects_near(agent2, 3).size(), size_t(2));
    
    env.add_to(agent3, loc5); 
    EXPECT_EQ(env.get_objects_near(agent3, 4).size(), size_t(1));*/
}




































