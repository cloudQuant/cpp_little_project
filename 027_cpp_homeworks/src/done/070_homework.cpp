/*
 * 描述
利用流操纵算子实现： 输入一个整数，先将该整数以十六进制输出，然后再将该整数以10个字符的宽度输出，宽度不足时在左边补0。

注意：在不同系统、编译器上的输出格式略有不同，但保证在程序中采用默认格式设置一定能在OJ平台上得到正确结果。

输入
一个正整数，保证可以用int类型存储。

输出
第一行：以十六进制输出该整数；

第二行：以10个字符的宽度输出该整数。
 */

#include <iostream>
#include <iomanip>

int main(){
   int a;
   std::cin >> a;
   std::cout << std::hex << a << std::endl;
   // 十进制输出，10位，不足补0
   std::cout << std::dec << std::setw(10) << std::setfill('0') << a << std::endl;
}