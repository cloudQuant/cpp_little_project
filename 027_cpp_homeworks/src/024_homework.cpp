/*
 * 注意： 总时间限制: 2000ms 内存限制: 65536kB

描述
中位数定义：一组数据按从小到大的顺序依次排列，处在中间位置的一个数或最中间两个数据的平均值
 （如果这组数的个数为奇数，则中位数为位于中间位置的那个数；如果这组数的个数为偶数，
 则中位数是位于中间位置的两个数的平均值）.

给出一组无序整数，求出中位数，如果求最中间两个数的平均数，向下取整即可（不需要使用浮点数）

输入
该程序包含多组测试数据，每一组测试数据的第一行为N，代表该组测试数据包含的数据个数，1 <= N <= 15000.

接着N行为N个数据的输入，N=0时结束输入

输出
输出中位数，每一组测试数据输出一行
 */

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int find_kth_largest(int N, int K, const int nums[]) {
    // 使用最小堆来维护前K个最大的数
    std::priority_queue< int, std::vector<int>, std::greater<int> > minHeap;

    // 遍历输入的N个整数
    for (int i = 0; i < N; ++i) {
        // 如果堆的大小小于K，直接将元素加入堆中
        if (minHeap.size() < K) {
            minHeap.push(nums[i]);
        } else {
            // 如果当前元素大于堆顶元素（最小堆的最小值），则替换堆顶元素
            if (nums[i] > minHeap.top()) {
                minHeap.pop();
                minHeap.push(nums[i]);
            }
        }
    }

    // 堆顶元素即为第K大的数
    return minHeap.top();
}

int main() {
    int n;
    while (cin >> n && n!= 0) {
        // 输入数据到数组
        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        if (n % 2 == 0) {
            int mid = n / 2;
            int begin = find_kth_largest(n, mid , arr);
            int end = find_kth_largest(n, mid + 1, arr);
            cout << (begin + end) / 2 << endl;
        } else {
            int mid = n / 2;
            cout << find_kth_largest(n, mid + 1, arr) << endl;
        }
    }
    return 0;
}