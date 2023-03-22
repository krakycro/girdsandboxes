#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include "container.hpp"

std::unique_ptr<Grid> GRID;

TEST(Container, Create) {
   EXPECT_NO_THROW({
      GRID = std::unique_ptr<Grid>(new Grid(2, 2, 2));
   });
}

TEST(Container, Populate) {
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

TEST(Container, Check1) {
   for(int i=0;i<GRID->size_x;i++)
   {
      for(int j=0;j<GRID->size_y;j++)
      {
         for(int k=0;k<GRID->size_z;k++)
         {
            ASSERT_TRUE(GRID->at(i,j,k,0)->val == i+j+k);
            ASSERT_TRUE(GRID->at(i,j,k,1)->val == 2*(i+j+k));
         }
      }
   }
}

TEST(Container, Swap) {
   EXPECT_NO_THROW({
      Grid::swap(GRID->at(1,1,1), GRID->at(1,1,0));
   });
}

TEST(Container, Check2) {
   ASSERT_TRUE(GRID->at(1,1,0,0)->val == 3);
   ASSERT_TRUE(GRID->at(1,1,0,1)->val == 6);
   ASSERT_TRUE(GRID->at(1,1,1,0)->val == 2);
   ASSERT_TRUE(GRID->at(1,1,1,1)->val == 4);
}

TEST(Container, Move) {

   auto b1 = GRID->at(1,1,0);
   auto o1 = b1->at(0);
   auto b2 = GRID->at(1,1,1);
   EXPECT_NO_THROW({
      b2->insert(b1->at(0));
   });
   o1->val = 6;
   auto o2 = b2->at(0);
   auto c2 = o2->get_coord();

   ASSERT_TRUE(b1->obj.size() == 2);
   ASSERT_TRUE(b2->obj.size() == 3);
   ASSERT_TRUE(o2->val == 6);
   ASSERT_TRUE(c2->z == 1);

   EXPECT_NO_THROW({
      ASSERT_TRUE(GRID->at(1,1,0,0) == nullptr);
      ASSERT_TRUE(GRID->at(1,1,0,1)->val == 6);
      ASSERT_TRUE(GRID->at(1,1,1,0)->val == 6);
      ASSERT_TRUE(GRID->at(1,1,1,1)->val == 2);
      ASSERT_TRUE(GRID->at(1,1,1,2)->val == 4);
   });

   auto o3 = b1->at(0);
   EXPECT_NO_THROW({
      ASSERT_TRUE(o3.get() == nullptr);
   });
}

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}