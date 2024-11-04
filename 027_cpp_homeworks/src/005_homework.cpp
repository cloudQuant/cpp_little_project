#include <iostream>

void split_integer(){
    int num;
    //std::cout << "请输入一个3位数的整数" << std::endl;
    std::cin >> num;
    std::cout << num/100 << std::endl;
    num = num%100;
    std::cout << num/10 << std::endl;
    num = num%10;
    std::cout << num << std::endl;
}

int main(){
    split_integer();
    return 0;
}