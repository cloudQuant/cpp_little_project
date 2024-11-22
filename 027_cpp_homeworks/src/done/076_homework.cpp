#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <queue>

class MyList {
private:
    std::map<std::string, std::list<int> > content;

public:
    MyList() {}

    // 创建新的序列
    void new_id(const std::string& id) {
        if (content.find(id) == content.end()) {
            content[id] = std::list<int>();
        }
    }

    // 添加元素到序列
    void add_id_num(const std::string& id, int num) {
        content[id].push_back(num);
    }

    // 合并两个序列
    void merge_id1_id2(const std::string& id1, const std::string& id2) {
        if (content.find(id1) != content.end() && content.find(id2) != content.end()) {
            content[id1].sort();
            content[id2].sort();
            content[id1].merge(content[id2]);
        }
    }

    // 去重序列中的元素
    void unique_id(const std::string& id) {
        if (content.find(id) != content.end()) {
            std::list<int>& lst = content[id];
            std::set<int> seen;
            for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ) {
                if (seen.find(*it) != seen.end()) {
                    it = lst.erase(it); // 删除重复元素
                } else {
                    seen.insert(*it);
                    ++it;
                }
            }
        }
    }

    // 输出序列
    void out_id(const std::string& id) {
        if (content.find(id) != content.end()) {
            std::list<int>& lst = content[id];
            lst.sort(); // 排序
            for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
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
    MyList my_list;
    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin, line);

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "new") {
            std::string id;
            ss >> id;
            my_list.new_id(id);
        } else if (command == "add") {
            std::string id;
            int num;
            ss >> id >> num;
            my_list.add_id_num(id, num);
        } else if (command == "merge") {
            std::string id1, id2;
            ss >> id1 >> id2;
            my_list.merge_id1_id2(id1, id2);
        } else if (command == "unique") {
            std::string id;
            ss >> id;
            my_list.unique_id(id);
        } else if (command == "out") {
            std::string id;
            ss >> id;
            my_list.out_id(id);
        }
    }

    return 0;
}
