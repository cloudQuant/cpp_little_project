/*
 * 描述
我们定义一个正整数a比正整数b优先的含义是：

*a的质因数数目（不包括自身）比b的质因数数目多；

*当两者质因数数目相等时，数值较大者优先级高。

现在给定一个容器，初始元素数目为0，之后每次往里面添加10个元素，
 每次添加之后，要求输出优先级最高与最低的元素，并把该两元素从容器中删除。

输入
第一行: num (添加元素次数，num <= 30)

下面10*num行，每行一个正整数n（n < 10000000).

输出
每次输入10个整数后，输出容器中优先级最高与最低的元素，两者用空格间隔。
 */

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
using namespace std;

// 计算一个正整数的不同质因子数量（不包括自身）
int countDistinctPrimeFactorsExcludingSelf(int n) {
    set<int> distinctFactors; // 用于存储不同的质因子
    int original = n; // 保存原始数字，用于排除自身
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            distinctFactors.insert(i);
            while (n % i == 0) {
                n /= i; // 将当前质因子移除
            }
        }
    }
    if (n > 1 && n != original) { // 剩余部分是质数但不包括原数本身
        distinctFactors.insert(n);
    }
    return distinctFactors.size(); // 返回不同质因子的数量
}

// 定义元素结构体
struct Element {
    int value;   // 数值
    int factors; // 不同质因子数目（不包括自身）

    Element(int v) : value(v), factors(countDistinctPrimeFactorsExcludingSelf(v)) {}
};

// 自定义比较规则
struct Compare {
    bool operator()(const Element& a, const Element& b) const {
        if (a.factors != b.factors) {
            return a.factors > b.factors; // 不同质因子数目多的优先
        }
        return a.value > b.value; // 数值大的优先
    }
};

int main() {
    int num; // 添加元素的次数
    cin >> num;

    // 使用 multiset 实现优先级排序
    multiset<Element, Compare> container;

    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < 10; ++j) {
            int n;
            cin >> n;
            container.insert(Element(n));
        }

        // 输出优先级最高和最低的元素，并从容器中移除
        multiset<Element, Compare>::iterator highest = container.begin();
        multiset<Element, Compare>::iterator lowest = --container.end();

        cout << highest->value << " " << lowest->value << endl;

        container.erase(highest);
        container.erase(lowest);
    }

    return 0;
}



