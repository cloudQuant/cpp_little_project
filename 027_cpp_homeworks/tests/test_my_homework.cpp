//#include "../src/include/my_home_work.hpp"
#include "../src/include/my_home_work.hpp"
#include <gtest/gtest.h>
#include <sstream>

class MyHomeWorkTest : public ::testing::Test {};

// Test cases for cal_apple_worms function
TEST_F(MyHomeWorkTest, CalAppleWorms_Case1) {
    std::istringstream input("10 4 9\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    int result = MyHomeWork::cal_apple_worms();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    EXPECT_EQ(result, 7);
    EXPECT_EQ(output.str(), "请输入苹果总数n, 虫子x小时吃一个苹果, 剩余苹果y, eg: 20 3 8\n7\n");
}

TEST_F(MyHomeWorkTest, CalAppleWorms_Case2) {
    std::istringstream input("10 4 36\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    int result = MyHomeWork::cal_apple_worms();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    EXPECT_EQ(result, 1);
    EXPECT_EQ(output.str(), "请输入苹果总数n, 虫子x小时吃一个苹果, 剩余苹果y, eg: 20 3 8\n1\n");
}

TEST_F(MyHomeWorkTest, CalAppleWorms_Case3) {
    std::istringstream input("10 4 100\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    int result = MyHomeWork::cal_apple_worms();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    EXPECT_EQ(result, 0);
    EXPECT_EQ(output.str(), "请输入苹果总数n, 虫子x小时吃一个苹果, 剩余苹果y, eg: 20 3 8\n0\n");
}

// Test cases for cal_elephant_drink_water function
TEST_F(MyHomeWorkTest, CalElephantDrinkWater_Case1) {
    std::istringstream input("23 11\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::cal_elephant_drink_water();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 3);
}

TEST_F(MyHomeWorkTest, CalElephantDrinkWater_Case2) {
    std::istringstream input("1 1\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::cal_elephant_drink_water();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 6367);  // 大象至少需要6367桶才能喝够20升
}