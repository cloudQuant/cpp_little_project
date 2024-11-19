/*
 * 描述
    输入一个整数矩阵，计算位于矩阵边缘的元素之和。所谓矩阵边缘的元素，就是第一行和最后一行的元素以及第一列和最后一列的元素。

    输入
    第一行为整数k，表示有k组数据。

    每组数据有多行组成，表示一个矩阵：

    第一行分别为矩阵的行数m和列数n（m < 100，n < 100），两者之间以空格分隔。

    接下来输入的m行数据中，每行包含n个整数，整数之间以空格作为间隔。

    输出

    输出对应矩阵的边缘元素和，一个一行。
 */

#include <iostream>
int cal_arr_margin_sum(int *p, int rows, int cols){
    int value = 0;
    for (int r=0; r<rows; r++){
        for (int c=0; c<cols; c++){
            if (r==0 || c==0 || r == rows-1 || c == cols -1){
                value += *(p + r * cols + c);  // 修正访问方式
            }
        }
    }
    return value;
}

int main(){
    int n;
    int rows, cols;
    std::cin >> n;
    for (int i=0; i<n;i++){
        std::cin >> rows >> cols;
        int arr[rows][cols];
        for (int r=0; r<rows; r++){
            for (int c=0; c<cols; c++){
                std::cin>>arr[r][c];
            }
        }
        int v = cal_arr_margin_sum((int *)arr, rows, cols);
        std::cout << v << std::endl;
    }
    return 0;
}