//
// Created by yun on 10/29/24.
//

#ifndef MY_HOME_WORK_HPP
#define MY_HOME_WORK_HPP
#include <iostream>
#include <cmath>
#include <cstdint>

class MyHomeWork{
  public:
      constexpr static const double pi = M_PI;
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
