/*
 * 描述
当你站在一个迷宫里的时候，往往会被错综复杂的道路弄得失去方向感，如果你能得到迷宫地图，事情就会变得非常简单。

假设你已经得到了一个n*m的迷宫的图纸，请你找出从起点到出口的最短路。

输入
第一行是两个整数n和m(1 <= n,m <= 100)，表示迷宫的行数和列数。

接下来n行，每行一个长为m的字符串，表示整个迷宫的布局。字符'.'表示空地，'#'表示墙，'S'表示起点,'T'表示出口。

输出
输出从起点到出口最少需要走的步数。(你不能起出迷宫外)
 */

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int dx[4] = {0, 0, 1, -1}; // 右、左、下、上
const int dy[4] = {1, -1, 0, 0};

struct Node {
    int x, y, steps;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> maze(n);
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<Node> q;

    int startX, startY, endX, endY;

    // 输入迷宫地图，并找到起点和终点
    for (int i = 0; i < n; ++i) {
        cin >> maze[i];
        for (int j = 0; j < m; ++j) {
            if (maze[i][j] == 'S') {
                startX = i;
                startY = j;
            }
            if (maze[i][j] == 'T') {
                endX = i;
                endY = j;
            }
        }
    }

    // 初始化 BFS
    q.push({startX, startY, 0});
    visited[startX][startY] = true;

    // BFS 搜索最短路径
    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        // 如果到达终点，输出步数并结束程序
        if (current.x == endX && current.y == endY) {
            cout << current.steps << endl;
            return 0;
        }

        // 遍历四个方向
        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            // 检查新位置是否合法，并且没有访问过
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                !visited[nx][ny] && maze[nx][ny] != '#') {
                visited[nx][ny] = true;
                q.push({nx, ny, current.steps + 1});
            }
        }
    }

    // 如果没有找到路径，输出 -1
    cout << -1 << endl;
    return 0;
}
