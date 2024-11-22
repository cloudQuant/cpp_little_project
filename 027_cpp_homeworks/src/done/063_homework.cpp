/*
描述
魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的 若干 城市。

红司令部，City 1，City 2，……，City n，蓝司令部

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值这两种属性。

有的武士可以拥有武器。武器有三种，sword, bomb,和arrow，编号分别为0,1,2。

双方的武士编号都是从1开始计算。红方制造出来的第 n 个武士，编号就是n。同样，蓝方制造出来的第 n 个武士，编号也是n。

不同的武士有不同的特点。

dragon 可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器。dragon还有“士气”这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造dragon所需的生命元数量。

ninjia可以拥有两件武器。编号为n的ninjia降生时即获得编号为 n%3 和 (n+1)%3的武器。

iceman有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器。

lion 有“忠诚度”这个属性，其值等于它降生后其司令部剩余生命元的数目。

wolf没特点。

请注意，在以后的题目里，武士的士气，生命值，忠诚度在其生存期间都可能发生变化，都有作用，武士手中的武器随着使用攻击力也会发生变化。

武士在刚降生的时候有一个生命值。

在每个整点，双方的司令部中各有一个武士降生。

红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序循环制造武士。

蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序循环制造武士。

制造武士需要生命元。

制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。

如果司令部中的生命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个。如果所有武士都不能制造了，则司令部停止制造武士。

给定一个时间，和双方司令部的初始生命元数目，要求你将从0点0分开始到双方司令部停止制造武士为止的所有事件按顺序输出。

一共有两种事件，其对应的输出样例如下：

1) 武士降生

输出样例： 004 blue lion 5 born with strength 5,2 lion in red headquarter

表示在 4点整，编号为5的蓝魔lion武士降生，它降生时生命值为5,降生后蓝魔司令部里共有2个lion武士。(为简单起见，不考虑单词的复数形式)注意，每制造出一个新的武士，都要输出此时司令部里共有多少个该种武士。

如果造出的是dragon，那么还要输出一行，例：

It has a arrow,and it's morale is 23.34

表示该dragon降生时得到了arrow,其士气是23.34（为简单起见，本题中arrow前面的冠词用a,不用an，士气精确到小数点后面2位，四舍五入）

如果造出的是ninjia，那么还要输出一行，例：

It has a bomb and a arrow

表示该ninjia降生时得到了bomb和arrow。

如果造出的是iceman，那么还要输出一行，例：

It has a sword

表示该iceman降生时得到了sword。

如果造出的是lion，那么还要输出一行，例：

It's loyalty is 24

表示该lion降生时的忠诚度是24。

2) 司令部停止制造武士

输出样例： 010 red headquarter stops making warriors

表示在 10点整，红方司令部停止制造武士

输出事件时：

首先按时间顺序输出；

同一时间发生的事件，先输出红司令部的，再输出蓝司令部的。

输入
第一行 是一个整数,代表测试数据组数。

每组测试数据共两行。

第一行，一个整数M。其含义为： 每个司令部 一开始 都有M个生命元( 1 <= M <= 10000)

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000

输出
对每组测试数据，要求输出从0时0分开始，到双方司令部都停止制造武士为止的所有事件。

对每组测试数据，首先输出“Case:n" n是测试数据的编号，从1开始

接下来按恰当的顺序和格式输出所有事件。每个事件都以事件发生的时间开头，时间以小时为单位，有三位。
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

class Weapon{
private:
     int num;
     std::vector<std::string> names;
public:
      Weapon(){
          this->names.push_back("sword");
          this->names.push_back("bomb");
          this->names.push_back("arrow");
      };
      Weapon(int i){
          this->num = i;
          this->names.push_back("sword");
          this->names.push_back("bomb");
          this->names.push_back("arrow");}
      std::string get_weapon_name(){return this->names[this->num];}
      void set_num(int i){this->num = i;}
  };

class Soldier{
private:
    int num;
    int life_num;
public:
    Soldier(){};
    Soldier(int num, int life_num){this->num = num;this->life_num = life_num;}
    void set_life_num(int life_num_){this->life_num = life_num_;}
    void set_num(int num_){this->num = num_;}
    int get_life_num(){return this->life_num;}
    int get_num(){return this->num;}
    virtual std::string get_name() = 0;
    virtual void print_status() = 0;
    // 添加虚析构函数
    virtual ~Soldier() {}
};

class DragonSoldier: public Soldier{
private:
      Weapon w;
      double morale;
public:
      DragonSoldier(){};
      DragonSoldier(int num, int life_num, double morale) : Soldier(num, life_num){
             this->w.set_num(num%3);
             this->morale = morale;
      }
      double get_morale(){return this->morale;}
      std::string get_weapon_name(){return this->w.get_weapon_name();}
      std::string get_name(){return "dragon";}
      void print_status(){
          std::cout << "It has a "
                    << this->get_weapon_name()
                    <<",and it's morale is "
                    << std::fixed << std::setprecision(2) << this->morale
                    << std::endl;
      }
};

class NinjaSoldier: public Soldier{
private:
    Weapon w1, w2;
public:
    NinjaSoldier(){};
    NinjaSoldier(int num, int life_num) : Soldier(num, life_num){
        this->w1.set_num(num%3);
        this->w2.set_num((num+1)%3);
    }
    std::string get_weapon_name(){
        return "a " + this->w1.get_weapon_name()+ " and a " + this->w2.get_weapon_name();
    }
    std::string get_name(){return "ninja";}
    void print_status(){
        std::cout << "It has " << this->get_weapon_name() << std::endl;
    }

};

class IcemanSoldier: public Soldier{
private:
    Weapon w1;
public:
    IcemanSoldier(){};
    IcemanSoldier(int num, int life_num) : Soldier(num, life_num){this->w1.set_num(num%3);}
    std::string get_weapon_name(){return this->w1.get_weapon_name();}
    std::string get_name(){return "iceman";}
    void print_status(){std::cout << "It has a " << this->get_weapon_name() << std::endl;}
};

class LionSoldier: public Soldier{
private:
    int loyalty;
public:
    LionSoldier(){};
    LionSoldier(int num, int life_num, int loyalty) : Soldier(num, life_num), loyalty(loyalty){}
    int get_loyalty(){return this->loyalty;}
    std::string get_name(){return "lion";}
    void print_status(){std::cout <<"It's loyalty is " << this->get_loyalty() << std::endl;}
};

class WolfSoldier: public Soldier{
public:
  WolfSoldier(){};
  WolfSoldier(int num, int life_num) : Soldier(num, life_num){}
  std::string get_name(){return "wolf";}
  void print_status(){}
};


class DemonArmy{
private:
    int life_num; // 生命值
    int now_time; //当前时间
    int now_index; //当前制作士兵的顺序
    bool stop_status; // 当前是否停止制作
    std::string name; // 军营的名字
    std::vector<std::string> soldier_names; // 制作士兵的顺序
    std::vector< std::vector<Soldier*> > soldier_content; // 制作士兵的结果保存
    std::map<std::string, int> soldier_name_life_map; // 制作士兵需要耗费的生命值
 public:
     bool get_stop_status(){return stop_status;}
     DemonArmy(std::string name, int life_num, std::map<std::string, int>&soldier_name_life_map,
              std::vector<std::string> &soldier_names){
       this->life_num = life_num;
       this->now_time = 0;
       this->now_index = 0;
       this->name = name;
       this->soldier_names = soldier_names;
       this->soldier_name_life_map = soldier_name_life_map ;
       this->stop_status = false;
       this->soldier_content.resize(5);
     }
    ~DemonArmy(){
        for (size_t i = 0; i < this->soldier_content.size(); ++i) {
            for (size_t j = 0; j < this->soldier_content[i].size(); ++j) {
                delete this->soldier_content[i][j]; // 释放指针指向的对象
                this->soldier_content[i][j] = NULL; // 避免悬空指针
            }
            this->soldier_content[i].clear(); // 清空当前列表
        }
        this->soldier_content.clear(); // 清空所有士兵内容

    }
     void print_soldier_status(Soldier & sd){
       std::cout    << std::setw(3)
                    << std::setfill('0')
                    << this->now_time << " "
                    << this->name <<" "
                    << sd.get_name() <<" "
                    << this->now_time+1 << " born with strength "
                    << sd.get_life_num() <<","
                    << this->soldier_content[this->now_index%5].size() << " "
                    << sd.get_name() << " in "
                    << this->name <<" headquarter"
                    << std::endl;
       sd.print_status();
       }
      void print_stop_status(){
           std::cout << std::setw(3) << std::setfill('0') << this->now_time<<" "
                     << this->name
                     << " headquarter stops making warriors" << std::endl;
        }
    Soldier* create_solider(std::string& soldier_name, int num, int life_num){
         this->life_num -= life_num;
         if (soldier_name == "dragon"){
             double morale = 1.0*this->life_num/life_num;
             return new DragonSoldier(num,life_num, morale);
         }else if (soldier_name == "ninja"){
             NinjaSoldier ns(num,life_num);
             return new NinjaSoldier(num,life_num);
         }
         else if (soldier_name == "iceman"){
             IcemanSoldier is(num, life_num);
             return new IcemanSoldier(num, life_num);
         }
         else if (soldier_name == "lion"){
             return new LionSoldier(num, life_num, this->life_num);
         }else{
             return new WolfSoldier(num, life_num);
         }
     }
     void generate_next_soldier(){
          if (this->stop_status){return;}
          std::string now_soldier_name(this->soldier_names[this->now_index%5]);
          int soldier_life_num = this->soldier_name_life_map[now_soldier_name];
          // 如果当前军营的生命值大于可以制造士兵的生命值
          if (this->life_num >= soldier_life_num){
              // 制造士兵
              Soldier * now_soldier = this->create_solider(now_soldier_name,this->now_time+1,soldier_life_num);
              // 保存士兵
              this->soldier_content[this->now_index%5].push_back(now_soldier);
              // 打印士兵状态
              this->print_soldier_status(*now_soldier);
              // 增加时间，增加指数
              this->now_time++;
              this->now_index++;

            }
          //如果当前军营的生命值不足以制造当前的士兵，查看能否制造其他士兵，否则就停止制造
          else{
                bool stop = true;
                for(int i =0; i<5; i++){
                    this->now_index++;
                    std::string now_soldier_name(this->soldier_names[this->now_index%5]);
                    int soldier_life_num = this->soldier_name_life_map[now_soldier_name];
                    if (this->life_num >= soldier_life_num){
                            // 制造士兵
                            Soldier * now_soldier = this->create_solider(now_soldier_name,this->now_time+1,soldier_life_num);
                            // 保存士兵
                            this->soldier_content[this->now_index%5].push_back(now_soldier);
                            // 打印士兵状态
                            this->print_soldier_status(*now_soldier);
                            // 增加时间，增加指数
                            this->now_time++;
                            this->now_index++;
                            stop = false;
                            break;
                          }
                    }
                this->stop_status = stop;
                if (this->stop_status){
                  print_stop_status();
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

    int case_num;
    std::cin >> case_num;
    for (int i=0 ;i<case_num; ++i){
      int  life_num, a, b,c,d,e;
      std::cin >> life_num >> a >> b >> c >> d >> e;
      std::map<std::string, int> soldier_name_life_map;
      soldier_name_life_map["dragon"] = a;
      soldier_name_life_map["ninja"] = b;
      soldier_name_life_map["iceman"] = c;
      soldier_name_life_map["lion"] = d;
      soldier_name_life_map["wolf"] = e;
      std::cout << "Case:" << i+1 << std::endl;
      DemonArmy red_army("red", life_num, soldier_name_life_map, red_names);
      DemonArmy blue_army("blue", life_num, soldier_name_life_map, blue_names);
      while (!red_army.get_stop_status() || !blue_army.get_stop_status()){
        red_army.generate_next_soldier();
        blue_army.generate_next_soldier();
      }
    }

    return 0;
}