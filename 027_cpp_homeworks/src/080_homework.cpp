/*
 * 描述
为了迎接08年的奥运会，让大家更加了解各种格斗运动，facer新开了一家热血格斗场。格斗场实行会员制，但是新来的会员不需要交入会费，而只要同一名老会员打一场表演赛，证明自己的实力。

我们假设格斗的实力可以用一个正整数表示，成为实力值。另外，每个人都有一个唯一的id，也是一个正整数。为了使得比赛更好看，每一个新队员都会选择与他实力最为接近的人比赛，即比赛双方的实力值之差的绝对值越小越好，如果有两个人的实力值与他差别相同，则他会选择比他弱的那个（显然，虐人必被虐好）。

不幸的是，Facer一不小心把比赛记录弄丢了，但是他还保留着会员的注册记录。现在请你帮facer恢复比赛纪录，按照时间顺序依次输出每场比赛双方的id。

输入
第一行一个数n(0 < n <=100000)，表示格斗场新来的会员数（不包括facer）。以后n行每一行两个数，按照入会的时间给出会员的id和实力值。一开始，facer就算是会员，id为1，实力值1000000000。输入保证两人的实力值不同。

输出
N行，每行两个数，为每场比赛双方的id，新手的id写在前面。
 */

#include <map>
#include <iostream>
#include <cmath>

int main() {
    std::multimap<int, int> content;
    content.insert(std::make_pair(1000000000, 1)); // Facer 的实力值和 ID

    int n;
    std::cin >> n; // 输入新会员数量

    int id, score;
    for (int i = 0; i < n; ++i) {
        std::cin >> id >> score;

        // 将新会员加入 multimap
        content.insert(std::make_pair(score, id));

        // 查找当前插入点附近的元素
        std::multimap<int, int>::iterator current = content.find(score);
        std::multimap<int, int>::iterator left = current;
        std::multimap<int, int>::iterator right = current;

        if (left != content.begin()) {
            --left; // 左侧邻居
        } else {
            left = content.end(); // 无左邻居
        }

        ++right; // 右侧邻居

        // 比较左右邻居，选择最优对手
        int opponent_id;
        if (left != content.end() && right != content.end()) {
            // 左右都有邻居
            int left_diff = std::abs(score - left->first);
            int right_diff = std::abs(score - right->first);

            if (left_diff < right_diff || (left_diff == right_diff && left->first < right->first)) {
                opponent_id = left->second;
            } else {
                opponent_id = right->second;
            }
        } else if (left != content.end()) {
            // 只有左邻居
            opponent_id = left->second;
        } else {
            // 只有右邻居
            opponent_id = right->second;
        }

        // 输出比赛双方 ID
        std::cout << id << " " << opponent_id << std::endl;
    }

    return 0;
}