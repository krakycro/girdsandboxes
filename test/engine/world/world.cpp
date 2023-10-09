#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include <container.hpp>
#include <world.hpp>

std::unique_ptr<Container::Grid> GRID;

TEST(World, ObjectNull)
{

}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}