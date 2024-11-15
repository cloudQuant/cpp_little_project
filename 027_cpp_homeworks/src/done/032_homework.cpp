/*
 * 描述
    我国有4大淡水湖。

    A说：洞庭湖最大，洪泽湖最小，鄱阳湖第三。

    B说：洪泽湖最大，洞庭湖最小，鄱阳湖第二，太湖第三。

    C说：洪泽湖最小，洞庭湖第三。

    D说：鄱阳湖最大，太湖最小，洪泽湖第二，洞庭湖第三。


    已知这4个湖的大小均不相等，4个人每人仅答对一个，

    请编程按照鄱阳湖、洞庭湖、太湖、洪泽湖的顺序给出他们的大小排名。
 */

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>

bool cmp(const std::set<std::string>& vec_set,
         const std::vector<std::string>& names,
         const std::vector<int>& ranks,
         const std::map<int, std::string>& rank_order_map) {
    int count = 0;
    for (size_t i = 0; i < names.size(); ++i) {
        std::string name_rank = names[i] + rank_order_map.find(ranks[i])->second;
        if (vec_set.find(name_rank) != vec_set.end()) {
            ++count;
        }
    }
    return count == 1;
}

int main() {
    std::vector<std::string> names;
    names.push_back("鄱阳湖");
    names.push_back("洞庭湖");
    names.push_back("太湖");
    names.push_back("洪泽湖");

    std::vector< std::set<std::string> > vecs;
    std::set<std::string> a_set;
    a_set.insert("洞庭湖最大");
    a_set.insert("洪泽湖最小");
    a_set.insert("鄱阳湖第三");
    vecs.push_back(a_set);

    std::set<std::string> b_set;
    b_set.insert("洪泽湖最大");
    b_set.insert("洞庭湖最小");
    b_set.insert("鄱阳湖第二");
    b_set.insert("太湖第三");
    vecs.push_back(b_set);

    std::set<std::string> c_set;
    c_set.insert("洪泽湖最小");
    c_set.insert("洞庭湖第三");
    vecs.push_back(c_set);

    std::set<std::string> d_set;
    d_set.insert("鄱阳湖最大");
    d_set.insert("太湖最小");
    d_set.insert("洪泽湖第二");
    d_set.insert("洞庭湖第三");
    vecs.push_back(d_set);

    std::map<int, std::string> rank_order_map;
    rank_order_map[1] = "最大";
    rank_order_map[2] = "第二";
    rank_order_map[3] = "第三";
    rank_order_map[4] = "最小";

    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            if (i == j) continue;
            for (int k = 1; k <= 4; ++k) {
                if (i == k || j == k) continue;
                for (int l = 1; l <= 4; ++l) {
                    if (i == l || j == l || k == l) continue;

                    std::vector<int> ranks;
                    ranks.push_back(i);
                    ranks.push_back(j);
                    ranks.push_back(k);
                    ranks.push_back(l);

                    int right_count = 0;

                    for (size_t m = 0; m < vecs.size(); ++m) {
                        if (cmp(vecs[m], names, ranks, rank_order_map)) {
                            ++right_count;
                        } else {
                            break;
                        }
                    }

                    if (right_count == 4) {
                        std::cout << i << "\n" << j << "\n" << k << "\n" << l << std::endl;
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}
