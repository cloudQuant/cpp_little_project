/*
 * 注意： 总时间限制: 1000ms 内存限制: 65536kB

    描述
    给定一组整数，要求利用数组把这组数保存起来，再利用实现对数组中的数循环移动。
    假定共有n个整数，则要使前面各数顺序向后移m个位置，并使最后m各数变为最前面的m各数。

    注意，不要用先输出后m个数，再输出前n-m个数的方法实现，也不要用两个数组的方式实现。

    要求只用一个数组的方式实现，一定要保证在输出结果时，输出的顺序和数组中数的顺序是一致的。

    输入
    输入有两行：第一行包含一个正整数n和一个正整数m，第二行包含n个正整数。每两个正整数中间用一个空格分开。

    输出
    输出有一行：经过循环移动后数组中整数的顺序依次输出，每两个整数之间用空格分隔。
 */

//#include <iostream>
//
//int main(){
//    int n, m;
//    std::cin >> n >> m;
//    int arr[n];
//    for(int i = 0; i < n; i++){
//        std::cin >> arr[i];
//    }
//    for(int i = 0; i < m; i++){
//        int temp = arr[n-1];
//        for(int j = n-1; j > i; j--){
//            arr[j] = arr[j-1];
//        }
//        for(int j = i; j > 0; j--){
//            arr[j] = arr[j-1];
//        }
//        arr[0] = temp;
//    }
//    for(int i = 0; i < n; i++){
//        std::cout << arr[i] << " ";
//    }
//    std::cout << std::endl;
//    return 0;
//}

#include <iostream>
#include <algorithm>

void reverse(int arr[], int start, int end) {
    while (start < end) {
        std::swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    int arr[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    // 确保 m 不超过 n
    m = m % n;

    // 反转整个数组
    reverse(arr, 0, n - 1);
    // 反转前 m 个元素
    reverse(arr, 0, m - 1);
    // 反转后 n - m 个元素
    reverse(arr, m, n - 1);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}