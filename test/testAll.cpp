#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include "engine/container/container.cpp"
#include "engine/world/world.cpp"


TEST(testAll, ObjectNull)
{

}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
