/*
 * 描述
给一段英文短文，单词之间以空格分隔（每个单词包括其前后紧邻的标点符号）。请将短文重新排版，要求如下：

每行不超过80个字符；每个单词居于同一行上；在同一行的单词之间以一个空格分隔；行首和行尾都没有空格。

输入
第一行是一个整数n，表示英文短文中单词的数目. 其后是n个以空格分隔的英文单词（单词包括其前后紧邻的标点符号，
 且每个单词长度都不大于40个字母）。

输出
排版后的多行文本，每行文本字符数最多80个字符，单词之间以一个空格分隔，每行文本首尾都没有空格。
 */

#include <iostream>
#include <string>

int main(){
    int max_length = 80;
    int n;
    int row_length = 0;
    std::string word;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> word;
        if (row_length + word.length() + (row_length > 0 ? 1 : 0) > max_length) {
            std::cout << std::endl;
            row_length = 0;
        }

        if (row_length > 0) {
            std::cout << " ";
            row_length += 1;
        }

        std::cout << word;
        row_length += word.length();
    }

    std::cout << std::endl;
    return 0;
}