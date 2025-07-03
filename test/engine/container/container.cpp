#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>
#include <memory>

#include <container/container.hpp>

namespace testContainer
{

   static std::unique_ptr<Engine::Grid> GRID;

   TEST(testContainer, Create)
   {
      ASSERT_NO_THROW({
         GRID = std::unique_ptr<Engine::Grid>(new Engine::Grid(2, 2, 2));
      });
   }

   TEST(testContainer, ClassId)
   {
      ASSERT_NO_THROW({
         std::cout << "Grid id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << Engine::Grid::classid << std::endl;
         EXPECT_TRUE(Engine::Grid::classid == 0x00000001);
         std::cout << "Local id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << *GRID->myclass << std::endl;
         EXPECT_TRUE(Engine::Grid::classid == *GRID->myclass);
         std::cout << "Box id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << Engine::Box::classid << std::endl;
         EXPECT_TRUE(Engine::Box::classid == 0x00000100);
         auto o2 = std::make_shared<Engine::Box>();
         std::cout << "Local id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << *o2->myclass << std::endl;
         EXPECT_TRUE(Engine::Box::classid == *o2->myclass);
         std::cout << "Object id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << Engine::Object::classid << std::endl;
         EXPECT_TRUE(Engine::Object::classid == 0x00010000);
         auto o3 = std::make_shared<Engine::Object>();
         std::cout << "Local id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << *o3->myclass << std::endl;
         EXPECT_TRUE(Engine::Object::classid == *o3->myclass);
      });
   }

   TEST(testContainer, BoxNull)
   {
      Engine::Box BOX;
      ASSERT_NO_THROW({
         BOX.insert();
      });
   }

   TEST(testContainer, BoxEmpty)
   {
      ASSERT_NO_THROW({
         auto b1 = std::make_shared<Engine::Box>();
         b1->insert();
         auto o1 = b1->at(0);
         o1->val = 1;

         auto o2 = b1->at(1);
      });
   }

   TEST(testContainer, ObjEmpty)
   {
      ASSERT_NO_THROW({
         auto b1 = std::make_shared<Engine::Box>();
         auto o1 = std::make_shared<Engine::Object>();
         o1->val = 1;
         b1->insert(o1);
         EXPECT_TRUE(b1->get_obj_size() == 0);
      });
   }

   TEST(testContainer, ObjToBox)
   {
      ASSERT_NO_THROW({
         auto b1 = std::make_shared<Engine::Box>();
         auto b2 = std::make_shared<Engine::Box>();
         auto o1 = Engine::Object::Create();
         auto o2 = Engine::Object::Create();
         o1->val = 2;
         o2->val = 3;
         
         std::cout << "Operation" << std::endl;
         b1->insert(o1);
         EXPECT_TRUE(b1->get_obj_size() == 1);
         b1->insert(o2);
         std::cout << "Checking" << std::endl;
         EXPECT_TRUE(b1->get_obj_size() == 2);
         EXPECT_TRUE(b1->at(0)->val == 3);
         EXPECT_TRUE(b1->at(1)->val == 2);

         std::cout << "Operation" << std::endl;
         o1 = b1->at(1);
         o2 = b1->at(0);
         b2->insert(o1);
         EXPECT_TRUE(b2->get_obj_size() == 1);
         b2->insert(o2);
         std::cout << "Checking" << std::endl;
         EXPECT_TRUE(b2->get_obj_size() == 2);
         EXPECT_TRUE(b2->at(0)->val == 3);
         EXPECT_TRUE(b2->at(1)->val == 2);
      });
   }

   TEST(testContainer, Populate)
   {
      ASSERT_NO_THROW({
         for(size_t i=0;i<GRID->get_size_x();i++)
         {
            for(size_t j=0;j<GRID->get_size_y();j++)
            {
               for(size_t k=0;k<GRID->get_size_z();k++)
               {
                     auto b1 = GRID->at(i,j,k);
                     b1->insert();
                     b1->insert();
                     auto o1 = GRID->at(i,j,k,0);
                     auto o2 = GRID->at(i,j,k,1);
                     o1->val = i+j+k;
                     o2->val = 2*(i+j+k);
               }
            }
         }
      });
   }

   TEST(testContainer, CheckInsert)
   {
      for(size_t i=0;i<GRID->get_size_x();i++)
      {
         for(size_t j=0;j<GRID->get_size_y();j++)
         {
            for(size_t k=0;k<GRID->get_size_z();k++)
            {
               auto b1 = GRID->at(i,j,k);
               auto o1 = GRID->at(i,j,k,0);
               auto o2 = GRID->at(i,j,k,1);
               EXPECT_TRUE(o1->val == i+j+k);
               EXPECT_TRUE(o2->val == 2*(i+j+k));
               EXPECT_TRUE(b1->get_x() == i);
               EXPECT_TRUE(b1->get_y() == j);
               EXPECT_TRUE(b1->get_z() == k);
            }
         }
      }
   }

   TEST(testContainer, CheckCoord)
   {
      std::cout << "Operation" << std::endl;
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,0,1);
      auto o1 = b1->at(0);
      auto o2 = b2->at(0);
      auto c1 = o1->get_coord();
      auto c2 = o2->get_coord();

      std::cout << "Checking" << std::endl;
      EXPECT_TRUE(c1->get_x() == 1);
      EXPECT_TRUE(c1->get_y() == 1);
      EXPECT_TRUE(c1->get_z() == 0);
      EXPECT_TRUE(c2->get_x() == 1);
      EXPECT_TRUE(c2->get_y() == 0);
      EXPECT_TRUE(c2->get_z() == 1);
   }

   TEST(testContainer, CheckRoot)
   {
      std::cout << "Operation" << std::endl;
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,0,1);
      auto o1 = b1->at(0);
      auto o2 = b2->at(0);

      std::cout << "Checking" << std::endl;
      EXPECT_TRUE(o1->get_root() == b1);
      EXPECT_TRUE(o1->get_self() == o1);
      EXPECT_TRUE(o2->get_root() == b2);
      EXPECT_TRUE(o2->get_self() == o2);
   }

   TEST(testContainer, SwapGridFail)
   {
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,1,1);

      ASSERT_NO_THROW({
         ASSERT_TRUE(Engine::Grid::swap(b1, b1) == Engine::cont_status::CONT_NOK );
      });

      std::cout << "Checking get" << std::endl;
      EXPECT_TRUE(b1->get_x() == 1);
      EXPECT_TRUE(b1->get_y() == 1);
      EXPECT_TRUE(b1->get_z() == 0);
      EXPECT_TRUE(b2->get_x() == 1);
      EXPECT_TRUE(b2->get_y() == 1);
      EXPECT_TRUE(b2->get_z() == 1);

      std::cout << "Checking var" << std::endl;
      ASSERT_TRUE((GRID->at(1,1,0,0))->val == 2);
      ASSERT_TRUE((GRID->at(1,1,0,1))->val == 4);
      ASSERT_TRUE((GRID->at(1,1,1,0))->val == 3);
      ASSERT_TRUE((GRID->at(1,1,1,1))->val == 6);
   }

   TEST(testContainer, SwapGrid)
   {
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,1,1);
      ASSERT_NO_THROW({
         ASSERT_TRUE(Engine::Grid::swap(b1, b2) == Engine::cont_status::CONT_OK );
      });
   }

   TEST(testContainer, CheckGridSwaped)
   {
      std::cout << "Checking val" << std::endl;
      EXPECT_TRUE((GRID->at(1,1,0,0))->val == 3);
      EXPECT_TRUE((GRID->at(1,1,0,1))->val == 6);
      EXPECT_TRUE((GRID->at(1,1,1,0))->val == 2);
      EXPECT_TRUE((GRID->at(1,1,1,1))->val == 4);

      std::cout << "Checking get" << std::endl;
      EXPECT_TRUE((GRID->at(1,1,0))->get_x() == 1);
      EXPECT_TRUE((GRID->at(1,1,0))->get_y() == 1);
      EXPECT_TRUE((GRID->at(1,1,0))->get_z() == 0);
      EXPECT_TRUE((GRID->at(1,1,1))->get_x() == 1);
      EXPECT_TRUE((GRID->at(1,1,1))->get_y() == 1);
      EXPECT_TRUE((GRID->at(1,1,1))->get_z() == 1);
   }

   TEST(testContainer, CheckGridSwapedCoord)
   {
      std::cout << "Operation" << std::endl;
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,0,1);
      auto o1 = b1->at(0);
      auto o2 = b2->at(0);
      auto c1 = o1->get_coord();
      auto c2 = o2->get_coord();

      std::cout << "Checking" << std::endl;
      EXPECT_TRUE(c1->get_x() == 1);
      EXPECT_TRUE(c1->get_y() == 1);
      EXPECT_TRUE(c1->get_z() == 0);
      EXPECT_TRUE(c2->get_x() == 1);
      EXPECT_TRUE(c2->get_y() == 0);
      EXPECT_TRUE(c2->get_z() == 1);
   }

   TEST(testContainer, CheckGridSwapedRoot)
   {
      std::cout << "Operation" << std::endl;
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,0,1);
      auto o1 = b1->at(0);
      auto o2 = b2->at(0);

      std::cout << "Checking" << std::endl;
      EXPECT_TRUE(o1->get_root() == b1);
      EXPECT_TRUE(o1->get_self() == o1);
      EXPECT_TRUE(o2->get_root() == b2);
      EXPECT_TRUE(o2->get_self() == o2);
   }

   TEST(testContainer, Move)
   {
      std::cout << "Operation" << std::endl;
      auto b1 = GRID->at(1,1,0);
      auto o1 = b1->at(0);
      auto b2 = GRID->at(1,1,1);
      ASSERT_NO_THROW({
         b2->insert(o1);
      });
      o1->val = 11;
      auto o2 = b2->at(0);
      auto c2 = o2->get_coord();

      std::cout << "Checking get" << std::endl;
      EXPECT_TRUE(b1->get_obj_size() == 2);
      EXPECT_TRUE(b2->get_obj_size() == 3);
      EXPECT_TRUE(o2->val == 11);
      EXPECT_TRUE(c2->get_x() == 1);
      EXPECT_TRUE(c2->get_y() == 1);
      EXPECT_TRUE(c2->get_z() == 1);

      std::cout << "Checking val" << std::endl;
      ASSERT_NO_THROW({(GRID->at(1,1,0,0))->val = 5;});
      EXPECT_TRUE((GRID->at(1,1,0,0)) == Engine::Object::null);
      EXPECT_TRUE((GRID->at(1,1,0,1))->val == 6);
      EXPECT_TRUE((GRID->at(1,1,1,0))->val == 11);
      EXPECT_TRUE((GRID->at(1,1,1,1))->val == 2);
      EXPECT_TRUE((GRID->at(1,1,1,2))->val == 4);

      std::cout << "Checking move" << std::endl;
      auto o3 = b1->at(0);
      EXPECT_TRUE(o3 == Engine::Object::null);
   }

   TEST(testContainer, GetKey)
   {
      std::cout << "Operation" << std::endl;
      auto b = GRID->at(1,1,0);
      auto o1 = b->at(1);
      auto o2 = b->at(0);

      std::cout << "Checking" << std::endl;
      auto g1 = b->get(o1->get_key());
      EXPECT_TRUE(g1->val == 6);
      ASSERT_NO_THROW(b->get((o2)->get_key()));
   }

   TEST(testContainer, MoveBack)
   {
      std::cout << "Operation" << std::endl;
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,1,1);
      auto o0 = b2->at(0);

      EXPECT_NO_THROW({
         b1->insert(o0);
      });

      auto o1 = b1->at(0);
      auto c1 = o1->get_coord();

      std::cout << "Checking get" << std::endl;
      EXPECT_TRUE(b1->get_obj_size() == 2);
      EXPECT_TRUE(b2->get_obj_size() == 3);
      EXPECT_TRUE(o1->val == 11);
      EXPECT_TRUE(c1->get_x() == 1);
      EXPECT_TRUE(c1->get_y() == 1);
      EXPECT_TRUE(c1->get_z() == 0);

      std::cout << "Checking var" << std::endl;
      EXPECT_TRUE((GRID->at(1,1,0,0))->val == 11);
      EXPECT_TRUE((GRID->at(1,1,0,1))->val == 6);
      EXPECT_TRUE((GRID->at(1,1,1,0)) == Engine::Object::null);
      EXPECT_TRUE((GRID->at(1,1,1,1))->val == 2);
      EXPECT_TRUE((GRID->at(1,1,1,2))->val == 4);
   }

   TEST(testContainer, SwapBoxFail)
   {
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,1,1);

      auto o0a = b1->at(0);
      auto o0b = b2->at(0);

      EXPECT_NO_THROW({
         ASSERT_TRUE(Engine::Box::swap(o0a, o0b) == Engine::cont_status::CONT_NOK );
      });

      auto o1 = b1->at(0);
      auto c1 = o1->get_coord();

      std::cout << "Checking get" << std::endl;
      EXPECT_TRUE(b1->get_obj_size() == 2);
      EXPECT_TRUE(b2->get_obj_size() == 3);
      EXPECT_TRUE(o1->val == 11);
      EXPECT_TRUE(c1->get_x() == 1);
      EXPECT_TRUE(c1->get_y() == 1);
      EXPECT_TRUE(c1->get_z() == 0);

      std::cout << "Checking var" << std::endl;
      EXPECT_TRUE((GRID->at(1,1,0,0))->val == 11);
      EXPECT_TRUE((GRID->at(1,1,0,1))->val == 6);
      EXPECT_TRUE((GRID->at(1,1,1,0)) == Engine::Object::null);
      EXPECT_TRUE((GRID->at(1,1,1,1))->val == 2);
      EXPECT_TRUE((GRID->at(1,1,1,2))->val == 4);
   }

   TEST(testContainer, SwapBox)
   {
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,1,1);

      auto o0a = b1->at(0);
      auto o0b = b2->at(1);

      EXPECT_NO_THROW({
         ASSERT_TRUE(Engine::Box::swap(o0a, o0b) == Engine::cont_status::CONT_OK );
      });

      EXPECT_TRUE(b1->get_obj_size() == 3);
      EXPECT_TRUE(b2->get_obj_size() == 3);
   }

   TEST(testContainer, CheckBoxSwaped)
   {
      std::cout << "Checking val" << std::endl;
      EXPECT_TRUE((GRID->at(1,1,0,0))->val == 2);
      EXPECT_TRUE((GRID->at(1,1,0,1)) == Engine::Object::null);
      EXPECT_TRUE((GRID->at(1,1,0,2))->val == 6);
      EXPECT_TRUE((GRID->at(1,1,1,0))->val == 11);
      EXPECT_TRUE((GRID->at(1,1,1,1)) == Engine::Object::null);
      EXPECT_TRUE((GRID->at(1,1,1,2))->val == 4);

      std::cout << "Checking get" << std::endl;
      EXPECT_TRUE((GRID->at(1,1,0))->get_x() == 1);
      EXPECT_TRUE((GRID->at(1,1,0))->get_y() == 1);
      EXPECT_TRUE((GRID->at(1,1,0))->get_z() == 0);
      EXPECT_TRUE((GRID->at(1,1,1))->get_x() == 1);
      EXPECT_TRUE((GRID->at(1,1,1))->get_y() == 1);
      EXPECT_TRUE((GRID->at(1,1,1))->get_z() == 1);
   }

   TEST(testContainer, CheckBoxSwapedCoord)
   {
      std::cout << "Operation" << std::endl;
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,1,1);
      auto o1 = b1->at(0);
      auto o2 = b2->at(0);
      auto c1 = o1->get_coord();
      auto c2 = o2->get_coord();

      std::cout << "Checking" << std::endl;
      EXPECT_TRUE(c1->get_x() == 1);
      EXPECT_TRUE(c1->get_y() == 1);
      EXPECT_TRUE(c1->get_z() == 0);
      EXPECT_TRUE(c2->get_x() == 1);
      EXPECT_TRUE(c2->get_y() == 1);
      EXPECT_TRUE(c2->get_z() == 1);
   }

   TEST(testContainer, CheckBoxSwapedRoot)
   {
      std::cout << "Operation" << std::endl;
      auto b1 = GRID->at(1,1,0);
      auto b2 = GRID->at(1,1,1);
      auto o1 = b1->at(0);
      auto o2 = b2->at(0);

      std::cout << "Checking" << std::endl;
      EXPECT_TRUE(o1->get_root() == b1);
      EXPECT_TRUE(o1->get_self() == o1);
      EXPECT_TRUE(o2->get_root() == b2);
      EXPECT_TRUE(o2->get_self() == o2);
   }

} // testContainer

// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
// }
