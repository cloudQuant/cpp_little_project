/*
 * 描述
输入一个句子（一行），将句子中的每一个单词翻转后输出。

输入
只有一行，为一个字符串，不超过500个字符。单词之间以空格隔开。所谓单词指的是所有不包含空格的连续的字符。

这道题请用cin.getline输入一行后再逐个单词递归处理。

输出
翻转每一个单词后的字符串，单词之间的空格需与原文一致。


 */

#include <iostream>
#include <stack>

int main(){
    const int MAX_LENGTH = 501; // 定义最大长度
    char buffer[MAX_LENGTH];
    std::cin.getline(buffer, MAX_LENGTH);
    std::stack<char> q;
    for (int i=0; buffer[i] != '\0'; i++){
        char c = buffer[i];
        //std::cout << c ;
        if (c!=' '){
            q.push(c);
        }
        else{
            while (!q.empty()){
                std::cout << q.top();
                q.pop();
            }
            std::cout <<" ";
        }
    }
    // 处理最后一个单词
    while (!q.empty()) {
        std::cout << q.top();
        q.pop();
    }
    std::cout << std::endl;
    return 0;
}