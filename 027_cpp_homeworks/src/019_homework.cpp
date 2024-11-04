/*
 * 注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
一般我们用strcmp可比较两个字符串的大小，比较方法为对两个字符串从前往后逐个字符相比较
 （按ASCII码值大小比较），直到出现不同的字符或遇到'\0'为止。如果全部字符都相同，则认为相同；
 如果出现不相同的字符，则以第一个不相同的字符的比较结果为准。但在有些时候，我们比较字符串的大小时，
 希望忽略字母的大小，例如"Hello"和"hello"在忽略字母大小写时是相等的。
 请写一个程序，实现对两个字符串进行忽略字母大小写的大小比较。

输入
输入为两行，每行一个字符串，共两个字符串。
 （请用cin.getline(s,80)录入每行字符串）（每个字符串长度都小于80）

输出
如果第一个字符串比第二个字符串小，输出一个字符"<"

如果第一个字符串比第二个字符串大，输出一个字符">"

如果两个字符串相等，输出一个字符"="
 */

//#include <iostream>
//#include <cstring>
//
//int main() {
//    char s1[80], s2[80];
//    std::cin.getline(s1, 80);
//    std::cin.getline(s2, 80);
//
//    int len1 = strlen(s1), len2 = strlen(s2);
//    int i = 0, j = 0;
//    while (i < len1 && j < len2) {
//        if (s1[i] == s2[j]) {
//            i++;
//            j++;
//        }
//        else if (s1[i] == s2[j] + 32) {
//            i++;
//            j++;
//        }
//        else if (s1[i] + 32 == s2[j]) {
//            i++;
//            j++;
//        } else {
//            break;
//        }
//    }
//
//    if (i < len1 && j < len2) {
//        std::cout << (s1[i] < s2[j] ? "<" : ">") << std::endl;
//    } else if (i == len1 && j == len2) {
//        std::cout << "=" << std::endl;
//    } else if (i < len1 && j == len2) {
//        std::cout << ">" << std::endl;
//    } else {
//        std::cout << "<" << std::endl;
//    }
//
//    return 0;
//}
#include <iostream>
#include <cstring>
#include <cctype>

int main() {
    char s1[80], s2[80];
    std::cin.getline(s1, 80);
    std::cin.getline(s2, 80);

    // 将字符串转换为小写以进行忽略大小写的比较
    for (int i = 0; s1[i]; i++) s1[i] = std::tolower(s1[i]);
    for (int i = 0; s2[i]; i++) s2[i] = std::tolower(s2[i]);

    // 使用strcmp进行比较
    int result = strcmp(s1, s2);

    if (result < 0) {
        std::cout << "<" << std::endl;
    } else if (result > 0) {
        std::cout << ">" << std::endl;
    } else {
        std::cout << "=" << std::endl;
    }

    return 0;
}
