/*
 * 有一种细菌分为A、B两个亚种，它们的外在特征几乎完全相同，仅仅在繁殖能力上有显著差别，
 * A亚种繁殖能力非常强，B亚种的繁殖能力很弱。在一次为时一个 小时的细菌繁殖实验中，实验员由于疏忽把细菌培养皿搞乱了，
 * 请你编写一个程序，根据实验结果，把两个亚种的培养皿重新分成两组。

输入
输入有多行，第一行为整数n（n≤100），表示有n个培养皿。

其余n行，每行有三个整数，分别代表培养皿编号，试验前细菌数量，试验后细菌数量。

输出
输出有多行：

第一行输出A亚种培养皿的数量，其后每行输出A亚种培养皿的编号，按繁殖率升序排列。

然后一行输出B亚种培养皿的数量，其后每行输出B亚种培养皿的编号，也按繁殖率升序排列。

样例输入
5
1 10 3456
2 10 5644
3 10 4566
4 20 234
5 20 232
样例输出

提示
亚种内部细菌繁殖能力差异 远远小于 亚种之间细菌繁殖能力差异。

也就是说，亚种间任何两组细菌的繁殖率之差都比亚种内部两组细菌的繁殖率之差大。
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

struct Compare {
    bool operator()(const std::vector<double>& a, const std::vector<double>& b) const {
        return a[1] > b[1];
    }
};

double accumulate_func(double sum, const std::vector<double>& vec) {
    return sum + vec[1];
}

int main() {
    int n;
    std::cin >> n;
    std::vector< std::vector<double> > content;
    for (int i = 0; i < n; i++) {
        int id, before, after;
        std::vector<double> vec;
        std::cin >> id >> before >> after;
        vec.push_back(id);
        vec.push_back(static_cast<double>(after - before)/before);
        content.push_back(vec);
    }
    // 排序，按增长率降序排序
    std::sort(content.begin(), content.end(), Compare());

    // 计算总增长率
    double total_rate = std::accumulate(content.begin(), content.end(), 0.0, accumulate_func);

    double avg_rate = total_rate / n;
    int a_count = 0, b_count = 0;

    for (int i = 0; i < n; i++) {
        if (content[i][1] > avg_rate) {
            a_count++;
        }else{
            b_count++;
        }
    }
    std::cout << a_count << std::endl;
    for (int i = a_count-1; i >= 0; i--){
        std::cout << content[i][0] << std::endl;
    }
    std::cout << b_count << std::endl;
    for (int i = b_count-1; i >= 0; i--){
        std::cout << content[i+a_count][0] << std::endl;
    }

    return 0;

}