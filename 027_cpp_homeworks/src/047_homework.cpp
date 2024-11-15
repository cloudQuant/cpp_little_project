/*
 * 描述
输入二个正整数m 和 k，其中1 < m < 100000，1 < k <5 ，
 判断m 能否被19整除，且恰好含有k个3，如果满足条件，则输出YES，否则，输出NO。

例如，输入：

43833 3

满足条件，输出YES

如果输入

39331 3

尽管有3个3，但不能被19整除，也不满足条件，应输出NO

输入
m 和 k 的值，空格间隔

输出
满足条件时输出 YES，不满足时输出 NO
 */

#include <iostream>
int main() {
    int m = 0, k = 0;
    std::cin >> m >> k;

    // 检查输入的有效性
    if (m <= 1 || k <= 1 || k >= 5) {
        std::cout << "NO" << std::endl;
        return 0;
    }

    // 检查 m 是否能被 19 整除
    if (m % 19 != 0) {
        std::cout << "NO" << std::endl;
        return 0;
    }

    // 统计数字 '3' 的个数
    int count = 0;
    while (m > 0) {
        if (m % 10 == 3) {
            count++;
        }
        m /= 10;
    }

    // 判断是否恰好包含 k 个 '3'
    if (count == k) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
