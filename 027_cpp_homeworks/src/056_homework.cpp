/*
描述
魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市。

红司令部，City 1，City 2，……，City n，蓝司令部

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。

双方的武士编号都是从1开始计算。红方制造出来的第n个武士，编号就是n。同样，蓝方制造出来的第n个武士，编号也是n。

武士在刚降生的时候有一个生命值。

在每个整点，双方的司令部中各有一个武士降生。

红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。

蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。

制造武士需要生命元。

制造一个初始生命值为m的武士，司令部中的生命元就要减少m个。

如果司令部中的生命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个。如果所有武士都不能制造了，则司令部停止制造武士。

给定一个时间，和双方司令部的初始生命元数目，要求你将从0点0分开始到双方司令部停止制造武士为止的所有事件按顺序输出。

一共有两种事件，其对应的输出样例如下：

1) 武士降生

输出样例： 004 blue lion 5 born with strength 5,2 lion in red headquarter

表示在4点整，编号为5的蓝魔lion武士降生，它降生时生命值为5，降生后蓝魔司令部里共有2个lion武士。（为简单起见，不考虑单词的复数形式）注意，每制造出一个新的武士，都要输出此时司令部里共有多少个该种武士。

2) 司令部停止制造武士

输出样例： 010 red headquarter stops making warriors

表示在10点整，红方司令部停止制造武士

输出事件时：

首先按时间顺序输出；

同一时间发生的事件，先输出红司令部的，再输出蓝司令部的。

输入
第一行是一个整数，代表测试数据组数。

每组测试数据共两行。

第一行：一个整数M。其含义为， 每个司令部一开始都有M个生命元( 1 <= M <= 10000)。

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000。

输出
对每组测试数据，要求输出从0时0分开始，到双方司令部都停止制造武士为止的所有事件。

对每组测试数据，首先输出"Case:n" n是测试数据的编号，从1开始 。

接下来按恰当的顺序和格式输出所有事件。每个事件都以事件发生的时间开头，时间以小时为单位，有三位。
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

class Solider{
   private:
     int life_num;
     int now_num;
     int now_index;
     bool stop_status;
     std::string name;
     std::vector<std::string> names;
     std::vector<int> solider_numbers;
     std::map<std::string, int> name_map;
   public:
     bool get_stop_status(){
        return stop_status;
      }
     Solider(int life_num, int a, int b, int c, int d, int e,
             std::string name, std::vector<std::string> &names){
       this->life_num = life_num;
       this->now_num = 0;
       this->now_index = 0;
       this->name = name;
       this->names = names;
       this->stop_status = false;
       this->name_map["dragon"] = a;
       this->name_map["ninja"] = b;
       this->name_map["iceman"] = c;
       this->name_map["lion"] = d;
       this->name_map["wolf"] = e;
       this->solider_numbers.push_back(0);
       this->solider_numbers.push_back(0);
       this->solider_numbers.push_back(0);
       this->solider_numbers.push_back(0);
       this->solider_numbers.push_back(0);

     }
     void generage_solider(){
          if (this->stop_status){return;}
          std::string solider_type = this->names[this->now_index%5];
          int now_life_num = this->name_map[solider_type];
//          std::cout << "now_index = " << now_index
//                    << " now_num = " << now_num
//                    << " solider_type = " << solider_type
//                    << std::endl;
          if (this->life_num >= now_life_num){
              this->solider_numbers[this->now_index%5]++;
              this->life_num -= now_life_num;


              std::cout << std::setw(3) << std::setfill('0') << this->now_num << " "
                         << this->name <<" "
                         << solider_type <<" "
                         << this->now_num+1 << " born with strength "
                          << now_life_num <<"," << this->solider_numbers[this->now_index%5] << " "
                          <<solider_type<< " in "
                          << this->name <<" headquarter" << std::endl;
              this->now_num++;
              this->now_index++;
            }
           else{
                bool stop = true;
                for(int i =0; i<5; i++){
                    this->now_index++;
                    solider_type = this->names[this->now_index%5];
                    now_life_num = this->name_map[solider_type];
                    if (this->life_num >= now_life_num){
                            this->solider_numbers[this->now_index%5]++;
                            this->life_num -= now_life_num;

                            std::cout << std::setw(3) << std::setfill('0') << this->now_num << " "
                                       << this->name <<" "
                                       << solider_type <<" "
                                       << this->now_num+1 << " born with strength "
                                        << now_life_num <<"," << this->solider_numbers[this->now_index%5] << " "
                                        <<solider_type<< " in "
                                        << this->name <<" headquarter" << std::endl;
                            this->now_num++;
                            this->now_index++;
                            stop = false;
                            break;
                          }
                    }
                this->stop_status = stop;
                if (this->stop_status){
                  std::cout << std::setw(3) << std::setfill('0') << this->now_num<<" "
                      << this->name
                      << " headquarter stops making warriors" << std::endl;
                }
            }

       }

  };

int main(){
    std::vector<std::string> red_names;
    red_names.push_back("iceman");
    red_names.push_back("lion");
    red_names.push_back("wolf");
    red_names.push_back("ninja");
    red_names.push_back("dragon");
    std::vector<std::string> blue_names;

    blue_names.push_back("lion");
    blue_names.push_back("dragon");
    blue_names.push_back("ninja");
    blue_names.push_back("iceman");
    blue_names.push_back("wolf");

    int case_num, life_num, a, b,c,d,e;
    std::cin >> case_num >> life_num >> a >> b >> c >> d >> e;
    std::cout << "Case:" << case_num << std::endl;
    Solider red(life_num, a, b, c, d, e, "red", red_names);
    Solider blue(life_num, a, b, c, d, e, "blue", blue_names);
    while (!red.get_stop_status() || !blue.get_stop_status()){
      red.generage_solider();
      blue.generage_solider();
    }

    return 0;
}