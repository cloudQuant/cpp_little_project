/*
 * 注意： 总时间限制: 1000ms 内存限制: 65536kB

    描述
    在北大校园里,没有自行车,上课办事会很不方便.但实际上,并非去办任何事情都是骑车快,
    因为骑车总要找车、开锁、停车、锁车等,这要耽误一些时间.
    假设找到自行车,开锁并车上自行车的时间为27秒;
    停车锁车的时间为23秒;步行每秒行走1.2米,
    骑车每秒行走3.0米.
    请判断走不同的距离去办事,是骑车快还是走路快.

    输入
    第一行为待处理的数据的数量n

    其后每一行整数为一次办事要行走的距离,单位为米.

    输出
    对应每个整数,如果骑车快,输出一行"Bike";如果走路快,输出一行"Walk";如果一样快,输出一行"All".
 */

#include <iostream>

int main() {
    int n=0;
    int distance;
    int bike_time;
    int walk_time;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> distance;
        bike_time = distance / 3.0 + 27 + 23;
        walk_time = distance / 1.2;
        if (bike_time < walk_time) {
            std::cout << "Bike" << std::endl;
        } else if (walk_time < bike_time) {
            std::cout << "Walk" << std::endl;
        } else {
            std::cout << "All" << std::endl;
        }
    }
    return 0;
}