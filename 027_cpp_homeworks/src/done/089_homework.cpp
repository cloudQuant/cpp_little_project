//#include <iostream>
//#include <iomanip> // 用于十六进制输出
//using namespace std;
//
//int main() {
//    int t; // 输入数据组数
//    cin >> t;
//
//    while (t--) {
//        unsigned int n, i, j; // 输入的整数和位索引
//        cin >> n >> i >> j;
//
//        unsigned int k = 0; // 初始化结果为 0
//
//        // 将第 i 位设置为 n 的第 i 位
//        if ((n >> i) & 1) {
//            k |= (1 << i); // 如果 n 的第 i 位是 1，则将 k 的第 i 位置为 1
//        }
//
//        // 将第 j 位设置为与 n 的第 j 位不同
//        if ((n >> j) & 1) {
//            k &= ~(1 << j); // 如果 n 的第 j 位是 1，将 k 的第 j 位置为 0
//        } else {
//            k |= (1 << j); // 如果 n 的第 j 位是 0，将 k 的第 j 位置为 1
//        }
//
//        // 将 i 和 j 之间的所有位设置为 1
//        for (unsigned int bit = i + 1; bit < j; ++bit) {
//            k |= (1 << bit);
//        }
//
//        // 按十六进制大写输出结果
//        cout << hex << uppercase << k << endl;
//    }
//
//    return 0;
//}

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int case_num = 0; case_num < t; ++case_num) {
        int n, i, j;
        cin >> n >> i >> j;
        unsigned int k = 0;

        if(i < j - 1) {
            // 设置第 i 位与 n 的第 i 位相同
            if((n >> i) & 1) {
                k |= (1 << i);
            }

            // 设置第 j 位与 n 的第 j 位不同
            if(!((n >> j) & 1)) {
                k |= (1 << j);
            }

            // 设置 i 和 j 之间的位为 1
            unsigned int mask = ((1 << (j - i - 1)) - 1) << (i + 1);
            k |= mask;
        }

        // 按十六进制大写输出
        cout << hex << uppercase << k << endl;
    }
    return 0;
}

