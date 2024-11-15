/*
 * 描述
    从键盘输入一指定金额（以元为单位，如345），然后输出支付该金额的各种面额的人民币数量，显示100元，50元，20元，10元，5元，1元各多少张，要求尽量使用大面额的钞票。

    输入
    一个小于1000的正整数。

    输出
    输出分行，每行显示一个整数，从上到下分别表示100元，50元，20元，10元，5元，1元人民币的张数
 */

#include <iostream>
#include <vector>

static std::vector<int> count_money(int money) {
    std::vector<int> counts;
    counts.push_back(100);
    counts.push_back(50);
    counts.push_back(20);
    counts.push_back(10);
    counts.push_back(5);
    counts.push_back(1);
    std::vector<int> result;
    for (int i = 0; i < counts.size(); i++) {
        int count = money / counts[i];
        result.push_back(count);
        money %= counts[i];
        }
    return result;
}

int main() {
    int money;
    std::cin >> money;
    std::vector<int> counts = count_money(money);
    for (int i = 0; i < counts.size(); i++) {
        std::cout << counts[i] << std::endl;
    }
    return 0;
}