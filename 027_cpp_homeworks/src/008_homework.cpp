/*
       * 描述
        某医院想统计一下某项疾病的获得与否与年龄是否有关，需要对以前的诊断记录进行整理。

        输入
        共2行，第一行为过往病人的数目n（0 < n <= 100)，第二行为每个病人患病时的年龄。

        输出
        每个年龄段（分四段：18以下，19-35，36-60，大于60注意看样例输出的格式）的患病人数占总患病人数的比例，以百分比的形式输出，
        精确到小数点后两位（double）。关于c++的格式化的输入输出，请参考：http://www.cplusplus.com/reference/iomanip。
        也可以在网上搜索一下，资料很多的。
      */
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
static void analyze_age_disease_correlation(){
    std::map<std::string, int> age_disease_count;
    age_disease_count["1-18"] = 0;
    age_disease_count["19-35"] = 0;
    age_disease_count["36-60"] = 0;
    age_disease_count["60-"] = 0;
    int n=0;
    int value;
    std::cin >> n;
    // std::cout << "n = " << n << std::endl;
    for (int i = 0; i < n; i++){
        std::cin >> value;
        if (value < 19) {
            age_disease_count["1-18"]++;
        }
        else if (19<= value && value< 36) {
            age_disease_count["19-35"]++;
        }
        else if (36<= value && value<= 60) {
            age_disease_count["36-60"]++;
        }
        else {
            age_disease_count["60-"]++;
        }
    }
    // 输出数据
    for (std::map<std::string, int>::iterator it = age_disease_count.begin(); it != age_disease_count.end(); ++it) {
        std::cout << it->first << ": " << std::fixed << std::setprecision(2)
                  << (double)it->second / n * 100 << "%" << std::endl;
    }
}

int main() {
    analyze_age_disease_correlation();
    return 0;
}