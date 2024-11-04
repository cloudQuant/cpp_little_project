/*
 * 描述
    判断某年是否是闰年。

    输入
    输入只有一行，包含一个整数a(0 < a < 3000)

    输出
    一行，如果公元a年是闰年输出Y，否则输出N
 */

#include <iostream>

int main(){
    int a;
    std::cin >> a;
    if (a % 4 == 0 && (a % 100!= 0 || a % 400 == 0)) {
        std::cout << "Y" << std::endl;
    } else {
        std::cout << "N" << std::endl;
    }
    return 0;
}