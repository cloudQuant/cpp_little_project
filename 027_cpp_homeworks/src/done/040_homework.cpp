/*
 * 描述
在某个字符串（长度不超过100）中有左括号、右括号和大小写字母；规定（与常见的算数式子一样）
 任何一个左括号都从内到外与在它右边且距离最近的右括号匹配。写一个程序，找到无法匹配的左括号和右括号，
 输出原来字符串，并在下一行标出不能匹配的括号。不能匹配的左括号用"$"标注,不能匹配的右括号用"?"标注.

输入
输入包括多组数据，每组数据一行，包含一个字符串，只包含左右括号和大小写字母，字符串长度不超过100

注意：cin.getline(str,100)最多只能输入99个字符！

输出
对每组输出数据，!!!输出两行，第一行包含原始输入字符!!!，第二行由"$","?"和空格组成，"$"和"?"表示与之对应的左括号和右括号不能匹配。

 */

#include <iostream>
#include <stack>
#include <cstring>
#include <vector>

int main() {
    char buffer[101];
    std::vector<std::string> vecs;  // 使用std::string代替char数组来存储每行输入

    // 处理多组输入，直到遇到 EOF
    // 处理多组输入，直到没有新行输入（空行或EOF）
    // 处理多组输入，直到遇到 EOF 或空行
    while (true) {
        std::cin.getline(buffer, 101);

        if (std::cin.eof()) {
            break;  // 遇到EOF时退出
        }

        if (std::strlen(buffer) == 0) {
            break;  // 空行输入时退出
        }

        vecs.push_back(std::string(buffer));  // 将输入行添加到vecs
    }

    // 遍历每一行输入
    for (int i = 0; i < vecs.size(); i++) {
        std::stack< std::pair<int, char> > s;
        std::string line = vecs[i];  // 获取当前行作为字符串
        int len = line.length();     // 获取当前行的长度

        // 第一行输出原始字符串
        std::cout << line << std::endl;

        // 检查括号匹配
        for (int i = 0; i < len; i++) {
            char c = line[i];
            if (c == '(') {
                s.push(std::make_pair(i, c));
            } else if (c == ')') {
                if (!s.empty() && s.top().second == '(') {
                    s.pop();
                } else {
                    s.push(std::make_pair(i, c));
                }
            }
        }

        // 初始化标记字符串
        std::string marks(len, ' ');  // 使用std::string代替char数组
        marks[len] = '\0';

        // 标记无法匹配的括号
        while (!s.empty()) {
            if (s.top().second == '(') {
                marks[s.top().first] = '$';
            } else {
                marks[s.top().first] = '?';
            }
            s.pop();
        }

        // 输出标记行
        std::cout << marks << std::endl;
    }

    return 0;
}