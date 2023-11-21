#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include <container/container.hpp>
#include <world/world.hpp>

namespace testWorld
{

   std::unique_ptr<Container::Grid> GRID;

   std::shared_ptr<Container::Object> OBJ;
   std::shared_ptr<Container::Box> BOX;

   std::shared_ptr<World::Item> ITEM;
   std::shared_ptr<World::Space> SPACE;

   TEST(testContainer, Create)
   {
       ASSERT_NO_THROW({
           GRID = std::unique_ptr<Container::Grid>(new Container::Grid(2, 2, 2));
       });
    }

   TEST(testWorld, ItemCreate)
   {
       ASSERT_NO_THROW({
           OBJ  = std::make_shared<Container::Object>();
           ITEM = std::make_shared<World::Item>();
       });
   }

   TEST(testWorld, SpaceCreate)
   {
       ASSERT_NO_THROW({
           BOX   = std::make_shared<Container::Box>();
           SPACE = std::make_shared<World::Space>();
       });
   }

   TEST(testWorld, SpaceTest)
   {
       auto b1 = GRID->at(0,0,0);
       BOX->insert<Container::Object>();
       auto o1 = BOX->at(0);
       o1->val = 1;
       std::cout << o1->val << std::endl;
       //SPACE->insert<World::Item>();
       //std::make_shared<World::Item>(SPACE->at(0));
   }

}

// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
// }
