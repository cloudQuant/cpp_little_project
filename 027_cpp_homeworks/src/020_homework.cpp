/*
 * 注意： 总时间限制: 1000ms 内存限制: 65536kB

    描述
    一个以'.'结尾的简单英文句子，单词之间用空格分隔，没有缩写形式和其它特殊形式

    输入
    一个以'.'结尾的简单英文句子（长度不超过500），单词之间用空格分隔，没有缩写形式和其它特殊形式

    输出
    该句子中最长的单词。如果多于一个，则输出第一个
 */

#include <iostream>
#include <string>
#include <sstream>

int main() {
    char sentence[500];
    std::cin.getline(sentence, 500);

    std::string max_word, word;
    std::stringstream ss(sentence);

    while (ss >> word) {
        // 检查并移除单词末尾的句号
        if (word[word.length() - 1] == '.') {
            word = word.substr(0, word.length() - 1);  // 生成不带句号的子字符串
        }

        // 更新最长单词
        if (word.length() > max_word.length()) {
            max_word = word;
        }
    }

    std::cout << max_word << std::endl;
    return 0;
}
