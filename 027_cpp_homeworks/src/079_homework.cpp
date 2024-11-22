/*
 * 描述
现有一整数集（允许有重复元素），初始为空。我们定义如下操作：

add x 把x加入集合

del x 把集合中所有与x相等的元素删除

ask x 对集合中元素x的情况询问

对每种操作，我们要求进行如下输出。

add 输出操作后集合中x的个数

del 输出操作前集合中x的个数

ask 先输出0或1表示x是否曾被加入集合（0表示不曾加入），再输出当前集合中x的个数，中间用空格格开。
 */

#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <list>

class MySet {
private:
    std::multiset<int> content;
    std::set<int> history;       // 存储曾经加入过的元素

public:
    MySet() {}
    // 添加x
    void add_x(int x) {
        content.insert(x);
        history.insert(x);
        std::cout << content.count(x) << std::endl;
    }
    // 删除x
    void del_x(int x) {
        std::cout << content.count(x) << std::endl;
        content.erase(x);
    }
    // 询问x
    void ask_x(int x) {
        if (history.count(x)){
            std::cout << 1 << " " << content.count(x) << std::endl;
        }else{
            std::cout << 0 << " " << 0 << std::endl;
        }
    }
};

// 辅助函数：将字符串转为整数
int my_string_to_i(const std::string& str) {
    std::stringstream ss(str);
    int N;
    ss >> N;
    return N;
}

int main() {
    MySet my_set;
    int n;
    std::cin >> n;
    std::cin.ignore();
    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "add") {
            std::string num;
            ss >> num;
            int x = my_string_to_i(num);
            my_set.add_x(x);
        } else if (command == "del") {
            std::string id1;
            ss >> id1;
            int x = my_string_to_i(id1);
            my_set.del_x(x);
        } else if (command == "ask") {
            std::string id1;
            ss >> id1;
            int x = my_string_to_i(id1);
            my_set.ask_x(x);
        }
    }

    return 0;
}
