/*
 * 描述
    在main函数中， 生成一个5*5的矩阵，输入矩阵数据，并输入n，m的值。
    判断n，m是否在数组范围内，如果不在，则输出error；
    如果在范围内，则将n行和m行交换，输出交换n，m后的新矩阵。

    输入
    5*5矩阵的数据，以及n和m的值。

    输出
    如果不可交换，则输出error

    如果可交换，则输出新矩阵
 */

#include <iostream>
#include <iomanip>

int main(){
    int matrix[5][5];
    int n, m;
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            std::cin >> matrix[i][j];
        }
    }
    std::cin >> n >> m;
    // std::cout << "n = " << n << " m = " << m << std::endl;
    if(n<0 || n>4 || m<0 || m>4){
        std::cout << "error" << std::endl;
        return 0;
    }
    int temp[5];
    for(int i=0; i<5; i++){
        temp[i] = matrix[n][i];
    }
    for(int i=0; i<5; i++){
        matrix[n][i] = matrix[m][i];
    }
    for(int i=0; i<5; i++){
        matrix[m][i] = temp[i];
    }
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            std::cout << std::setw(4) <<matrix[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;
}