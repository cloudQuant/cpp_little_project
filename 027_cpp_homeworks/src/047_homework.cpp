/*
 * 描述
输入二个正整数m 和 k，其中1 < m < 100000，1 < k <5 ，
 判断m 能否被19整除，且恰好含有k个3，如果满足条件，则输出YES，否则，输出NO。

例如，输入：

43833 3

满足条件，输出YES

如果输入

39331 3

尽管有3个3，但不能被19整除，也不满足条件，应输出NO

输入
m 和 k 的值，空格间隔

输出
满足条件时输出 YES，不满足时输出 NO
 */

#include <iostream>
int main(){
    int m=0, k=0;
    std::cin >> m >> k;
    if (m % 19 != 0){
        std::cout << "NO" << std::endl;
        return 0;
    }
    int count = 0;
    while (m / 10 > 0){
        if (m % 10 == k){
            count++;
        }
        m = m / 10;
    }
    if (count == 3){
        std::cout << "YES" << std::endl;
    }else{
        std::cout << "NO" << std::endl;
    };
    return 0;
}