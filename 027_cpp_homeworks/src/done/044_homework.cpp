/*
 * 描述
某个科室的病房分为重症和普通，只有当病人的疾病严重程度超过了入住重症病房的最低严重值，才可以安排入住重症病房。

现在要求设计一个程序，给病人安排好病房。疾病的严重程度用0到10来表示，0表示小毛病，10表示非常严重。

输入
第一行输入病人的个数m(m < 50)，以及安排住入重症病房的最低严重值a

紧接着m行，每行表示病人编号（三个位，用0补齐）及其疾病的严重程度（浮点数，1位小数）。

每个病人的疾病严重程度都不一样。

输出
要求按照病人的严重程度输出住在重症病房里的病人的编号

注意：

如果当前所有病人的严重程度并不满足住在重症病房里，则输出“None.”（不包括引号）
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

// 修改为常量引用，避免传递临时对象时出现问题
bool compare(const std::pair<std::string, double> &a,
             const std::pair<std::string, double> &b) {
    return a.second > b.second;  // 直接返回判断结果
}

int main() {
    int m;
    double a, severity;
    std::string patient_id;
    std::vector< std::pair<std::string, double> > patients;

    // 获取病人数目和最低入住病房的严重程度a
    std::cin >> m >> a;

    // 循环获取所有的数据
    for (int i = 0; i < m; ++i) {
        std::cin >> patient_id >> severity;
        patients.push_back(std::make_pair(patient_id, severity));
    }

    // 根据病人的严重程度进行排序，按照从大到小的顺序进行排序
    std::sort(patients.begin(), patients.end(), compare);

    // 输出
    bool at_least_one = false;
    for (int i = 0; i < m; ++i) {
        std::pair<std::string, double> p = patients[i];
        if (p.second > a) {
            at_least_one = true;
            std::cout << p.first << " "
                      << std::fixed << std::setprecision(1) << p.second  // 设置只保留一位小数
                      << std::endl;
            // std::cout << p.first << std::endl;
        }

    }

    if (!at_least_one) {
        std::cout << "None." << std::endl;
    }

    return 0;
}
