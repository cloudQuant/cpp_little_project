//
// Created by yun on 10/29/24.
//

#ifndef MY_HOME_WORK_HPP
#define MY_HOME_WORK_HPP
#include <iostream>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <functional>

class MyHomeWork{
  public:
      constexpr static const double pi = M_PI;
    /*
    * 描述
      从键盘输入一指定金额（以元为单位，如345），然后输出支付该金额的各种面额的人民币数量，显示100元，50元，20元，10元，5元，1元各多少张，要求尽量使用大面额的钞票。

      输入
      一个小于1000的正整数。

      输出
      输出分行，每行显示一个整数，从上到下分别表示100元，50元，20元，10元，5元，1元人民币的张数
    */
    static std::vector<int> count_money(int money) {
        std::vector<int> counts = {100, 50, 20, 10, 5, 1};
        std::vector<int> result;
        for (int i = 0; i < counts.size(); i++) {
            int count = money / counts[i];
            result.push_back(count);
            money %= counts[i];
        }
        return result;
    }
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
    static int find_kth_largest(int N, int K, const std::vector<int>& nums) {
        // 使用最小堆来维护前K个最大的数
        std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

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

    /*
    * 描述
      输入一个0--100的分数，判断分数代表什么等级。

      95<=分数<=100, 输出1

      90<=分数<95,输出2

      85<=分数<90,输出3

      80<=分数<85,输出4

      70<=分数<80,输出5

      60<=分数<70输出6

      分数 < 60;输出7.

      输入
      n

      输出
      m
      */
    static int judge_score(double score) {
        // 定义查找表
        std::vector<std::pair<double, int>> lookup_table = {
                {100, 1}, {95, 1}, {90, 2}, {85, 3}, {80, 4}, {70, 5}, {60, 6}, {0, 7}
        };

        // 查找分数对应的等级
        for (const auto& entry : lookup_table) {
            if (score >= entry.first) {
                return entry.second;
            }
        }

        // 如果分数不在范围内，返回-1
        return -1;
    }
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
      static void analyze_age_disease_correlation(){
          std::map<std::string, int> age_disease_count = {
                  {"1-18", 0},
                  {"19-35", 0},
                  {"36-60", 0},
                  {"60-", 0}
          };
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
              else if (36<= value && value< 60) {
                  age_disease_count["36-60"]++;
              }
              else {
                  age_disease_count["60-"]++;
              }
          }
          // 输出数据
          for (auto it = age_disease_count.begin(); it!= age_disease_count.end(); it++){
              std::cout << it->first << ": " << std::fixed << std::setprecision(2)
                        << (double)it->second / n * 100 << "%" << std::endl;
          }

      }
      /*
       * 描述
        从键盘输入一个任意的三位整数，要求正确地分离出它的百位、十位和个位数，并分别在屏幕上输出，输出采用每行输出一个数的方式，不带其它符号。

        输入
        一个任意的三位整数

        输出
        一个任意的三位整数
       */
      static void split_integer(){
          int num;
          //std::cout << "请输入一个3位数的整数" << std::endl;
          std::cin >> num;
          std::cout << num/100 << std::endl;
          num = num%100;
          std::cout << num/10 << std::endl;
          num = num%10;
          std::cout << num << std::endl;
      }
      /*
       * 描述
        输入6个正整数，且这6个正整数中至少存在一个奇数和一个偶数。

        设这6个正整数中最大的奇数为a，最小的偶数为b，求出|a-b|的值

        输入
        输入为一行，6个正整数,且6个正整数都小于100

        输入保证这6个数中至少存在一个奇数和一个偶数

        输出
        输出为一行，输出最大的奇数与最小的偶数之差的绝对值
       */
      static int max_odd_min_even_diff(){
          int max_odd=0;
          int min_even=100;
          int num=0;
          for (int i=0;i<6;++i){
              std::cin>>num;
              if (num%2==1){
                  if (num>max_odd){
                      max_odd=num;
                  }
              }else{
                  if (num<min_even){
                      min_even=num;
                  }
              }
          }
          return std::abs(max_odd-min_even);
      }
      /*
       * 描述
        孙老师讲授的《计算概论》这门课期中考试刚刚结束，他想知道考试中取得的最高分数。因为人数比较多，他觉得这件事情交给计算机来做比较方便。你能帮孙老师解决这个问题吗？

        输入
        输入两行，第一行为整数n（1 <= n < 100），表示参加这次考试的人数.第二行是这n个学生的成绩，相邻两个数之间用单个空格隔开。所有成绩均为0到100之间的整数。

        输出
        输出一个整数，即最高的成绩。
       */
      static int get_highest_score(){
          int n=0;
          int score=0;
          int highest_score=0;
          std::cout << "请输入人数和分数" << std::endl;
          std::cin >> n;
          for (int i=0; i<n;++i){
              std::cin >> score;
              if (score > highest_score){
                  highest_score = score;
              }
          }
          return highest_score;

      }
      /*
        描述
        你买了一箱n个苹果，很不幸的是买完时箱子里混进了一条虫子。
        虫子每x小时能吃掉一个苹果，假设虫子在吃完一个苹果之前不会吃另一个，
        那么经过y小时你还有多少个完整的苹果？

        输入
        输入仅一行，包括n，x和y（均为整数）。

        输出
        输出也仅一行，剩下的苹果个数
    */
    static int cal_apple_worms(){
        int n = 0; // 苹果总数
        int x = 0; // 虫子x小时吃一个苹果
        int y = 0; // 经过y小时
        std::cout << "请输入苹果总数n, 虫子x小时吃一个苹果, 剩余苹果y, eg: 20 3 8" << std::endl;
        std::cin >> n >> x >> y;
        int eat_num = 1.0*y/x;
        if (n < eat_num){
            std::cout << 0 << std::endl;
            return 0;
        }
        else{
            int result = static_cast<int>((n - 1.0*y/x));
            std::cout << result << std::endl;
            return result;
        }

      }
    /*
    描述
    一只大象口渴了，要喝20升水才能解渴，但现在只有一个深h厘米，底面半径为r厘米的小圆桶(h和r都是整数)。问大象至少要喝多少桶水才会解渴。

    输入
    输入有一行：包行两个整数，以一个空格分开，分别表示小圆桶的深h和底面半径r，单位都是厘米。

    输出
    输出一行，包含一个整数，表示大象至少要喝水的桶数。
*/
    static int cal_elephant_drink_water(){
          int r = 0;
          int h = 0;
          std::cout << "请输入桶的深度h和半径r, eg: 10, 20" << std::endl;
          std::cin >> h >> r;
          double v = pi * r * r * h;
          int result = std::ceil(20000/v);
          return result;
      }

};

#endif //MY_HOME_WORK_HPP
