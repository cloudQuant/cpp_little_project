#include <gtest/gtest.h>
#include <iostream>

class MyPointerTest : public ::testing::Test {};

TEST_F(MyPointerTest, TestArrayPointer) {
    char a[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 0}, *p;
    int i = 8;
    p = a + i;
    std::cout << "a = " << a << std::endl;
    std::cout << "p = " << p << std::endl;
    std::cout << "p - 3 = " <<p - 3 << std::endl;
    std::cout << "*(p - 3) = " << *(p - 3) << std::endl;
    EXPECT_EQ(*a+1, '2');
    EXPECT_EQ(*(a+1), '2');
    EXPECT_EQ(*a, '1');
    EXPECT_EQ(*(p - 3), '6');
    EXPECT_EQ(strcmp(p - 3, "6789"), 0);
}

TEST_F(MyPointerTest, TestArrayPointer2) {
    int a[10] = {6, 7, 2, 9, 1, 10, 5, 8, 4, 3}, *p = a, i;
    std::cout << "p[0] = " << p[0] << std::endl;
    // test1
    for( i = 0; i < 10; i++, p++){
        //std::cout << "p[0] = " << p[0] << std::endl;
        if(*p > *a){
            *a=*p;
        }
    }
    EXPECT_EQ(a[0], 10);
    a[0] = 6;
    p = a;
    // test2
    for( i = 0; i < 10; i++, p++){
    if(*p > *a){
        *a=*p;
        }
    }
    EXPECT_EQ(a[0], 10);
    a[0] = 6;

}



