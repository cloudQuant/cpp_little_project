/*
 * 描述
有一批易感人群住在网格状的宿舍区内，宿舍区为n*n的矩阵，每个格点为一个房间，房间里可能住人，也可能空着。
 在第一天，有些房间里的人得了流感，以后每天，得流感的人会使其邻居传染上流感，（已经得病的不变），空房间不会传染。
 请输出第m天得流感的人数。

输入
第一行一个数字n，n不超过100，表示有n*n的宿舍房间。

接下来的n行，每行n个字符，’.’表示第一天该房间住着健康的人，’#’表示该房间空着，’@’表示第一天该房间住着得流感的人。

接下来的一行是一个整数m，m不超过100.

输出
输出第m天，得流感的人数
 */

#include <iostream>
#include <cstring>

int n;

void simulate(char grid[][100], char new_grid[][100]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '#') {
                new_grid[i][j] = '#';
            } else if (grid[i][j] == '@') {
                new_grid[i][j] = '@';
            } else {
                // 检查四个方向是否有感染源
                if ((i > 0 && grid[i - 1][j] == '@') ||
                    (i < n - 1 && grid[i + 1][j] == '@') ||
                    (j > 0 && grid[i][j - 1] == '@') ||
                    (j < n - 1 && grid[i][j + 1] == '@')) {
                    new_grid[i][j] = '@';
                } else {
                    new_grid[i][j] = '.';
                }
            }
        }
    }

    // 如果没有新的感染，提前结束模拟
    std::memcpy(grid, new_grid, sizeof(char) * 100 * 100);
}

int count_infected(char grid[][100]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '@') {
                count++;
            }
        }
    }
    return count;
}

int num_infected_after_m_days(char grid[][100], int m) {
    char new_grid[100][100];
    for (int day = 1; day < m; day++) {
        simulate(grid, new_grid);
    }
    return count_infected(grid);
}

int main() {
    int m;
    std::cin >> n;
    char grid[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> grid[i][j];
        }
    }
    std::cin >> m;
    std::cout << num_infected_after_m_days(grid, m) << std::endl;
    return 0;
}
