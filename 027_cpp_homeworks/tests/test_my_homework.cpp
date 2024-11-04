//#include "../src/include/my_home_work.hpp"
#include "../include/my_home_work.hpp"
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
// Test case 1: Normal case with multiple scores
TEST_F(MyHomeWorkTest, HighestScore_Case1) {
    std::istringstream input("5\n85 78 90 99 60\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::get_highest_score();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 99);
}

// Test case 2: All scores are the same
TEST_F(MyHomeWorkTest, HighestScore_AllSameScores) {
    std::istringstream input("5\n80 80 80 80 80\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::get_highest_score();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 80);
}

// Test case 3: Single student score
TEST_F(MyHomeWorkTest, HighestScore_SingleScore) {
    std::istringstream input("1\n70\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::get_highest_score();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 70);
}

// Test case 4: Minimum and maximum scores in the same input
TEST_F(MyHomeWorkTest, HighestScore_MinMaxScores) {
    std::istringstream input("6\n0 100 50 60 40 20\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::get_highest_score();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 100);
}

// Test case 5: Scores include only maximum value
TEST_F(MyHomeWorkTest, HighestScore_MaxValueOnly) {
    std::istringstream input("3\n100 100 100\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::get_highest_score();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 100);
}

// Test case 1: Typical case with a mix of odd and even numbers
TEST_F(MyHomeWorkTest, MaxOddMinEvenDiff_Case1) {
    std::istringstream input("1 2 3 4 5 6\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::max_odd_min_even_diff();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 3); // max odd = 5, min even = 2, diff = |5 - 2| = 3
}

// Test case 2: Another mix of odd and even numbers
TEST_F(MyHomeWorkTest, MaxOddMinEvenDiff_Case2) {
    std::istringstream input("1 6 3 8 5 10\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::max_odd_min_even_diff();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 1); // max odd = 5, min even = 6, diff = |5 - 6| = 1
}

// Test case 3: All even numbers except one odd number
TEST_F(MyHomeWorkTest, MaxOddMinEvenDiff_SingleOdd) {
    std::istringstream input("2 4 6 8 10 1\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::max_odd_min_even_diff();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 1); // max odd = 1, min even = 2, diff = |1 - 2| = 1
}

// Test case 4: All odd numbers except one even number
TEST_F(MyHomeWorkTest, MaxOddMinEvenDiff_SingleEven) {
    std::istringstream input("1 3 5 7 9 2\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::max_odd_min_even_diff();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 7); // max odd = 9, min even = 2, diff = |9 - 2| = 7
}

// Test case 5: Edge case with largest and smallest possible numbers under the constraints
TEST_F(MyHomeWorkTest, MaxOddMinEvenDiff_EdgeValues) {
    std::istringstream input("1 98 3 97 5 96\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    int result = MyHomeWork::max_odd_min_even_diff();

    std::cin.rdbuf(cin_backup);

    EXPECT_EQ(result, 1); // max odd = 97, min even = 96, diff = |97 - 96| = 1
}

// Test case 1: Typical three-digit positive number
TEST_F(MyHomeWorkTest, SplitInteger_Case1) {
    std::istringstream input("123\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    MyHomeWork::split_integer();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    EXPECT_EQ(output.str(), "1\n2\n3\n");
}

// Test case 2: Testing with a number that has zero in tens place
TEST_F(MyHomeWorkTest, SplitInteger_ZeroInTensPlace) {
    std::istringstream input("105\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    MyHomeWork::split_integer();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    EXPECT_EQ(output.str(), "1\n0\n5\n");
}

// Test case 3: Testing with the smallest three-digit number
TEST_F(MyHomeWorkTest, SplitInteger_MinValue) {
    std::istringstream input("100\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    MyHomeWork::split_integer();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    EXPECT_EQ(output.str(), "1\n0\n0\n");
}

// Test case 4: Testing with the largest three-digit number
TEST_F(MyHomeWorkTest, SplitInteger_MaxValue) {
    std::istringstream input("999\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    MyHomeWork::split_integer();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    EXPECT_EQ(output.str(), "9\n9\n9\n");
}

// Test case 5: Testing with a negative three-digit number
TEST_F(MyHomeWorkTest, SplitInteger_NegativeNumber) {
    std::istringstream input("-321\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    MyHomeWork::split_integer();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    EXPECT_EQ(output.str(), "-3\n-2\n-1\n");
}

// Test case 1: Typical case with evenly distributed age groups
TEST_F(MyHomeWorkTest, AnalyzeAgeDiseaseCorrelation_EvenDistribution) {
    std::istringstream input("4\n10\n25\n45\n65\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    MyHomeWork::analyze_age_disease_correlation();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string expected_output =
            "1-18: 25.00%\n"
            "19-35: 25.00%\n"
            "36-60: 25.00%\n"
            "60-: 25.00%\n";
    EXPECT_EQ(output.str(), expected_output);
}

// Test case 2: All ages in the same category (1-18)
TEST_F(MyHomeWorkTest, AnalyzeAgeDiseaseCorrelation_AllInCategory_1_18) {
    std::istringstream input("5\n10\n15\n18\n12\n13\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    MyHomeWork::analyze_age_disease_correlation();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string expected_output =
            "1-18: 100.00%\n"
            "19-35: 0.00%\n"
            "36-60: 0.00%\n"
            "60-: 0.00%\n";
    EXPECT_EQ(output.str(), expected_output);
}

// Test case 3: Ages split between 19-35 and 36-60
TEST_F(MyHomeWorkTest, AnalyzeAgeDiseaseCorrelation_SplitBetween19_35And36_60) {
    std::istringstream input("6\n22\n30\n35\n45\n50\n55\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    MyHomeWork::analyze_age_disease_correlation();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string expected_output =
            "1-18: 0.00%\n"
            "19-35: 50.00%\n"
            "36-60: 50.00%\n"
            "60-: 0.00%\n";
    EXPECT_EQ(output.str(), expected_output);
}

// Test case 4: Only age 60 and above
TEST_F(MyHomeWorkTest, AnalyzeAgeDiseaseCorrelation_AllAbove60) {
    std::istringstream input("3\n60\n75\n85\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    MyHomeWork::analyze_age_disease_correlation();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string expected_output =
            "1-18: 0.00%\n"
            "19-35: 0.00%\n"
            "36-60: 0.00%\n"
            "60-: 100.00%\n";
    EXPECT_EQ(output.str(), expected_output);
}

// Test case 5: Mix of all categories with varying counts
TEST_F(MyHomeWorkTest, AnalyzeAgeDiseaseCorrelation_MixedCategories) {
    std::istringstream input("6\n5\n23\n37\n59\n19\n82\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    MyHomeWork::analyze_age_disease_correlation();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string expected_output =
            "1-18: 16.67%\n"
            "19-35: 33.33%\n"
            "36-60: 33.33%\n"
            "60-: 16.67%\n";
    EXPECT_EQ(output.str(), expected_output);
}

// Test case 1: Score at upper boundary (100), should return 1
TEST_F(MyHomeWorkTest, JudgeScore_UpperBoundary) {
    EXPECT_EQ(MyHomeWork::judge_score(100), 1);
}

// Test case 2: Score just below 95 (e.g., 94), should return 2
TEST_F(MyHomeWorkTest, JudgeScore_LowerBoundaryForLevel2) {
    EXPECT_EQ(MyHomeWork::judge_score(94), 2);
}

// Test case 3: Score at lower boundary for level 5 (e.g., 70), should return 5
TEST_F(MyHomeWorkTest, JudgeScore_LowerBoundaryForLevel5) {
    EXPECT_EQ(MyHomeWork::judge_score(70), 5);
}

// Test case 4: Score just below passing threshold (59), should return 7
TEST_F(MyHomeWorkTest, JudgeScore_BelowPassingThreshold) {
    EXPECT_EQ(MyHomeWork::judge_score(59), 7);
}

// Test case 5: Score exactly at the boundary of each level
TEST_F(MyHomeWorkTest, JudgeScore_ExactBoundaries) {
    EXPECT_EQ(MyHomeWork::judge_score(95), 1);  // Exactly 95 should return 1
    EXPECT_EQ(MyHomeWork::judge_score(90), 2);  // Exactly 90 should return 2
    EXPECT_EQ(MyHomeWork::judge_score(85), 3);  // Exactly 85 should return 3
    EXPECT_EQ(MyHomeWork::judge_score(80), 4);  // Exactly 80 should return 4
    EXPECT_EQ(MyHomeWork::judge_score(60), 6);  // Exactly 60 should return 6
}

// Test case 1: Standard case with distinct elements
TEST_F(MyHomeWorkTest, FindKthLargest_StandardCase) {
    std::vector<int> nums = {85, 78, 90, 99, 60};
    int result = MyHomeWork::find_kth_largest(5, 2, nums); // Second largest
    EXPECT_EQ(result, 90);
}

// Test case 2: Edge case where K equals N
TEST_F(MyHomeWorkTest, FindKthLargest_KEqualsN) {
    std::vector<int> nums = {23, 45, 12, 56, 34};
    int result = MyHomeWork::find_kth_largest(5, 5, nums); // 5th largest
    EXPECT_EQ(result, 12);
}

// Test case 3: All elements are the same
TEST_F(MyHomeWorkTest, FindKthLargest_AllElementsSame) {
    std::vector<int> nums = {10, 10, 10, 10, 10};
    int result = MyHomeWork::find_kth_largest(5, 3, nums); // Any K will return 10
    EXPECT_EQ(result, 10);
}

// Test case 4: K is 1 (find the maximum)
TEST_F(MyHomeWorkTest, FindKthLargest_KIsOne) {
    std::vector<int> nums = {45, 78, 90, 23, 89, 99};
    int result = MyHomeWork::find_kth_largest(6, 1, nums); // Largest element
    EXPECT_EQ(result, 99);
}

// Test case 5: Edge case where K is the last element in a small array
TEST_F(MyHomeWorkTest, FindKthLargest_KIsLast) {
    std::vector<int> nums = {3, 1, 2};
    int result = MyHomeWork::find_kth_largest(3, 3, nums); // 3rd largest (smallest)
    EXPECT_EQ(result, 1);
}

// Test case 1: Standard case with multiple denominations
TEST_F(MyHomeWorkTest, CountMoney_StandardCase) {
    int money = 345;
    std::vector<int> expected = {3, 0, 2, 0, 1, 0}; // 3x100, 2x20, 1x5
    EXPECT_EQ(MyHomeWork::count_money(money), expected);
}

// Test case 2: Only one denomination needed (e.g., only 100s)
TEST_F(MyHomeWorkTest, CountMoney_OnlyHundreds) {
    int money = 200;
    std::vector<int> expected = {2, 0, 0, 0, 0, 0}; // 2x100
    EXPECT_EQ(MyHomeWork::count_money(money), expected);
}

// Test case 3: Test with an amount requiring all denominations
TEST_F(MyHomeWorkTest, CountMoney_AllDenominations) {
    int money = 186;
    std::vector<int> expected = {1, 1, 1, 1, 1, 1}; // 1x100, 1x50, 1x20, 1x10, 1x5, 1x1
    EXPECT_EQ(MyHomeWork::count_money(money), expected);
}

// Test case 4: Minimum amount
TEST_F(MyHomeWorkTest, CountMoney_MinimumAmount) {
    int money = 1;
    std::vector<int> expected = {0, 0, 0, 0, 0, 1}; // 1x1
    EXPECT_EQ(MyHomeWork::count_money(money), expected);
}

// Test case 5: Just below a denomination threshold
TEST_F(MyHomeWorkTest, CountMoney_JustBelowThreshold) {
int money = 49;
std::vector<int> expected = {0, 0, 2, 0, 1, 4}; // 2x20, 1x5, 4x1
EXPECT_EQ(MyHomeWork::count_money(money), expected);
}
