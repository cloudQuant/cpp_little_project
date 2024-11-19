/*
 * 描述
给定一个row行col列的整数数组array，要求从array[0][0]元素开始，按从左上到右下的对角线顺序遍历整个数组。
 输入

输入的第一行上有两个整数，依次为row和col。

余下有row行，每行包含col个整数，构成一个二维整数数组。

（注：输入的row和col保证0 < row < 100, 0 < col < 100）

输出
按遍历顺序输出每个整数。每个整数占一行。

 */

#include <iostream>

int main(){
    int rows, cols;
    std::cin >> rows >> cols;
    int arr[rows][cols];
    for (int r=0; r<rows; r++){
        for (int c=0; c<cols; c++){
            std::cin>>arr[r][c];
        }
    }
    // 输出数据
//    for (int c = 0; c < cols; c++){
//        for (int c1 = c; c1 >= 0; c1--){
//            for (int r = 0; r < rows; r++){
//                if ((c1+r) == c){
//                    std::cout << arr[r][c1] << std::endl;
//                }
//            }
//        }
//
//    }
    // 输出数据
        for (int sum = 0; sum < rows + cols - 1; sum++) {
            for (int r = 0; r < rows; r++) {
                int c = sum - r;
                if (c >= 0 && c < cols) {
                    std::cout << arr[r][c] << std::endl;
                }
            }
        }
    return 0;
}