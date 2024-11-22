/*
 * 写一个程序完成以下命令：

new id ——新建一个指定编号为id的序列(id<10000)

add id num——向编号为id的序列加入整数num

merge id1 id2——合并序列id1和id2中的数，并将id2清空

unique id——去掉序列id中重复的元素

out id ——从小到大输出编号为id的序列中的元素，以空格隔开

输入
第一行一个数n，表示有多少个命令( n＜＝２０００００)。以后n行每行一个命令。

输出
按题目要求输出。
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <list>
#include <queue>

class MyList {
private:
    std::vector<std::list<int> > content;
public:
    MyList(){};
    void new_id(int id){
        if (this->content.size()<id){
            for (std::size_t t = this->content.size(); t <= id; t++){
                std::list<int> li;
                this->content.push_back(li);
            }

        }
    }
    void add_id_num(int id, int num){
        this->content[id-1].push_back(num);
    }
    void merge_id1_id2(int id1, int id2){
        content[id1 - 1].sort();
        content[id2 - 1].sort();
        content[id1 - 1].merge(content[id2 - 1]);
        content[id2 - 1].clear();
    }
    void unique_id(int id1){
        std::list<int>& lst = content[id1 - 1];
        std::unordered_set<int> seen;
        for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ) {
            if (seen.count(*it)) {
                it = lst.erase(it);
            } else {
                seen.insert(*it);
                ++it;
            }
        }
    }
    void out_id(int id){
        std::list<int> a = content[id-1];
        a.sort();
        for(std::list<int>::iterator it=a.begin();it!=a.end();it++){
            std::cout << *it << " ";
        }
        std::cout<<std::endl;
    }

};

int my_string_to_i(std::string & topString){
    std::stringstream ss(topString);
    int N;
    ss >> N;
    return N;
}


int main(){
    MyList my_list;
    std::vector<std::string> cons;
    int n;
    std::cin >> n;
    std::cin.ignore();
    for (int i = 0; i<n; ++i) {
        std::string con;
        std::getline(std::cin, con);
        cons.push_back(con);
    }
    // std::cout << "----------------" << std::endl;
    for (int i = 0; i<cons.size(); ++i){
        // std::cout << "------ begin to run ----------" << std::endl;
        std::queue<std::string> word_queue;
        std::string con(cons[i]);
        std::stringstream ss(con);
        std::string word;
        // std::cout << con << std::endl;
        // 逐个提取单词并压入栈中
        while (ss >> word) {
            if (word.length() > 0){
                // std::cout << "push word to word_queue" << word << std::endl;
                word_queue.push(word);

            }
        }
        // std::cout << "提取数据成功,当前指令 "<< word_queue.front() << std::endl;
        // 获取指令
        if (word_queue.front() == "new"){
            // 去除命令
            word_queue.pop();
            // 提取第一个参数,并去除
            int id = my_string_to_i(word_queue.front());
            word_queue.pop();
            my_list.new_id(id);
        }
        else if (word_queue.front() == "add"){
            // 去除命令
            word_queue.pop();
            // 提取第一个参数,并去除
            int id = my_string_to_i(word_queue.front());
            word_queue.pop();
            // 提取第二个参数，并去除
            int num = my_string_to_i(word_queue.front());
            word_queue.pop();
            // 运行指令
            my_list.add_id_num(id, num);

        }
        else if (word_queue.front() == "merge"){
            // 去除命令
            word_queue.pop();
            // 提取第一个参数,并去除
            int id1 = my_string_to_i(word_queue.front());
            word_queue.pop();
            // 提取第二个参数，并去除
            int id2 = my_string_to_i(word_queue.front());
            word_queue.pop();
            // 运行指令
            my_list.merge_id1_id2(id1, id2);
        }
        else if (word_queue.front() == "unique"){
            // 去除命令
            word_queue.pop();
            // 提取第一个参数,并去除
            int id1 = my_string_to_i(word_queue.front());
            word_queue.pop();
            // 指令
            my_list.unique_id(id1);
        }
        else if (word_queue.front() == "out"){
            // 去除命令
            word_queue.pop();
            // 提取第一个参数,并去除
            int id1 = my_string_to_i(word_queue.front());
            word_queue.pop();
            // 指令
            my_list.out_id(id1);
        }
        else{
            std::cout << "wrong line" << std::endl;
        }

    }
}