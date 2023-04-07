#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include "container.hpp"

std::unique_ptr<Container::Grid> GRID;

TEST(Container, Create)
{
   EXPECT_NO_THROW({
      GRID = std::unique_ptr<Container::Grid>(new Container::Grid(2, 2, 2));
   });
}

TEST(Container, Populate)
{
   EXPECT_NO_THROW({
      for(int i=0;i<GRID->size_x;i++)
      {
         for(int j=0;j<GRID->size_y;j++)
         {
            for(int k=0;k<GRID->size_z;k++)
            {
                  GRID->at(i,j,k)->insert();
                  GRID->at(i,j,k)->insert();
                  GRID->at(i,j,k,0)->val = i+j+k;
                  GRID->at(i,j,k,1)->val = 2*(i+j+k);
            }
         }
      }
   });
}

TEST(Container, CheckInsert)
{
   for(int i=0;i<GRID->size_x;i++)
   {
      for(int j=0;j<GRID->size_y;j++)
      {
         for(int k=0;k<GRID->size_z;k++)
         {
            ASSERT_TRUE(GRID->at(i,j,k,0)->val == i+j+k);
            ASSERT_TRUE(GRID->at(i,j,k,1)->val == 2*(i+j+k));
            ASSERT_TRUE(GRID->at(i,j,k)->x == i);
            ASSERT_TRUE(GRID->at(i,j,k)->y == j);
            ASSERT_TRUE(GRID->at(i,j,k)->z == k);
         }
      }
   }
}

TEST(Container, CheckCoord)
{
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,0,1);
   auto o1 = b1->at(0);
   auto o2 = b2->at(0);
   auto c1 = o1->get_coord();
   auto c2 = o2->get_coord();

   ASSERT_TRUE(c1->x == 1);
   ASSERT_TRUE(c1->y == 1);
   ASSERT_TRUE(c1->z == 0);
   ASSERT_TRUE(c2->x == 1);
   ASSERT_TRUE(c2->y == 0);
   ASSERT_TRUE(c2->z == 1);
}

TEST(Container, CheckRoot)
{
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,0,1);
   auto o1 = b1->at(0);
   auto o2 = b2->at(0);

   ASSERT_TRUE(o1->root == b1);
   ASSERT_TRUE(o1->self == o1);

   ASSERT_TRUE(o2->root == b2);
   ASSERT_TRUE(o2->self == o2);
}

TEST(Container, Swap)
{
   EXPECT_NO_THROW({
      Container::Grid::swap(GRID->at(1,1,1), GRID->at(1,1,0));
   });
}

TEST(Container, CheckSwaped)
{
   ASSERT_TRUE(GRID->at(1,1,0,0)->val == 3);
   ASSERT_TRUE(GRID->at(1,1,0,1)->val == 6);
   ASSERT_TRUE(GRID->at(1,1,1,0)->val == 2);
   ASSERT_TRUE(GRID->at(1,1,1,1)->val == 4);

   ASSERT_TRUE(GRID->at(1,1,0)->x == 1);
   ASSERT_TRUE(GRID->at(1,1,0)->y == 1);
   ASSERT_TRUE(GRID->at(1,1,0)->z == 0);

   ASSERT_TRUE(GRID->at(1,1,1)->x == 1);
   ASSERT_TRUE(GRID->at(1,1,1)->y == 1);
   ASSERT_TRUE(GRID->at(1,1,1)->z == 1);
}

TEST(Container, CheckSwapedCoord)
{
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,0,1);
   auto o1 = b1->at(0);
   auto o2 = b2->at(0);
   auto c1 = o1->get_coord();
   auto c2 = o2->get_coord();

   ASSERT_TRUE(c1->x == 1);
   ASSERT_TRUE(c1->y == 1);
   ASSERT_TRUE(c1->z == 0);
   ASSERT_TRUE(c2->x == 1);
   ASSERT_TRUE(c2->y == 0);
   ASSERT_TRUE(c2->z == 1);
}

TEST(Container, CheckSwapedRoot)
{
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,0,1);
   auto o1 = b1->at(0);
   auto o2 = b2->at(0);

   ASSERT_TRUE(o1->root == b1);
   ASSERT_TRUE(o1->self == o1);

   ASSERT_TRUE(o2->root == b2);
   ASSERT_TRUE(o2->self == o2);
}

TEST(Container, Move)
{
   auto b1 = GRID->at(1,1,0);
   auto o1 = b1->at(0);
   auto b2 = GRID->at(1,1,1);
   EXPECT_NO_THROW({
      b2->insert(b1->at(0));
   });
   o1->val = 11;
   auto o2 = b2->at(0);
   auto c2 = o2->get_coord();

   ASSERT_TRUE(b1->obj.size() == 2);
   ASSERT_TRUE(b2->obj.size() == 3);
   ASSERT_TRUE(o2->val == 11);
   ASSERT_TRUE(c2->x == 1);
   ASSERT_TRUE(c2->y == 1);
   ASSERT_TRUE(c2->z == 1);

   ASSERT_DEATH({GRID->at(1,1,0,0)->val = 5;}, "");
   ASSERT_TRUE(GRID->at(1,1,0,0) == nullptr);
   ASSERT_TRUE(GRID->at(1,1,0,1)->val == 6);
   ASSERT_TRUE(GRID->at(1,1,1,0)->val == 11);
   ASSERT_TRUE(GRID->at(1,1,1,1)->val == 2);
   ASSERT_TRUE(GRID->at(1,1,1,2)->val == 4);

   auto o3 = b1->at(0);
   ASSERT_TRUE(o3.get() == nullptr);
}

TEST(Container, GetKey)
{
   auto b = GRID->at(1,1,0);
   auto o1 = b->at(1);
   auto o2 = b->at(0);

   ASSERT_TRUE(b->get(o1->key)->val == 6);
   ASSERT_DEATH(b->get(o2->key), "");
}

TEST(Container, MoveBack)
{
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,1,1);

   EXPECT_NO_THROW({
      b1->insert(b2->at(0));
   });

   auto o1 = b1->at(0);
   auto c1 = o1->get_coord();

   ASSERT_TRUE(b1->obj.size() == 2);
   ASSERT_TRUE(b2->obj.size() == 3);
   ASSERT_TRUE(o1->val == 11);
   ASSERT_TRUE(c1->z == 0);

   ASSERT_TRUE(GRID->at(1,1,0,0)->val == 11);
   ASSERT_TRUE(GRID->at(1,1,0,1)->val == 6);
   ASSERT_TRUE(GRID->at(1,1,1,0) == nullptr);
   ASSERT_TRUE(GRID->at(1,1,1,1)->val == 2);
   ASSERT_TRUE(GRID->at(1,1,1,2)->val == 4);
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}