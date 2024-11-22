/*
 * 描述
给定n个字符串（从1开始编号），每个字符串中的字符位置从0开始编号，长度为1-500，现有如下若干操作：

copy N X L：取出第N个字符串第X个字符开始的长度为L的字符串。

add S1 S2：判断S1，S2是否为0-99999之间的整数，若是则将其转化为整数做加法，若不是，则作字符串加法，返回的值为一字符串。

find S N：在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。

rfind S N：在第N个字符串中从右开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。

insert S N X：在第N个字符串的第X个字符位置中插入S字符串。

reset S N：将第N个字符串变为S。

print N：打印输出第N个字符串。

printall：打印输出所有字符串。

over：结束操作。

其中N，X，L可由find与rfind操作表达式构成，S，S1，S2可由copy与add操作表达式构成。

输入
第一行为一个整数n（n在1-20之间）

接下来n行为n个字符串，字符串不包含空格及操作命令等。

接下来若干行为一系列操作，直到over结束。

输出
根据操作提示输出对应字符串。
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <sstream>
#include <queue>

void deal_command(std::vector<std::string> &vec, std::set<std::string>&con_set, std::string &cons){
    if (cons.length() == 0){return;}
    // std::cout << "cons = " << cons << std::endl;
    std::stack<std::string> wordStack;
    std::stack<std::string> newWordStack;
    // 使用std::stringstream来分割字符串
    std::stringstream ss(cons);
    std::string word;

    // 逐个提取单词并压入栈中
    while (ss >> word) {
        if (word.length() > 0){
            wordStack.push(word);
        }
    }
    // 输出栈中的单词
    while (!wordStack.empty()) {
        word = wordStack.top();
        wordStack.pop();
        if (con_set.count(word)){
            if (word=="copy"){
                int N = std::stoi(newWordStack.top());
                newWordStack.pop();
                int X = std::stoi(newWordStack.top());
                newWordStack.pop();
                int L = std::stoi(newWordStack.top());
                newWordStack.pop();
                std::string result = vec[N-1].substr(X, L);
                newWordStack.push(result);
                //std::cout << "copy N =" << N << " X = " << X << " L = " << L <<" " << result << std::endl;
            }
            else if (word == "add"){
                std::string s1 = newWordStack.top();
                newWordStack.pop();
                std::string s2 = newWordStack.top();
                newWordStack.pop();
                std::string value;
                if (s1.length()==0 || s1.length()>=6 || s2.length() == 0 || s2.length() >= 6){
                    value = s1 + s2;
                    newWordStack.push(value);
                }else{
                    value = std::to_string(std::stoi(s1)+std::stoi(s2));
                    newWordStack.push(value);
                }
                //std::cout << "add run s1 = " << s1 << " s2 = " << s2 << " value = " << value << std::endl;
            }
            else if (word == "find"){
                std::string s = newWordStack.top();
                newWordStack.pop();
                int N = std::stoi(newWordStack.top());
                newWordStack.pop();
                std::string index;
                if (vec[N-1].find(s)!=std::string::npos){
                    index = std::to_string(vec[N-1].find(s));
                    newWordStack.push(index);
                }else{
                    index = std::to_string(vec[N-1].length());
                    newWordStack.push(index);
                }
                //std::cout << "find run s = " << s << " N = " << N << "index = " << index << std::endl;
            }
            else if (word == "rfind"){
                std::string s = newWordStack.top();
                newWordStack.pop();
                int N = std::stoi(newWordStack.top());
                newWordStack.pop();
                if (vec[N-1].rfind(s)!=std::string::npos){
                    std::string index = std::to_string(vec[N-1].rfind(s));
                    newWordStack.push(index);
                }else{
                    std::string index = std::to_string(vec[N-1].length());
                    newWordStack.push(index);
                }
            }
            else if (word == "insert"){
                std::string s = newWordStack.top();
                newWordStack.pop();
                int N = std::stoi(newWordStack.top());
                newWordStack.pop();
                int X = std::stoi(newWordStack.top());
                newWordStack.pop();
                //在第N个字符串的第X个字符位置中插入S字符串
                vec[N-1].insert(X, s);
            }
            else if (word == "reset"){

                std::string s = newWordStack.top();
                newWordStack.pop();
                //std::cout << "s = " << s << std::endl;
                int N = std::stoi(newWordStack.top());
                newWordStack.pop();
                //std::cout << "N = " << N << std::endl;
                // 将第N个字符串变为s
                vec[N-1] = s;
            }
            else if (word == "print"){
                int N = std::stoi(newWordStack.top());
                newWordStack.pop();
                std::cout << vec[N-1] << std::endl;
            }
            else if (word == "printall") {
                //std::cout << " -------------------------- " << std::endl;
                for (int i = 0; i < vec.size(); i++) {
                    std::cout << vec[i] << std::endl;
                }
                //std::cout << " -------------------------- " << std::endl;
            }
            else if (word == "over"){
                return;
            }
        }else{
            // std::cout << "存入newWordStack的word = " << word << std::endl;
            newWordStack.push(word);
        }
    }
}
int main(){
    std::set<std::string> con_set;
    con_set.insert("copy");
    con_set.insert("add");
    con_set.insert("find");
    con_set.insert("rfind");
    con_set.insert("insert");
    con_set.insert("reset");
    con_set.insert("print");
    con_set.insert("printall");
    int n;
    std::vector<std::string> vec;
    std::cin >> n;
    // 读取输入的数据并保存到vec中
    for (int i = 0; i < n; ++i){
        std::string s;
        std::cin >> s;
        vec.push_back(s);
    }
    // 进行字符串操作
    std::string con;
    while (std::getline(std::cin, con)){
        if (con == "over"){
            break;
        }else{
            deal_command(vec, con_set, con);
        }
    }
    return 0;
}