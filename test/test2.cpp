#include <gtest/gtest.h>
#include <iostream>

// Tests factorial of 0.
TEST(aaa, aaa) {
    std::cout << "test" << std::endl;
    ASSERT_STREQ("a", "a");
    EXPECT_FALSE(false); // error
}

int main(int argc, char **argv) {
   std::cout << "test" << std::endl;
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}