/*
 * 描述
    用户输入N和K，然后接着输入N个正整数（无序的），程序在不对N个整数排序的情况下，找出第K大的数。
    注意，第K大的数意味着从大到小排在第K位的数。

    输入
    N
    K
    a1 a2 a3 a4 ..... aN

    输出
    b
 */

#include <iostream>

#include <vector>
#include <queue>
#include <functional>

static int find_kth_largest(int N, int K, const std::vector<int>& nums) {
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
    int n, k;
    std::cin >> n >> k;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }
    int kth_largest = find_kth_largest(n, k, nums);
    std::cout << kth_largest << std::endl;
    return 0;
}