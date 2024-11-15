/*
 * 描述
所谓角谷猜想，是指对于任意一个正整数，如果是奇数，则乘3加1，如果是偶数，则除以2，得到的结果再按照上述规则重复处理，最终总能够得到1。如，假定初始整数为5，计算过程分别为16、8、4、2、1。

程序要求输入一个整数，将经过处理得到1的过程输出来。

输入
一个正整数

输出
从输入整数到1的步骤，每一步为一行，每一部中描述计算过程，假定输入为7，则输出为：
 */
#include <iostream>

void guess(int n){
    if (n==1){
        std::cout << "End" << std::endl;
    }else{
        if (n%2==0){
            int r = n/2;
            std::cout << n<<"/"<<2<<"="<<r<<std::endl;
            guess(r);
        }else{
            int r = n*3+1;
            std::cout << n<<"*"<<3<<"+"<<1<<"="<<r<<std::endl;
            guess(r);
        }
    }
}

int main(){
    int n;
    std::cin >> n;
    guess(n);
    return 0;
}