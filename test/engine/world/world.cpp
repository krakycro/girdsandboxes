#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include <container/container.hpp>
#include <world/world.hpp>

namespace testWorld
{

  std::unique_ptr<Container::Grid> GRID;
  std::unique_ptr<World::Item> ITEM;
  std::unique_ptr<World::Space> SPACE;

  TEST(testWorld, ItemCreate)
  {
      ASSERT_NO_THROW({
          GRID = std::unique_ptr<Container::Grid>(new Container::Grid(2, 2, 2));
          ITEM = std::unique_ptr<World::Item>(new World::Item());
      });
  }

  TEST(testWorld, SpaceCreate)
  {
      ASSERT_NO_THROW({
          SPACE = std::unique_ptr<World::Space>(new World::Space());
      });
  }

  TEST(testWorld, SpaceTest)
  {
      auto b1 = GRID->at(1,1,1);
      // b1->insert<Container::Object>();
      SPACE->insert<Container::Object>();
  }

}

// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
// }
