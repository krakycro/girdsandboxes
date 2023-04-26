#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include "container.hpp"

std::unique_ptr<Container::Grid> GRID;

TEST(Container, ObjectNull)
{
   // Container::Object::null = std::make_shared<Container::Object>();
}

TEST(Container, BoxNull)
{

}

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
            ASSERT_TRUE(GRID->at(i,j,k)->get_x() == i);
            ASSERT_TRUE(GRID->at(i,j,k)->get_y() == j);
            ASSERT_TRUE(GRID->at(i,j,k)->get_z() == k);
         }
      }
   }
}

TEST(Container, CheckCoord)
{
   std::cout << "Operation" << std::endl;
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,0,1);
   auto o1 = b1->at(0);
   auto o2 = b2->at(0);
   auto c1 = o1->get_coord();
   auto c2 = o2->get_coord();

   std::cout << "Checking" << std::endl;
   ASSERT_TRUE(c1->get_x() == 1);
   ASSERT_TRUE(c1->get_y() == 1);
   ASSERT_TRUE(c1->get_z() == 0);
   ASSERT_TRUE(c2->get_x() == 1);
   ASSERT_TRUE(c2->get_y() == 0);
   ASSERT_TRUE(c2->get_z() == 1);
}

TEST(Container, CheckRoot)
{
   std::cout << "Operation" << std::endl;
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,0,1);
   auto o1 = b1->at(0);
   auto o2 = b2->at(0);

   std::cout << "Checking" << std::endl;
   ASSERT_TRUE(o1->root == b1);
   ASSERT_TRUE(o1->self == o1);
   ASSERT_TRUE(o2->root == b2);
   ASSERT_TRUE(o2->self == o2);
}

TEST(Container, SwapGridFail)
{
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,1,1);

   EXPECT_NO_THROW({
      ASSERT_TRUE(Container::Grid::swap(b1, b1) == Container::cont_status::CONT_NOK );
   });

   std::cout << "Checking get" << std::endl;
   ASSERT_TRUE(b1->get_x() == 1);
   ASSERT_TRUE(b1->get_y() == 1);
   ASSERT_TRUE(b1->get_z() == 0);
   ASSERT_TRUE(b2->get_x() == 1);
   ASSERT_TRUE(b2->get_y() == 1);
   ASSERT_TRUE(b2->get_z() == 1);

   std::cout << "Checking var" << std::endl;
   ASSERT_TRUE(GRID->at(1,1,0,0)->val == 2);
   ASSERT_TRUE(GRID->at(1,1,0,1)->val == 4);
   ASSERT_TRUE(GRID->at(1,1,1,0)->val == 3);
   ASSERT_TRUE(GRID->at(1,1,1,1)->val == 6);
}

TEST(Container, SwapGrid)
{
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,1,1);
   EXPECT_NO_THROW({
      ASSERT_TRUE(Container::Grid::swap(GRID->at(1,1,1), GRID->at(1,1,0)) == Container::cont_status::CONT_OK );
   });
}

TEST(Container, CheckGridSwaped)
{
   std::cout << "Checking val" << std::endl;
   ASSERT_TRUE(GRID->at(1,1,0,0)->val == 3);
   ASSERT_TRUE(GRID->at(1,1,0,1)->val == 6);
   ASSERT_TRUE(GRID->at(1,1,1,0)->val == 2);
   ASSERT_TRUE(GRID->at(1,1,1,1)->val == 4);

   std::cout << "Checking get" << std::endl;
   ASSERT_TRUE(GRID->at(1,1,0)->get_x() == 1);
   ASSERT_TRUE(GRID->at(1,1,0)->get_y() == 1);
   ASSERT_TRUE(GRID->at(1,1,0)->get_z() == 0);
   ASSERT_TRUE(GRID->at(1,1,1)->get_x() == 1);
   ASSERT_TRUE(GRID->at(1,1,1)->get_y() == 1);
   ASSERT_TRUE(GRID->at(1,1,1)->get_z() == 1);
}

TEST(Container, CheckGridSwapedCoord)
{
   std::cout << "Operation" << std::endl;
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,0,1);
   auto o1 = b1->at(0);
   auto o2 = b2->at(0);
   auto c1 = o1->get_coord();
   auto c2 = o2->get_coord();

   std::cout << "Checking" << std::endl;
   ASSERT_TRUE(c1->get_x() == 1);
   ASSERT_TRUE(c1->get_y() == 1);
   ASSERT_TRUE(c1->get_z() == 0);
   ASSERT_TRUE(c2->get_x() == 1);
   ASSERT_TRUE(c2->get_y() == 0);
   ASSERT_TRUE(c2->get_z() == 1);
}

TEST(Container, CheckGridSwapedRoot)
{
   std::cout << "Operation" << std::endl;
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,0,1);
   auto o1 = b1->at(0);
   auto o2 = b2->at(0);

   std::cout << "Checking" << std::endl;
   ASSERT_TRUE(o1->root == b1);
   ASSERT_TRUE(o1->self == o1);
   ASSERT_TRUE(o2->root == b2);
   ASSERT_TRUE(o2->self == o2);
}

TEST(Container, Move)
{
   std::cout << "Operation" << std::endl;
   auto b1 = GRID->at(1,1,0);
   auto o1 = b1->at(0);
   auto b2 = GRID->at(1,1,1);
   EXPECT_NO_THROW({
      b2->insert(b1->at(0));
   });
   o1->val = 11;
   auto o2 = b2->at(0);
   auto c2 = o2->get_coord();

   std::cout << "Checking get" << std::endl;
   ASSERT_TRUE(b1->obj.size() == 2);
   ASSERT_TRUE(b2->obj.size() == 3);
   ASSERT_TRUE(o2->val == 11);
   ASSERT_TRUE(c2->get_x() == 1);
   ASSERT_TRUE(c2->get_y() == 1);
   ASSERT_TRUE(c2->get_z() == 1);

   std::cout << "Checking val" << std::endl;
   ASSERT_DEATH({GRID->at(1,1,0,0)->val = 5;}, "");
   ASSERT_TRUE(GRID->at(1,1,0,0) == nullptr);
   ASSERT_TRUE(GRID->at(1,1,0,1)->val == 6);
   ASSERT_TRUE(GRID->at(1,1,1,0)->val == 11);
   ASSERT_TRUE(GRID->at(1,1,1,1)->val == 2);
   ASSERT_TRUE(GRID->at(1,1,1,2)->val == 4);

   std::cout << "Checking move" << std::endl;
   auto o3 = b1->at(0);
   ASSERT_TRUE(o3.get() == nullptr);
}

TEST(Container, GetKey)
{
   std::cout << "Operation" << std::endl;
   auto b = GRID->at(1,1,0);
   auto o1 = b->at(1);
   auto o2 = b->at(0);

   std::cout << "Checking" << std::endl;
   ASSERT_TRUE(b->get(o1->key)->val == 6);
   ASSERT_DEATH(b->get(o2->key), "");
}

TEST(Container, MoveBack)
{
   std::cout << "Operation" << std::endl;
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,1,1);

   EXPECT_NO_THROW({
      b1->insert(b2->at(0));
   });

   auto o1 = b1->at(0);
   auto c1 = o1->get_coord();

   std::cout << "Checking get" << std::endl;
   ASSERT_TRUE(b1->obj.size() == 2);
   ASSERT_TRUE(b2->obj.size() == 3);
   ASSERT_TRUE(o1->val == 11);
   ASSERT_TRUE(c1->get_x() == 1);
   ASSERT_TRUE(c1->get_y() == 1);
   ASSERT_TRUE(c1->get_z() == 0);

   std::cout << "Checking var" << std::endl;
   ASSERT_TRUE(GRID->at(1,1,0,0)->val == 11);
   ASSERT_TRUE(GRID->at(1,1,0,1)->val == 6);
   ASSERT_TRUE(GRID->at(1,1,1,0) == nullptr);
   ASSERT_TRUE(GRID->at(1,1,1,1)->val == 2);
   ASSERT_TRUE(GRID->at(1,1,1,2)->val == 4);
}

TEST(Container, SwapBoxFail)
{
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,1,1);

   EXPECT_NO_THROW({
      ASSERT_TRUE(Container::Box::swap(b1->at(0), b2->at(0)) == Container::cont_status::CONT_NOK );
   });

   auto o1 = b1->at(0);
   auto c1 = o1->get_coord();

   std::cout << "Checking get" << std::endl;
   ASSERT_TRUE(b1->obj.size() == 2);
   ASSERT_TRUE(b2->obj.size() == 3);
   ASSERT_TRUE(o1->val == 11);
   ASSERT_TRUE(c1->get_x() == 1);
   ASSERT_TRUE(c1->get_y() == 1);
   ASSERT_TRUE(c1->get_z() == 0);

   std::cout << "Checking var" << std::endl;
   ASSERT_TRUE(GRID->at(1,1,0,0)->val == 11);
   ASSERT_TRUE(GRID->at(1,1,0,1)->val == 6);
   ASSERT_TRUE(GRID->at(1,1,1,0) == nullptr);
   ASSERT_TRUE(GRID->at(1,1,1,1)->val == 2);
   ASSERT_TRUE(GRID->at(1,1,1,2)->val == 4);
}

TEST(Container, SwapBox)
{
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,1,1);

   EXPECT_NO_THROW({
      ASSERT_TRUE(Container::Box::swap(b1->at(0), b2->at(1)) == Container::cont_status::CONT_OK );
   });

   ASSERT_TRUE(b1->obj.size() == 3);
   ASSERT_TRUE(b2->obj.size() == 3);
}

TEST(Container, CheckBoxSwaped)
{
   std::cout << "Checking val" << std::endl;
   ASSERT_TRUE(GRID->at(1,1,0,0)->val == 2);
   ASSERT_TRUE(GRID->at(1,1,0,1) == nullptr);
   ASSERT_TRUE(GRID->at(1,1,0,2)->val == 6);
   ASSERT_TRUE(GRID->at(1,1,1,0)->val == 11);
   ASSERT_TRUE(GRID->at(1,1,1,1) == nullptr);
   ASSERT_TRUE(GRID->at(1,1,1,2)->val == 4);

   std::cout << "Checking get" << std::endl;
   ASSERT_TRUE(GRID->at(1,1,0)->get_x() == 1);
   ASSERT_TRUE(GRID->at(1,1,0)->get_y() == 1);
   ASSERT_TRUE(GRID->at(1,1,0)->get_z() == 0);
   ASSERT_TRUE(GRID->at(1,1,1)->get_x() == 1);
   ASSERT_TRUE(GRID->at(1,1,1)->get_y() == 1);
   ASSERT_TRUE(GRID->at(1,1,1)->get_z() == 1);
}

TEST(Container, CheckBoxSwapedCoord)
{
   std::cout << "Operation" << std::endl;
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,1,1);
   auto o1 = b1->at(0);
   auto o2 = b2->at(0);
   auto c1 = o1->get_coord();
   auto c2 = o2->get_coord();

   std::cout << "Checking" << std::endl;
   ASSERT_TRUE(c1->get_x() == 1);
   ASSERT_TRUE(c1->get_y() == 1);
   ASSERT_TRUE(c1->get_z() == 0);
   ASSERT_TRUE(c2->get_x() == 1);
   ASSERT_TRUE(c2->get_y() == 1);
   ASSERT_TRUE(c2->get_z() == 1);
}

TEST(Container, CheckBoxSwapedRoot)
{
   std::cout << "Operation" << std::endl;
   auto b1 = GRID->at(1,1,0);
   auto b2 = GRID->at(1,1,1);
   auto o1 = b1->at(0);
   auto o2 = b2->at(0);

   std::cout << "Checking" << std::endl;
   ASSERT_TRUE(o1->root == b1);
   ASSERT_TRUE(o1->self == o1);
   ASSERT_TRUE(o2->root == b2);
   ASSERT_TRUE(o2->self == o2);
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}