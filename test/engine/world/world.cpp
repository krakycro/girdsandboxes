#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>
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

    TEST(testContainer, ClassId)
   {
        ASSERT_NO_THROW({
            std::cout << "Item id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << Engine::Item::classid << std::endl;
            EXPECT_TRUE(Engine::Item::classid == 0x01010000);
            auto o1 = std::make_shared<Engine::Item>();
            std::cout << "Local id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << *o1->myclass << std::endl;
            EXPECT_TRUE(Engine::Item::classid == *o1->myclass);
            std::cout << "Space id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << Engine::Space::classid << std::endl;
            EXPECT_TRUE(Engine::Space::classid == 0x01000100);
            auto o2 = std::make_shared<Engine::Space>();
            std::cout << "Local id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << *o2->myclass << std::endl;
            EXPECT_TRUE(Engine::Space::classid == *o2->myclass);
            std::cout << "Terrain id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << Engine::Terrain::classid << std::endl;
            EXPECT_TRUE(Engine::Terrain::classid == 0x01020000);
            auto o3 = std::make_shared<Engine::Terrain>();
            std::cout << "Local id: " << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << *o3->myclass << std::endl;
            EXPECT_TRUE(Engine::Terrain::classid == *o3->myclass);
        });
   }

   TEST(testContainer, Create)
   {
       ASSERT_NO_THROW({
           GRID = std::unique_ptr<Engine::Grid>(new Engine::Grid(2, 2, 2));
       });
    }

   TEST(testWorld, ItemCreate)
   {
       ASSERT_NO_THROW({
           OBJ  = Engine::Object::Create();
           OBJ->val = 5;
           std::cerr << "OBJ:" << OBJ->get_key() << ":" << OBJ->val << std::endl;
           ITEM = Engine::Item::Create();
           ITEM->val = 7;
           ITEM->density = 8;
           std::cerr << "ITEM:" << ITEM->get_key() << ":" << ITEM->val << ":" << ITEM->density << std::endl;
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
        auto o1 = Engine::Object::Create();
        BOX->insert();
        std::cout << "BOX size:" << BOX->get_obj_size() << "\n";
        BOX->insert();
        std::cout << "BOX size:" << BOX->get_obj_size() << "\n";
        BOX->at(0)->val = 1;
        BOX->at(1)->val = 2;
        std::cerr << "Key1 " << BOX->at(0)->get_key() << " Val1:" << BOX->at(0)->val << std::endl;
        std::cerr << "Key2 " << BOX->at(1)->get_key() << " Val2:" << BOX->at(1)->val << std::endl;
        BOX->insert(OBJ);
        std::cout << "BOX size:" << BOX->get_obj_size() << "\n";
        std::cerr << "Key1 " << BOX->at(0)->get_key() << " Val1:" << BOX->at(0)->val << std::endl;
        std::cerr << "Key2 " << BOX->at(1)->get_key() << " Val2:" << BOX->at(1)->val << std::endl;
        std::cerr << "Key2 " << BOX->at(2)->get_key() << " Val2:" << BOX->at(2)->val << std::endl;

        BOX->insert(ITEM);
        std::cout << "BOX size:" << BOX->get_obj_size() << "\n";

        auto i1 = Engine::Item::Create();
        i1->val = 11;
        i1->density = 22;

        BOX->insert(i1);
        std::cout << "BOX size:" << BOX->get_obj_size() << "\n";
        std::cerr << "Key1 " << BOX->at(0)->get_key() << " Val1:" << BOX->at(0)->val << std::endl;
        std::cerr << "Key2 " << BOX->at(1)->get_key() << " Val2:" << BOX->at(1)->val << std::endl;
        auto itm1 = std::static_pointer_cast<Engine::Item>(BOX->at(0));
        std::cerr << "KeyX1 " << itm1->get_key() << " ValX1:" << itm1->val << " DenX1:" << itm1->density << std::endl;
        auto itm2 = std::static_pointer_cast<Engine::Item>(BOX->at(1));
        std::cerr << "KeyX2 " << itm2->get_key() << " ValX2:" << itm2->val << " DenX2:" << itm2->density << std::endl;
   }

}

// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
// }
