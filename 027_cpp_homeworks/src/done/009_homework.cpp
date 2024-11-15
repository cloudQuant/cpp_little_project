/*
 * 描述
        输入一个0--100的分数，判断分数代表什么等级。

        95<=分数<=100, 输出1

        90<=分数<95,输出2

        85<=分数<90,输出3

        80<=分数<85,输出4

        70<=分数<80,输出5

        60<=分数<70输出6

        分数 < 60;输出7.

        输入
        n

        输出
        m
 */
#include <iostream>
#include <vector>
static int judge_score(double score) {
    // 定义查找表
    std::vector< std::pair<double, int> > lookup_table;
    //lookup_table.push_back(std::make_pair(100, 1));
    lookup_table.push_back(std::make_pair(95, 1));
    lookup_table.push_back(std::make_pair(90, 2));
    lookup_table.push_back(std::make_pair(85, 3));
    lookup_table.push_back(std::make_pair(80, 4));
    lookup_table.push_back(std::make_pair(70, 5));
    lookup_table.push_back(std::make_pair(60, 6));
    lookup_table.push_back(std::make_pair(0, 7));
    // 查找分数对应的等级
    for (int i = 0; i < lookup_table.size(); i++) {
        std::pair<double, int> entry = lookup_table[i];
        if (score >= entry.first) {
            return entry.second;
        }
    }

    // 如果分数不在范围内，返回-1
    return -1;
}
int main(){
    double score;
    std::cin >> score;
    int m = judge_score(score);
    std::cout << m << std::endl;
}