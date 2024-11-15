/*
 * 注意： 总时间限制: 1000ms 内存限制: 65536kB

    描述
    在一个长度为n(n < 1000)的整数序列中，判断是否存在某两个元素之和为k。

    输入
    第一行输入序列的长度n和k，用空格分开。

    第二行输入序列中的n个整数，用空格分开。

    输出
    如果存在某两个元素的和为k，则输出yes，否则输出no。
 */
#include <iostream>
#include <vector>

int main(){
    int n, k;
    std::cin >> n >> k;
    std::vector<int> nums(n);
    for(int i = 0; i < n; i++){
        std::cin >> nums[i];
    }
    bool found = false;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(nums[i] + nums[j] == k){
                found = true;
                break;
            }
        }
    }
    if(found){
        std::cout << "yes" << std::endl;
    }else{
        std::cout << "no" << std::endl;
    }
    return 0;
}