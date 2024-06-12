#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include <container/container.hpp>
#include <world/world.hpp>

namespace testWorld
{

   std::unique_ptr<Engine::Grid> GRID;

   std::shared_ptr<Engine::Object> OBJ;
   std::shared_ptr<Engine::Box> BOX;

   std::shared_ptr<Engine::Item> ITEM;
   std::shared_ptr<Engine::Space> SPACE;

   TEST(testContainer, Create)
   {
       ASSERT_NO_THROW({
           GRID = std::unique_ptr<Engine::Grid>(new Engine::Grid(2, 2, 2));
       });
    }

   TEST(testWorld, ItemCreate)
   {
       ASSERT_NO_THROW({
           OBJ  = std::make_shared<Engine::Object>();
           ITEM = std::make_shared<Engine::Item>();
       });
   }

   TEST(testWorld, SpaceCreate)
   {
       ASSERT_NO_THROW({
           BOX   = std::make_shared<Engine::Box>();
           SPACE = std::make_shared<Engine::Space>();
       });
   }

   TEST(testWorld, SpaceTest)
   {
    //    BOX->insert<Engine::Object>();
    //    auto o1 = BOX->at(0);
    //    o1->val = 1;
    //    std::cout << "val:" << o1->val << std::endl;
    //    std::cout << Engine::Object::oid << "-" << Engine::Item::oid << std::endl;

    //    SPACE->insert<Engine::Object>();
    //    std::cout << "val:" << o1->val << std::endl;
    //    std::cout << Engine::Object::oid << "-" << Engine::Item::oid << std::endl;
    //    SPACE->insert<Engine::Item>();
    //    std::cout << "val:" << o1->val << std::endl;
    //    std::cout << Engine::Object::oid << "-" << Engine::Item::oid << std::endl;
    //    SPACE->insert<Engine::Terrain>();
    //    std::cout << "val:" << o1->val << std::endl;
    //    std::cout << Engine::Object::oid << "-" << Engine::Item::oid << std::endl;

    //    auto o1 = SPACE->at(0);
    //    auto o2 = SPACE->at(1);
    //    auto o3 = SPACE->at(2);
    //    o2->val = 1;
    //    auto t1 = std::static_pointer_cast<Engine::Item> (o1);
    //    auto t2 = std::static_pointer_cast<Engine::Item> (o2);
    //    auto t3 = std::static_pointer_cast<Engine::Terrain> (o3);
    //    t1->val = 1;
    //    t1->ta = 2;
    //    t1->density = 3;
    //    t2->val = 4;
    //    t2->ta = 5;
    //    t2->density = 6;
    //    t3->val = 7;
    //    t3->density = 8;
    //    t3->quantity = 9;
    //    auto t4 = std::static_pointer_cast<Engine::Terrain> (o1);
    //    auto t5 = std::static_pointer_cast<Engine::Terrain> (o2);
    //    std::cout << t4->val << " " << t4->density << " " << t4->quantity << std::endl;
    //    std::cout << t5->val << " " << t5->density << " " << t5->quantity << std::endl;
    //    std::cout << t3->val << " " << t3->density << " " << t3->quantity << std::endl;
   }

}

// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
// }
