/*
 * 注意： 总时间限制: 1000ms 内存限制: 65536kB、

    描述
    有两个字符串str和substr，str的字符个数不超过10，substr的字符个数为3。（字符个数不包括字符串结尾处的'\0'。）将substr插入到str中ASCII码最大的那个字符后面，若有多个最大则只考虑第一个。

    输入
    输入包括若干行，每一行为一组测试数据，格式为

    str substr

    输出
    对于每一组测试数据，输出插入之后的字符串。
 */

#include <iostream>
#include <string>

int main() {
    std::string str, substr;
    while (std::cin >> str >> substr) {
        int max_index = 0;

        // 查找 ASCII 码值最大的字符的索引
        for (int i = 1; i < str.length(); ++i) {
            if (str[i] > str[max_index]) {
                max_index = i;
            }
        }

        // 在最大字符后插入 substr
        str.insert(max_index + 1, substr);

        std::cout << str << std::endl;
    }
    return 0;
}