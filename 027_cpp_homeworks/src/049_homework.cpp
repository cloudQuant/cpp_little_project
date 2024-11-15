/*
 * 描述
两个整数 a 和 b 运算后得到结果 c。表示为：a ? b = c，
 其中，？可能是加法 +，减法 -，乘法 *，整除 / 或 取余 %。请根据输入的 a,b,c 的值，
 确定运算符。如果某种运算成立，则输出相应的运算符，如果任何运算都不成立，则输出 error.

例如：

输入：

3,4,5

输出：

error

若输入：

3,4,3

则输出：

%
 */

#include <iostream>
#include <string>

int main(){
    std::string content;
    std::getline(std::cin, content);
    //std::cout << content << std::endl;
    int a = std::stoi(content.substr(0,1));
    int b = std::stoi(content.substr(2,1));
    int c = std::stoi(content.substr(4,1));
    if (a - b == c){
        std::cout << "-" << std::endl;
        return 0;
    }
    if (a + b == c){
        std::cout << "+" << std::endl;
        return 0;
    }
    if (a * b == c){
        std::cout << "*" << std::endl;
        return 0;
    }
    if (a / b == c){
        std::cout << "/" << std::endl;
        return 0;
    }
    if (a%b==c){
        std::cout << "%" << std::endl;
        return 0;
    }
    std::cout << "error" << std::endl;
    return 0;

}