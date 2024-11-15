/*
 * 注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
输入一个整数，判断它能否被3，5，7整除，并输出以下信息：

1、能同时被3，5，7整除（直接输出3 5 7，每个数中间一个空格）；

2、能被其中两个数整除（输出两个数，小的在前，大的在后。例如：3 5或者 3 7或者5 7,中间用空格分隔）

3、能被其中一个数整除（输出这个除数）

4、不能被任何数整除；（输出小写字符'n',不包括单引号)

输入
一个数字

输出
一行数字,从小到大排列,包含3,5,7中为该输入的除数的数字,数字中间用空格隔开
 */

#include <iostream>

int main(){
    int num;
    while (std::cin >> num){
        if (num % 3 == 0 && num % 5 == 0 && num % 7 == 0){
            std::cout << "3 5 7\n";
        }
        else if (num % 3 == 0 && num % 5 == 0){
            std::cout << "3 5\n";
        }
        else if (num % 3 == 0 && num % 7 == 0){
            std::cout << "3 7\n";
        }
        else if (num % 5 == 0 && num % 7 == 0){
            std::cout << "5 7\n";
        }
        else if (num % 3 == 0){
            std::cout << "3\n";
        }
        else if (num % 5 == 0){
            std::cout << "5\n";
        }
        else if (num % 7 == 0){
            std::cout << "7\n";
        }
        else{
            std::cout << "n\n";
        }
    }
    return 0;
}

