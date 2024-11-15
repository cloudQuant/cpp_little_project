/*
 * 描述
在一个m×n的山地上，已知每个地块的平均高程，请求出所有山顶所在的地块
 （所谓山顶，就是其地块平均高程不比其上下左右相邻的四个地块每个地块的平均高程小的地方)。

输入
第一行是两个整数，表示山地的长m（5≤m≤20）和宽n（5≤n≤20）。

其后m行为一个m×n的整数矩阵，表示每个地块的平均高程。每行的整数间用一个空格分隔。

输出
输出所有上顶所在地块的位置。每行一个。按先m值从小到大，再n值从小到大的顺序输出。
 */

#include <iostream>
#include <vector>

// 检查当前位置是否为山顶
bool is_mountain_peak(const std::vector< std::vector<int> >& vec, int i, int j) {
    int m = vec.size();
    int n = vec[0].size();
    int current = vec[i][j];

    // 检查上下左右四个方向的邻居
    if (i > 0 && current < vec[i - 1][j]) return false;   // 上
    if (i < m - 1 && current < vec[i + 1][j]) return false; // 下
    if (j > 0 && current < vec[i][j - 1]) return false;   // 左
    if (j < n - 1 && current < vec[i][j + 1]) return false; // 右

    return true;
}

int main() {
    int m, n;
    std::cin >> m >> n;

    // 初始化山地矩阵
    std::vector< std::vector<int> > vec(m, std::vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> vec[i][j];
        }
    }

    // 寻找所有的山顶地块
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (is_mountain_peak(vec, i, j)) {
                std::cout << i << " " << j << std::endl;
            }
        }
    }

    return 0;
}