/*
 * 描述
    某校大门外长度为L的马路上有一排树，每两棵相邻的树之间的间隔都是1米。我们可以把马路看成一个数轴，马路的一端在数轴0的位置，另一端在L的位置；数轴上的每个整数点，即0，1，2，……，L，都种有一棵树。

    马路上有一些区域要用来建地铁，这些区域用它们在数轴上的起始点和终止点表示。已知任一区域的起始点和终止点的坐标都是整数，区域之间可能有重合的部分。现在要把这些区域中的树（包括区域端点处的两棵树）移走。你的任务是计算将这些树都移走后，马路上还有多少棵树。

    输入
    输入的第一行有两个整数L（1 <= L <= 10000）和 M（1 <= M <= 100），L代表马路的长度，M代表区域的数目，L和M之间用一个空格隔开。接下来的M行每行包含两个不同的整数，用一个空格隔开，表示一个区域的起始点和终止点的坐标。

    输出
    输出包括一行，这一行只包含一个整数，表示马路上剩余的树的数目。
 */

//#include <iostream>
//#include <set>
//#include <vector>
//
//
//int main(){
//    int L, M;
//    std::cin >> L >> M;
//    std::set<int> trees;
//    for(int i = 0; i <= L; i++){
//        trees.insert(i);
//    }
//    // std::vector<std::set<int>> move_trees;
//    for(int i = 0; i < M; i++){
//        int start, end;
//        std::cin >> start >> end;
//        std::set<int> move_tree;
//        for(int j = start; j <= end; j++){
//            move_tree.insert(j);
//        }
//        //std::cout << "tree size: " << trees.size() << std::endl;
//        std::set<int> result;
//        std::set_difference(trees.begin(), trees.end(), move_tree.begin(), move_tree.end(), std::inserter(result, result.begin()));
//        trees = result;
//        //std::cout << "tree size: " << trees.size() << std::endl;
//    }
//    std::cout << trees.size() << std::endl;
//    return 0;
//}

#include <iostream>
#include <vector>

int main() {
    int L, M;
    std::cin >> L >> M;

    // 创建一个布尔数组，初始化为 false，表示所有树都在
    std::vector<bool> trees(L + 1, false);

    // 读取每个区域并标记需要移走的树
    for (int i = 0; i < M; i++) {
        int start, end;
        std::cin >> start >> end;
        for (int j = start; j <= end; j++) {
            trees[j] = true;  // 标记为 true 表示需要移走
        }
    }

    // 计算剩余的树的数量
    int remaining_trees = 0;
    for (int i = 0; i <= L; i++) {
        if (!trees[i]) {
            remaining_trees++;
        }
    }

    std::cout << remaining_trees << std::endl;
    return 0;
}