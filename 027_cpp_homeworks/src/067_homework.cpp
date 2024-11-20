# include<iostream>
# include<iomanip>
# include<string>
# include<cmath>
# include<map>
using namespace std;

# define WEPON_MAX_NUM 3				// 根据题意一个武士拥有的最多武器件数
# define WARRIOR_KIND_NUM 5				// 武士的种类
# define SWORD_DAMAGE 2 / 10			// sword的初始攻击力为拥有者的百分比
# define SWORD_ABRASE 8 / 10			// 每使用一次攻击力为原攻击力的百分比
# define ICEMAN_LIFE_REDUCE 9			// 每前进两步iceman生命值减少量
# define ICEMAN_DAMAGE_INCREASE 20		// 每前进两部iceman攻击力增加量
# define HEADQUARTER_INSPIRE 8			// 司令部向获胜的战士奖励的生命元个数

int CITY_NUM;							// 两个司令部之间城市的数量
int TIME_NUM;							// 每组进行总的世界，以分为单位
int ARROW_DAMAGE;						// 弓箭的攻击力
int LIFE_ELEMENT;						// 一开始拥有的生命元数量
int LION_LOAYLTY_REDUCE;				// lion每经过一场未能杀死敌人的战斗，忠诚度降低值
double DRAGON_MORALE_CHANGE = 0.2;		// dragon每经过一场战斗，士气变化值
double DRAGON_MORALE_YELL = 0.8;		// dragon欢呼的判定条件之一（士气值的最小界，不包括）

map<string, int> WARRIOR_LIFE;												// 制造各种武士所需的生命元
map<string, int> WARRIOR_DAMAGE;											// 每种武士的攻击力
//map<string, int>WEPON_USE_TIME = { {"sword",-1},{"bomb",1},{"arrow",3} };	// 武器使用次数，-1表示可以无限次数使用
map<string, int> WEPON_USE_TIME; // 全局变量

void initializeWeaponUseTime() {
    WEPON_USE_TIME.insert(make_pair("sword", -1));
    WEPON_USE_TIME.insert(make_pair("bomb", 1));
    WEPON_USE_TIME.insert(make_pair("arrow", 3));
}

string WEPON_LIST[3] = { "sword","bomb","arrow" };											// 武器列表
string WARRIOR_CIN_SORT[WARRIOR_KIND_NUM] = { "dragon","ninja","iceman","lion","wolf" };	// 生命值和攻击力输入顺序


class CWarrior;
// 武器类
class CWepon {
public:
    string name;		// 武器名称
    int id;				// 武器编号
    int damage_value;	// 武器攻击力
    int use_time;		// 使用次数
    // 构造函数
    CWepon(int _id) :id(_id), damage_value(0) {
        // damage_value的赋值主要放在派生类的构造函数中进行，这里先默认设置为0
        name = WEPON_LIST[_id];
        use_time = WEPON_USE_TIME[name];
    }
    // 重载运算符实现武器之间的大小比较
    bool operator > (const CWepon& compare_object) {
        if (id > compare_object.id)return true;
        else return false;
    }
    // 使用武器
    virtual void use_attribute(CWarrior* warrior_use, CWarrior* warrior_victim) {}
    virtual void use_attribute(int city_num, int time_now, CWarrior* warrior_use, CWarrior* warrior_victim) {}
    virtual ~CWepon() {}
};

// 武器派生类sword
class CSword :public CWepon {
public:
    // 构造函数
    CSword(int _id, int warrior_damage_value) :CWepon(_id) {
        // 初始攻击力为拥有它的武士的攻击力的20%
        damage_value = warrior_damage_value * SWORD_DAMAGE;
    }
    // 使用属性
    virtual void use_attribute(CWarrior* warrior_use, CWarrior* warrior_victim);
};

// 武器派生类arrow
class CArrow :public CWepon {
public:
    // 构造函数
    CArrow(int _id, int _damage_value) :CWepon(_id) {
        damage_value = _damage_value;
    }
    // 使用属性
    virtual void use_attribute(CWarrior* warrior_use, CWarrior* warrior_victim);
};

// 武器派生类bomb
class CBomb :public CWepon {
public:
    // 构造函数
    CBomb(int _id) :CWepon(_id) {
        // -1表示攻击力无限大
        damage_value = -1;
    }
    virtual void use_attribute(int city_num, int time_now, CWarrior* warrior_use, CWarrior* warrior_victim);
};

class CCity;
// 武士类
class CWarrior {
public:
    string color;			// 所属阵营
    string name;			// 所属种类
    int id;					// 编号
    int life_value;			// 生命值
    int damage_value;		// 攻击力
    int wepon_num_total;	// 拥有的武器总数
    int has_shoot;			// 是否放过弓箭在该小时的35分放过弓箭：0表示未放过弓箭，-1表示放过弓箭，1表示放过弓箭且射死敌方
    CWepon* wepon[WEPON_MAX_NUM];			// 拥有的武器
    // 构造函数
    CWarrior(string _color, string _name, int _id, int _life_value, int _damage_value) :
            color(_color), name(_name), id(_id), life_value(_life_value), damage_value(_damage_value), wepon_num_total(0), has_shoot(0) {
        // 初始化拥有的武器未空
        for (int i = 0; i < WEPON_MAX_NUM; ++i) {
            wepon[i] = NULL;
        }
    }
    // 武士降生时获取初始武器
    void get_wepon_initial(int wepon_id) {
        CWepon* ptr_wepon = NULL;
        if (wepon_id == 0) {
            ptr_wepon = new CSword(wepon_id, WARRIOR_DAMAGE[name]);
            if (ptr_wepon->damage_value == 0) {
                // 如果初试获得的sword攻击力为0，则视为武士没有sword
                delete ptr_wepon;
                ptr_wepon = NULL;
            }
        }
        else if (wepon_id == 1) {
            ptr_wepon = new CBomb(wepon_id);
        }
        else if (wepon_id == 2) {
            ptr_wepon = new CArrow(wepon_id, ARROW_DAMAGE);
        }
        // 为武士装备武器
        if (ptr_wepon != NULL) {
            wepon[wepon_num_total++] = ptr_wepon;
        }
    }
    // 更新自身拥有的武器总数即各种武器数量
    void update_wepon_num() {
        wepon_num_total = 0;
        for (int i = 0; i < WEPON_MAX_NUM; ++i) {
            if (wepon[i] != NULL) {
                ++wepon_num_total;
            }
        }
    }
    // 对自身拥有的武器进行排序（编号从小到大）和更新武器数量
    void sort_wepon() {
        for (int i = WEPON_MAX_NUM - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                if ((wepon[j] == NULL && wepon[j + 1] != NULL) || (wepon[j] != NULL && wepon[j + 1] != NULL && *wepon[j] > *wepon[j + 1])) {
                    CWepon* tmp = wepon[j + 1];
                    wepon[j + 1] = wepon[j];
                    wepon[j] = tmp;
                }
            }
        }
        update_wepon_num();
    }
    // 报告自身的武器情况
    void print_wepon_info(int time_now) {
        int arrow_use_time = 0, bomb_num = 0, sword_damage = 0;
        for (int i = 0; i < WEPON_MAX_NUM; ++i) {
            if (wepon[i] != NULL) {
                if (wepon[i]->name == "sword")sword_damage = wepon[i]->damage_value;
                if (wepon[i]->name == "bomb")bomb_num = 1;
                if (wepon[i]->name == "arrow")arrow_use_time = wepon[i]->use_time;
            }
        }
        if (!arrow_use_time && !bomb_num && !sword_damage) {
            cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << color << " " << name << " " << id
                 << " has no weapon";
        }
        else {
            int flag_first = 0, flag_second = 0;
            cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << color << " " << name << " " << id << " has ";
            if (arrow_use_time) {
                flag_first = 1;
                cout << "arrow(" << arrow_use_time << ")";
            }
            if (bomb_num && flag_first) {
                flag_second = 1;
                cout << ",bomb";
            }
            else if (bomb_num && !flag_first) {
                flag_second = 1;
                cout << "bomb";
            }
            if (sword_damage && (flag_first || flag_second)) {
                cout << ",sword(" << sword_damage << ")";
            }
            else if (sword_damage && !flag_first && !flag_second) {
                cout << "sword(" << sword_damage << ")";
            }

        }
        cout << endl;
    }
    // 放箭，成功放箭返回true，无箭可放返回false
    void use_arrow(int time_now, CWarrior* warrior_victim) {
        int arrow_position = -1;
        for (int i = 0; i < WEPON_MAX_NUM; ++i) {
            if (wepon[i] != NULL && wepon[i]->name == "arrow") {
                arrow_position = i;
                break;
            }
        }
        if (arrow_position == -1) return;
        else has_shoot = -1;
        wepon[arrow_position]->use_attribute(this, warrior_victim);
        // 若成功放箭，则判断使用后弓箭的状态
        if (wepon[arrow_position]->use_time == 0) {
            delete wepon[arrow_position];
            wepon[arrow_position] = NULL;
        }
        return;
    }
    // 若有bomb，返回bomb在武器中的位置，若没有则返回-1
    int bomb_num() {
        int num = -1;
        for (int i = 0; i < WEPON_MAX_NUM; ++i) {
            if (wepon[i] != NULL && wepon[i]->name == "bomb") {
                num = i;
                break;
            }
        }
        return num;
    }
    // 若有sword，返回sword在武器中的位置，若没有则返回-1
    int sword_num() {
        int num = -1;
        for (int i = 0; i < WEPON_MAX_NUM; ++i) {
            if (wepon[i] != NULL && wepon[i]->name == "sword") {
                num = i;
                break;
            }
        }
        return num;
    }
    // 战斗获胜属性
    virtual void win_fight(int city_num, int time_now, CWarrior* loser) {}
    // 战斗平局属性
    virtual void peace_fight() {}
    // 进攻，time_flag为1表示主动进攻，为-1表示反击
    void attack(int city_num, int time_now, CWarrior* warrior_against, int time_flag) {
        // ninja被挨打不会反击
        if (name == "ninja" && time_flag == -1) return;
        // 为进攻事件进行输出
        if (time_flag == 1) {
            cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << color << " " << name << " " << id << " attacked " << warrior_against->color
                 << " " << warrior_against->name << " " << warrior_against->id << " in city " << city_num << " with " << life_value
                 << " elements and force " << damage_value << endl;
        }
        else if (time_flag == -1 && name != "ninja") {
            cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << color << " " << name << " " << id << " fought back against " << warrior_against->color
                 << " " << warrior_against->name << " " << warrior_against->id << " in city " << city_num << endl;
        }
        int sword_id = sword_num();
        if (sword_id != -1) {
            wepon[sword_id]->use_attribute(this, warrior_against);
            // 判断武器状态
            if (wepon[sword_id]->damage_value == 0) {
                delete wepon[sword_id];
                wepon[sword_id] = NULL;
            }
        }
        if (time_flag == 1)warrior_against->life_value -= damage_value;
        else if (time_flag == -1)warrior_against->life_value -= damage_value * 1 / 2;
        return;
    }
    // 若是lion，若在一场战斗中没有战死，且为进攻方，则可以进行欢呼
    virtual void dragon_live(int city_num, int time_now, CCity* ptr_city_list) {}
    // 虚析构函数
    virtual ~CWarrior() {
        for (int i = 0; i < WEPON_MAX_NUM; ++i) {
            if (wepon[i] != NULL)delete wepon[i];
        }
    }
};

// 武士派生类dragon
class CDragon :public CWarrior {
public:
    double morale;					// 士气
    // 构造函数
    CDragon(string _color, string _name, int _id, int _life_value, int _damage_value, double _morale) :
            CWarrior(_color, _name, _id, _life_value, _damage_value), morale(_morale) {
        // 装备初始武器
        get_wepon_initial(id % 3);
    }
    // 欢呼
    void dragon_yell(int time_now, int city_num) {
        cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << color << " " << name
             << " " << id << " yelled in city " << city_num << endl;
    }
    // 战胜属性
    virtual void win_fight(int city_num, int time_now, CWarrior* loser) {
        morale += DRAGON_MORALE_CHANGE;
    }
    // 平局属性
    virtual void peace_fight() {
        morale -= DRAGON_MORALE_CHANGE;
    }
    // dragon获胜或平局进行欢呼
    virtual void dragon_live(int city_num, int time_now, CCity* ptr_city_list);
};

// 武士派生类ninja
class CNinja :public CWarrior {
public:
    // 构造函数
    CNinja(string _color, string _name, int _id, int _life_value, int _damage_value) :
            CWarrior(_color, _name, _id, _life_value, _damage_value) {
        // 装备初始武器
        get_wepon_initial(id % 3);
        get_wepon_initial((id + 1) % 3);
    }
};

// 武士派生类iceman
class CIceman :public CWarrior {
public:
    int step;						// 到达城市时记录一共走了几步
    // 构造函数
    CIceman(string _color, string _name, int _id, int _life_value, int _damage_value) :
            CWarrior(_color, _name, _id, _life_value, _damage_value), step(0) {
        // 装备初始武器
        get_wepon_initial(id % 3);
    }
    // 前进属性(攻击力变化，注意对sword的影响)
    void advance_attribute() {
        if ((++step) % 2 == 0) {
            // 每前进2步，在第二步完成时，生命值减少，攻击力增加
            life_value -= ICEMAN_LIFE_REDUCE;
            if (life_value <= 0)life_value = 1;
            damage_value += ICEMAN_DAMAGE_INCREASE;
        }
    }
};

// 武士派生类lion
class CLion :public CWarrior {
public:
    int loyalty;							// 忠诚度
    CLion(string _color, string _name, int _id, int _life_value, int _damage_value, int _loyalty) :
            CWarrior(_color, _name, _id, _life_value, _damage_value), loyalty(_loyalty) {
    }
    virtual void peace_fight() {
        // 经过一场未能杀死敌人的战斗，忠诚度就降低
        loyalty -= LION_LOAYLTY_REDUCE;
    }
};

// 武士派生类wolf
class CWolf :public CWarrior {
public:
    // 构造函数
    CWolf(string _color, string _name, int _id, int _life_value, int _damage_value) :
            CWarrior(_color, _name, _id, _life_value, _damage_value) {}
    // 若杀死敌人则获取敌人的武器(武器易主，注意对sword的影响)
    void grab_wepon(CWarrior* warrior_victim) {
        // 先对自身武器进行排序
        sort_wepon();
        int j;
        for (int i = 0; i < WEPON_MAX_NUM && wepon_num_total < WEPON_MAX_NUM; ++i) {
            if (warrior_victim->wepon[i] != NULL) {
                for (j = 0; j < wepon_num_total; ++j) {
                    if (warrior_victim->wepon[i]->name == wepon[j]->name)break;
                }
                // 若不存在该类型武器则缴获，若缴获sword且还未使用过
                if (j == wepon_num_total) {
                    // 若缴获sword且还未使用过，则更新其初始攻击力
                    //if (warrior_victim->wepon[i]->name == "sword" && warrior_victim->wepon[i]->use_time == WEPON_USE_TIME["sword"]) {
                    //	warrior_victim->wepon[i]->damage_value = damage_value * SWORD_DAMAGE;
                    //}
                    wepon[wepon_num_total++] = warrior_victim->wepon[i];
                    warrior_victim->wepon[i] = NULL;
                    --warrior_victim->wepon_num_total;
                }
            }
        }
    }
    virtual void win_fight(int city_num, int time_now, CWarrior* loser) {
        grab_wepon(loser);
    }
};

// 城市类
class CCity {
public:
    CWarrior* warrior_red;			// 位于该城市的红方武士指针
    CWarrior* warrior_red_tmp;		// 辅助红方武士移动的指针
    CWarrior* warrior_blue;			// 位于该城市的蓝方武士指针
    int life_element;				// 城市中产生的生命元
    int red_win;					// 红方连赢次数
    int blue_win;					// 蓝方连赢次数
    int flag;						// 0代表无旗，1代表红旗，-1代表蓝旗
    // 构造函数
    CCity() :warrior_red(NULL), warrior_red_tmp(NULL), warrior_blue(NULL), life_element(0), red_win(0), blue_win(0), flag(0) {}
    // 判断该城市的旗帜是否改变
    void flag_change(int time_now, int city_num) {
        if (warrior_red->life_value > 0 && warrior_blue->life_value <= 0) {
            // 红方获胜
            blue_win = 0;
            if (flag == 1)return;
            if (++red_win == 2) {
                flag = 1;
                cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " red flag raised in city " << city_num << endl;
            }
        }
        if (warrior_blue->life_value > 0 && warrior_red->life_value <= 0) {
            // 蓝方获胜
            red_win = 0;
            if (flag == -1)return;
            if (++blue_win == 2) {
                flag = -1;
                cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " blue flag raised in city " << city_num << endl;
            }
        }
        if (warrior_red->life_value > 0 && warrior_blue->life_value > 0) {
            // 平局或使用bomb不会影响旗帜
            red_win = 0;
            blue_win = 0;
        }
    }
    // 析构函数
    ~CCity() {
        if (warrior_red != NULL)delete warrior_red;
        if (warrior_blue != NULL)delete warrior_blue;
    }
};

// 司令部类
class CHeadquarter {
public:
    string color;				// 所属派别
    int life_element;			// 生命元总数
    int total_num;				// 拥有的武士数量
    int make_num;				// 下一个要制造的武士编号
    int enemy_num;				// 到达该司令部的敌人数
    string make_sort[5];		// 制造武士的顺序
    // 构造函数
    CHeadquarter(string _color, int _life_element) :color(_color), life_element(_life_element), total_num(0), make_num(0), enemy_num(0) {
        if (_color == "red") {
            string _make_sort[5] = { "iceman", "lion", "wolf", "ninja", "dragon" };
            for (int i = 0; i < 5; ++i) make_sort[i] = _make_sort[i];

        }
        else if (_color == "blue") {
            string _make_sort[5] = { "lion","dragon","ninja","iceman","wolf" };
            for (int i = 0; i < 5; ++i) make_sort[i] = _make_sort[i];
        }
    }

    // 制造武士并投放城市
    void make_warrior(int time_now, CCity* ptr_city_list) {
        typedef CWarrior* (CHeadquarter::*Func_Ptr)(int); // 使用 typedef 替代 using

        // 初始化 map
        map<string, Func_Ptr> make_warrior_map;
        make_warrior_map.insert(make_pair("dragon", &CHeadquarter::make_warrior_dragon));
        make_warrior_map.insert(make_pair("ninja", &CHeadquarter::make_warrior_ninja));
        make_warrior_map.insert(make_pair("iceman", &CHeadquarter::make_warrior_iceman));
        make_warrior_map.insert(make_pair("lion", &CHeadquarter::make_warrior_lion));
        make_warrior_map.insert(make_pair("wolf", &CHeadquarter::make_warrior_wolf));
        string name = make_sort[make_num];
        int life_need = WARRIOR_LIFE[name];
        if (life_element >= life_need) {
            // 可以制造，更新司令部制造完武士后的状态
            life_element -= life_need;
            ++total_num;
            if (++make_num == WARRIOR_KIND_NUM)make_num = 0;
            // 输出制造信息
            cout << setfill('0') << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << color
                 << " " << name << " " << total_num << " born" << endl;
            // 生成武士并放入投入司令部
            CWarrior* ptr_warrior = (this->*make_warrior_map[name])(life_need);
            if (color == "red") {
                ptr_city_list[0].warrior_red = ptr_warrior;
            }
            else ptr_city_list[CITY_NUM + 1].warrior_blue = ptr_warrior;
        }
    }

    // 制造武士wolf
    CWarrior* make_warrior_wolf(int life_need) {
        CWarrior* ptr_wolf = new CWolf(color, "wolf", total_num, life_need, WARRIOR_DAMAGE["wolf"]);
        return ptr_wolf;
    }

    // 制造武士lion
    CWarrior* make_warrior_lion(int life_need) {
        // 计算忠诚度
        int loyalty = life_element;
        CWarrior* ptr_lion = new CLion(color, "lion", total_num, life_need, WARRIOR_DAMAGE["lion"], loyalty);
        // 输出其忠诚度
        cout << "Its loyalty is " << loyalty << endl;
        return ptr_lion;
    }

    // 制造武士iceman
    CWarrior* make_warrior_iceman(int life_need) {
        CWarrior* ptr_iceman = new CIceman(color, "iceman", total_num, life_need, WARRIOR_DAMAGE["iceman"]);
        return ptr_iceman;
    }

    // 制造武士ninja
    CWarrior* make_warrior_ninja(int life_need) {
        CWarrior* ptr_ninja = new CNinja(color, "ninja", total_num, life_need, WARRIOR_DAMAGE["ninja"]);
        return ptr_ninja;
    }

    // 制造武士dragon
    CWarrior* make_warrior_dragon(int life_need) {
        // 计算士气
        double morale = (double)life_element / (double)life_need;
        CWarrior* ptr_dragon = new CDragon(color, "dragon", total_num, life_need, WARRIOR_DAMAGE["dragon"], morale);
        cout << "Its morale is " << fixed << setprecision(2) << morale << endl;
        return ptr_dragon;
    }

    // 输出拥有的生命元数量
    void print_life_element_info(int time_now) {
        cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << life_element
             << " elements in " << color << " headquarter" << endl;
    }

};

void CSword::use_attribute(CWarrior* warrior_use, CWarrior* warrior_victim) {
    // 只造成等于sword攻击力的伤害值，磨损自身，use_time用来标志是否第一次使用sword
    warrior_victim->life_value -= damage_value;
    // 不可以写成damage_value *= SWORD_ABRASE, 因为这样SWORD_ABRASE直接被转变成0
    damage_value = damage_value * SWORD_ABRASE;
    --use_time;
}

void CArrow::use_attribute(CWarrior* warrior_use, CWarrior* warrior_victim) {
    // 造成伤害和减少一次使用次数
    warrior_victim->life_value -= damage_value;
    if (warrior_victim->life_value <= 0) {
        warrior_victim->life_value = 0;
        warrior_use->has_shoot = 1;
    }
    --use_time;
}

void CBomb::use_attribute(int city_num, int time_now, CWarrior* warrior_use, CWarrior* warrior_victim) {
    // 双方的生命值都变为0
    warrior_use->life_value = 0;
    warrior_victim->life_value = 0;
    --use_time;
    // 输出事件信息
    cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << warrior_use->color << " " << warrior_use->name << " " << warrior_use->id
         << " used a bomb and killed " << warrior_victim->color << " " << warrior_victim->name << " " << warrior_victim->id << endl;
}

void CDragon::dragon_live(int city_num, int time_now, CCity* ptr_city_list) {
    // 一场主动进攻的战斗结束时，没有被战死，则进行欢呼
    if (color == "red" && morale > DRAGON_MORALE_YELL) {
        if (ptr_city_list[city_num].flag == 1 || (ptr_city_list[city_num].flag == 0 && city_num % 2 == 1)) {
            dragon_yell(time_now, city_num);
        }
    }
    else if (color == "blue" && morale > DRAGON_MORALE_YELL) {
        if (ptr_city_list[city_num].flag == -1 || (ptr_city_list[city_num].flag == 0 && city_num % 2 == 0)) {
            dragon_yell(time_now, city_num);
        }
    }
}


// 接收数据，初始化信息
void cin_data() {
    // 接收生命元、城市、忠诚度变化、时间范围值
    cin >> LIFE_ELEMENT >> CITY_NUM >> ARROW_DAMAGE >> LION_LOAYLTY_REDUCE >> TIME_NUM;
    // 接收每种武士的生命值
    int life_value;
    for (int i = 0; i < WARRIOR_KIND_NUM; ++i) {
        cin >> life_value;
        WARRIOR_LIFE[WARRIOR_CIN_SORT[i]] = life_value;
    }
    // 接收每种武士的攻击力
    int warrior_damage;
    for (int i = 0; i < WARRIOR_KIND_NUM; ++i) {
        cin >> warrior_damage;
        WARRIOR_DAMAGE[WARRIOR_CIN_SORT[i]] = warrior_damage;
    }
    return;
}

// 判断武士是否是lion，若是其是否会逃跑
bool Lion_ran_second(int city_num, int time_now, CWarrior* ptr_warrior) {
    if (ptr_warrior != NULL && ptr_warrior->name == "lion") {
        CLion* ptr_warrior_lion = dynamic_cast<CLion*>(ptr_warrior);
        if (ptr_warrior_lion->loyalty <= 0) {
            // 在己方司令部可能逃跑，在地方司令部不会逃跑
            if ((ptr_warrior_lion->color == "red" && city_num != CITY_NUM + 1) || (ptr_warrior_lion->color == "blue" && city_num != 0)) {
                // 输出逃跑信息，释放指针
                cout << setfill('0') << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60
                     << " " << ptr_warrior_lion->color << " lion " << ptr_warrior_lion->id << " ran away" << endl;
                delete ptr_warrior_lion;
                ptr_warrior_lion = NULL;
                ptr_warrior = NULL;
                return true;
            }
        }
    }
    return false;
}

// lion逃跑事件
void Lion_ran(int city_num, int time_now, CCity* ptr_city_list) {
    // 先判断红方
    CWarrior* ptr_warrior = ptr_city_list[city_num].warrior_red;
    bool run_can = Lion_ran_second(city_num, time_now, ptr_warrior);
    if (run_can)ptr_city_list[city_num].warrior_red = NULL;
    // 再判断蓝方
    ptr_warrior = ptr_city_list[city_num].warrior_blue;
    run_can = Lion_ran_second(city_num, time_now, ptr_warrior);
    if (run_can)ptr_city_list[city_num].warrior_blue = NULL;
}

// 触发武士相应的前进属性，输出前进信息，判断是否占领司令部：-1红方被占，0双方未被占，1蓝方被占
int march_info(int city_num, int time_now, CWarrior* ptr_warrior, CHeadquarter& red_quarter, CHeadquarter& blue_quarter) {
    // 这里的city_num表示的是到达城市的编号
    if (ptr_warrior->name == "iceman") {
        CIceman* ptr_iceman = dynamic_cast<CIceman*>(ptr_warrior);
        ptr_iceman->advance_attribute();
    }
    if (ptr_warrior->color == "blue" && city_num == 0) {
        // 抵达司令部
        cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << ptr_warrior->color << " " << ptr_warrior->name
             << " " << ptr_warrior->id << " reached red headquarter with " << ptr_warrior->life_value
             << " elements and force " << ptr_warrior->damage_value << endl;
        if (++red_quarter.enemy_num == 2) {
            // 占领红方司令部
            return -1;
        }
    }
    else if (ptr_warrior->color == "red" && city_num == CITY_NUM + 1) {
        // 抵达司令部
        cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << ptr_warrior->color << " " << ptr_warrior->name
             << " " << ptr_warrior->id << " reached blue headquarter with " << ptr_warrior->life_value
             << " elements and force " << ptr_warrior->damage_value << endl;
        if (++blue_quarter.enemy_num == 2) {
            // 占领蓝方司令部
            return 1;
        }
    }
    else {
        // 双方司令部还未占领
        cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << ptr_warrior->color << " " << ptr_warrior->name
             << " " << ptr_warrior->id << " marched to city " << city_num << " with " << ptr_warrior->life_value
             << " elements and force " << ptr_warrior->damage_value << endl;
    }
    return 0;
}

// 双方士兵前进，对于红方来说city_num是出发的城市编号，对于蓝方来说city_num是到达的城市编号
int march_city(int city_num, int time_now, CCity* ptr_city_list, CHeadquarter& red_quarter, CHeadquarter& blue_quarter) {
    int result = 0;
    if (ptr_city_list[city_num + 1].warrior_blue != NULL) {
        // 蓝方武士向西前进
        ptr_city_list[city_num].warrior_blue = ptr_city_list[city_num + 1].warrior_blue;
        ptr_city_list[city_num + 1].warrior_blue = NULL;
        CWarrior* ptr_warrior = ptr_city_list[city_num].warrior_blue;
        // 触发武士前进属性，输出武士前进信息
        int tmp_result = march_info(city_num, time_now, ptr_warrior, red_quarter, blue_quarter);
        if (tmp_result == -1) {
            // 红方司令部被占领
            result = -1;
            cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " red headquarter was taken" << endl;
            // 这里千万不能直接return one_win，因为一旦红方被占领，若红司令部有武士要前进到city1的话就得不到输出
        }
    }
    if (ptr_city_list[city_num].warrior_red_tmp != NULL) {
        // 红方武士向东前进
        ptr_city_list[city_num + 1].warrior_red = ptr_city_list[city_num].warrior_red_tmp;
        ptr_city_list[city_num].warrior_red_tmp = NULL;
        CWarrior* ptr_warrior = ptr_city_list[city_num + 1].warrior_red;
        // 触发武士前进属性，输出武士前进信息
        int tmp_result = march_info(city_num + 1, time_now, ptr_warrior, red_quarter, blue_quarter);
        if (tmp_result == 1) {
            // 输出蓝方被占领
            result = 1;
            cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " blue headquarter was taken" << endl;
        }
    }
    return result;
}

// 若某个城市只有一个武士，则武士取走生命元传回司令部
void take_element(int city_num, int time_now, CCity* ptr_city_list, CHeadquarter& red_quarter, CHeadquarter& blue_quarter) {
    CWarrior* warrior_red = ptr_city_list[city_num].warrior_red;
    CWarrior* warrior_blue = ptr_city_list[city_num].warrior_blue;
    CWarrior* warrior_take = NULL;
    int city_element = ptr_city_list[city_num].life_element;
    bool take_away = false;
    // 红方取走
    if (warrior_red != NULL && warrior_blue == NULL) {
        red_quarter.life_element += city_element;
        warrior_take = warrior_red;
        take_away = true;
    }
        // 蓝方取走
    else if (warrior_blue != NULL && warrior_red == NULL) {
        blue_quarter.life_element += city_element;
        warrior_take = warrior_blue;
        take_away = true;
    }
    // 输出事件
    if (take_away) {
        cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << warrior_take->color << " " << warrior_take->name
             << " " << warrior_take->id << " earned " << city_element << " elements for his headquarter" << endl;
        ptr_city_list[city_num].life_element = 0;
    }
    return;
}

// 使用arrow事件
void shoot_arrow(int city_num, int time_now, CCity* ptr_city_list) {
    CWarrior* warrior_red = ptr_city_list[city_num].warrior_red;
    CWarrior* warrior_blue = ptr_city_list[city_num + 1].warrior_blue;
    if (warrior_red != NULL && warrior_blue != NULL && warrior_red->life_value > 0 && warrior_blue->life_value > 0) {
        // 放箭
        warrior_red->use_arrow(time_now, warrior_blue);
        warrior_blue->use_arrow(time_now, warrior_red);
    }
}

// 判断是否放箭，以及放箭是否射死敌人
void shoot_result_second(int city_num, int time_now, CWarrior* warrior, CWarrior* enemy) {
    if (enemy != NULL && warrior->has_shoot == 1) {
        cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << warrior->color << " " << warrior->name
             << " " << warrior->id << " shot and killed " << enemy->color << " " << enemy->name
             << " " << enemy->id << endl;
        warrior->has_shoot = 0;
    }
    else if (enemy != NULL && warrior->has_shoot == -1) {
        cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << warrior->color << " " << warrior->name
             << " " << warrior->id << " shot" << endl;
        warrior->has_shoot = 0;
    }
    return;
}

// 输出放箭事件结果（因为放箭事件算发生在箭发出的城市，因此在所有放箭结束后再来判定和输出）
void shoot_result(int city_num, int time_now, CCity* ptr_city_list) {
    CWarrior* warrior_red = ptr_city_list[city_num].warrior_red;
    CWarrior* warrior_blue = ptr_city_list[city_num].warrior_blue;
    CWarrior* enemy_against = NULL;
    // 若此时战士血量小于等于0，则说明其被弓箭射死，被射死的武士暂时不被释放，因为在40分战斗开始前还要进行判断
    if (warrior_red != NULL) {
        enemy_against = ptr_city_list[city_num + 1].warrior_blue;
        shoot_result_second(city_num, time_now, warrior_red, enemy_against);
    }
    if (warrior_blue != NULL) {
        enemy_against = ptr_city_list[city_num - 1].warrior_red;
        shoot_result_second(city_num, time_now, warrior_blue, enemy_against);
    }
    return;
}

// attack_flag为1代表attacker是主动进攻方，attack_flag为-1表示attacker是反击方，炸弹在victim手上
void throw_bomb_second(int city_num, int time_now, CWarrior* attacker, CWarrior* victim, int victim_bomb_num, int attack_flag) {
    // 如果victim主动进攻时能够杀死attacker，那么就不存在反击一说，因此先行判断
    if (attack_flag == -1) {
        int victim_damage = victim->damage_value;
        int victim_sword = victim->sword_num();
        int attacker_life = attacker->life_value;
        attacker_life -= victim_damage;
        if (victim_sword != -1)attacker_life -= victim->wepon[victim_sword]->damage_value;
        if (attacker_life <= 0)return;
    }
    int victim_life = victim->life_value;
    int attacker_damage = attacker->damage_value;
    // 反击方攻击力取自身攻击力的一半
    if (attack_flag == -1)attacker_damage = attacker_damage * 1 / 2;
    victim_life -= attacker_damage;
    int attacker_sword = attacker->sword_num();
    if (attacker_sword != -1)victim_life -= attacker->wepon[attacker_sword]->damage_value;
    if (victim_life <= 0)victim->wepon[victim_bomb_num]->use_attribute(city_num, time_now, victim, attacker);
    return;
}

// 使用bomb事件
void throw_bomb(int city_num, int time_now, CCity* ptr_city_list) {
    CWarrior* warrior_red = ptr_city_list[city_num].warrior_red;
    CWarrior* warrior_blue = ptr_city_list[city_num].warrior_blue;
    if (warrior_red != NULL && warrior_blue != NULL && warrior_red->life_value > 0 && warrior_blue->life_value > 0) {
        // 若有bomb则获取bomb在武器数组中的位置，没有bomb位置将返回-1
        int red_bomb_num = warrior_red->bomb_num();
        int blue_bomb_num = warrior_blue->bomb_num();
        // 红方有炸弹的情况下进行判断是否使用：分为蓝方是进攻方和蓝方是反击方
        if (red_bomb_num != -1) {
            if (ptr_city_list[city_num].flag == -1 || (ptr_city_list[city_num].flag == 0 && city_num % 2 == 0)) {
                // 若蓝方是进攻方（插蓝旗，以及编号为偶数的无旗城市）
                throw_bomb_second(city_num, time_now, warrior_blue, warrior_red, red_bomb_num, 1);
            }
            else if (warrior_blue->name != "ninja" && (ptr_city_list[city_num].flag == 1 || (ptr_city_list[city_num].flag == 0 && city_num % 2 == 1))) {
                // 若蓝方是反击方（插红旗，以及编号为奇数的无旗城市）且不是ninja，因为ninja不会反击
                throw_bomb_second(city_num, time_now, warrior_blue, warrior_red, red_bomb_num, -1);
            }
        }
        // 蓝方有炸弹的情况下进行判断是否使用，若红方已经启用炸弹就不用判断了
        if (warrior_red->life_value > 0 && warrior_blue->life_value > 0 && blue_bomb_num != -1) {
            if (ptr_city_list[city_num].flag == 1 || (ptr_city_list[city_num].flag == 0 && city_num % 2 == 1)) {
                // 若红方是进攻方（插红旗，以及编号为奇数的无旗城市）
                throw_bomb_second(city_num, time_now, warrior_red, warrior_blue, blue_bomb_num, 1);
            }
            else if (warrior_red->name != "ninja" && (ptr_city_list[city_num].flag == -1 || (ptr_city_list[city_num].flag == 0 && city_num % 2 == 0))) {
                // 若红方是反击方且不是ninja
                throw_bomb_second(city_num, time_now, warrior_red, warrior_blue, blue_bomb_num, -1);
            }
        }
    }
    // 有可能双方都被弓箭射死了，也有可能是双方使用bomb同归于尽了，此时可以释放
    if (warrior_red != NULL && warrior_blue != NULL && warrior_red->life_value <= 0 && warrior_blue->life_value <= 0) {
        delete warrior_red;
        delete warrior_blue;
        ptr_city_list[city_num].warrior_red = NULL;
        ptr_city_list[city_num].warrior_blue = NULL;
    }
}

// 针对在战斗开始前，attcker是在这次攻击中进攻的一方，attack_flag为1代表此次为主动进攻，为-1表示反击
bool fight_against_second(int city_num, int time_now, CWarrior* attcker, CWarrior* against, CCity* ptr_city_list, int attack_flag) {
    attcker->attack(city_num, time_now, against, attack_flag);
    if (against->life_value <= 0) {
        cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << against->color << " " << against->name << " "
             << against->id << " was killed in city " << city_num << endl;
        // 触发胜利属性
        attcker->win_fight(city_num, time_now, against);
        return true;
    }
    return false;
}

// 战斗事件
void fight_against(int city_num, int time_now, CCity* ptr_city_list) {
    CWarrior* warrior_red = ptr_city_list[city_num].warrior_red;
    CWarrior* warrior_blue = ptr_city_list[city_num].warrior_blue;
    if (warrior_red != NULL && warrior_blue != NULL) {
        // 有一方可能已经被弓箭射死
        if (warrior_red->life_value > 0 && warrior_blue->life_value <= 0) {
            // 暂且不释放,输出司令部获取城市生命元信息（实际待奖励后再获取）
            warrior_red->win_fight(city_num, time_now, warrior_blue);
            if (warrior_red->name == "dragon")warrior_red->dragon_live(city_num, time_now, ptr_city_list);
            cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << warrior_red->color << " " << warrior_red->name
                 << " " << warrior_red->id << " earned " << ptr_city_list[city_num].life_element << " elements for his headquarter" << endl;
            // 刷新旗帜
            ptr_city_list[city_num].flag_change(time_now, city_num);

        }
        else if (warrior_blue->life_value > 0 && warrior_red->life_value <= 0) {
            warrior_blue->win_fight(city_num, time_now, warrior_red);
            if (warrior_blue->name == "dragon")warrior_blue->dragon_live(city_num, time_now, ptr_city_list);
            cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << warrior_blue->color << " " << warrior_blue->name
                 << " " << warrior_blue->id << " earned " << ptr_city_list[city_num].life_element << " elements for his headquarter" << endl;
            ptr_city_list[city_num].flag_change(time_now, city_num);
        }
        else if (warrior_red->life_value > 0 && warrior_blue->life_value > 0) {
            // 先记录战斗前的生命值
            int life_red = warrior_red->life_value, life_blue = warrior_blue->life_value;
            if (ptr_city_list[city_num].flag == 1 || (ptr_city_list[city_num].flag == 0 && city_num % 2 == 1)) {
                // 红方进攻，若蓝方存活则反击
                bool one_win = fight_against_second(city_num, time_now, warrior_red, warrior_blue, ptr_city_list, 1);
                if (one_win == false)fight_against_second(city_num, time_now, warrior_blue, warrior_red, ptr_city_list, -1);
            }
            else {
                // 蓝方进攻，若红方存活则反击
                bool one_win = fight_against_second(city_num, time_now, warrior_blue, warrior_red, ptr_city_list, 1);
                if (one_win == false)fight_against_second(city_num, time_now, warrior_red, warrior_blue, ptr_city_list, -1);
            }
            CWarrior* winner = NULL;
            CWarrior* loser = NULL;
            if (warrior_red->life_value > 0 && warrior_blue->life_value <= 0) {
                winner = warrior_red;
                loser = warrior_blue;
            }
            else if (warrior_blue->life_value > 0 && warrior_red->life_value <= 0) {
                winner = warrior_blue;
                loser = warrior_red;
            }
            else if (warrior_blue->life_value > 0 && warrior_red->life_value > 0) {
                // 平局，触发武士平局属性
                warrior_red->peace_fight();
                if (warrior_red->name == "dragon")warrior_red->dragon_live(city_num, time_now, ptr_city_list);
                warrior_blue->peace_fight();
                if (warrior_blue->name == "dragon")warrior_blue->dragon_live(city_num, time_now, ptr_city_list);
            }
            if (winner) {
                // 胜方为dragon，有可能触发其欢呼特性
                if (winner->name == "dragon")winner->dragon_live(city_num, time_now, ptr_city_list);
                // 若败方为lion，则触发其战死特性
                if (loser->name == "lion" && loser->color == "red")winner->life_value += life_red;
                else if (loser->name == "lion" && loser->color == "blue")winner->life_value += life_blue;
                cout << setw(3) << time_now / 60 << ":" << setw(2) << time_now % 60 << " " << winner->color << " " << winner->name
                     << " " << winner->id << " earned " << ptr_city_list[city_num].life_element << " elements for his headquarter" << endl;
            }
            // 刷新旗帜
            ptr_city_list[city_num].flag_change(time_now, city_num);

        }
    }
}

// 司令部对城市中战斗获胜的武士进行奖励,inspire_flag为1表示对红方武士进行奖赏，inspire_flag为-1表示对蓝方武士进行奖赏
void inspire_warrior(int city_num, CCity* ptr_city_list, CHeadquarter& red_quarter, CHeadquarter& blue_quarter, int inspire_flag) {
    CWarrior* warrior_red = ptr_city_list[city_num].warrior_red;
    CWarrior* warrior_blue = ptr_city_list[city_num].warrior_blue;
    if (inspire_flag == 1) {
        if (warrior_red != NULL && warrior_blue != NULL && warrior_red->life_value > 0 && warrior_blue->life_value <= 0) {
            // 红方司令部对红武士进行奖赏
            if (red_quarter.life_element >= HEADQUARTER_INSPIRE) {
                warrior_red->life_value += HEADQUARTER_INSPIRE;
                red_quarter.life_element -= HEADQUARTER_INSPIRE;
            }
        }
    }
    else if (inspire_flag == -1) {
        if (warrior_red != NULL && warrior_blue != NULL && warrior_blue->life_value > 0 && warrior_red->life_value <= 0) {
            if (blue_quarter.life_element >= HEADQUARTER_INSPIRE) {
                warrior_blue->life_value += HEADQUARTER_INSPIRE;
                blue_quarter.life_element -= HEADQUARTER_INSPIRE;
            }
        }
    }
    return;
}

// 清扫战场
void clean_city(int city_num, CCity* ptr_city_list) {
    CWarrior* warrior_red = ptr_city_list[city_num].warrior_red;
    CWarrior* warrior_blue = ptr_city_list[city_num].warrior_blue;
    if (warrior_red != NULL && warrior_red->life_value <= 0) {
        delete warrior_red;
        ptr_city_list[city_num].warrior_red = NULL;
    }
    if (warrior_blue != NULL && warrior_blue->life_value <= 0) {
        delete warrior_blue;
        ptr_city_list[city_num].warrior_blue = NULL;
    }
    return;
}

// 司令部从打了胜仗的城市回收生命元
void gain_life_element(int city_num, int time_now, CCity* ptr_city_list, CHeadquarter& red_quarter, CHeadquarter& blue_quarter) {
    CWarrior* warrior_red = ptr_city_list[city_num].warrior_red;
    CWarrior* warrior_blue = ptr_city_list[city_num].warrior_blue;
    CWarrior* warrior_take = NULL;
    int life_element = ptr_city_list[city_num].life_element;
    if (warrior_red != NULL && warrior_blue == NULL && life_element > 0) {
        red_quarter.life_element += life_element;
        ptr_city_list[city_num].life_element = 0;
    }
    else if (warrior_blue != NULL && warrior_red == NULL && life_element > 0) {
        blue_quarter.life_element += life_element;
        ptr_city_list[city_num].life_element = 0;
    }
    return;
}

// 终极版
void make_war(int case_num) {
    // 开始测试，接收输出，并初始化信息
    cin_data();
    // 输出测试样例组好
    cout << "Case " << case_num << ":" << endl;
    // 创建红蓝司令部和城市，将两方司令部也算作城市
    CHeadquarter red_quarter("red", LIFE_ELEMENT), blue_quarter("blue", LIFE_ELEMENT);
    CCity* ptr_city_list = new CCity[CITY_NUM + 2];
    int time_now = 0;
    cout << setfill('0');
    while (time_now <= TIME_NUM) {
        if (time_now % 60 == 0) {
            // 武士降生
            red_quarter.make_warrior(time_now, ptr_city_list);
            blue_quarter.make_warrior(time_now, ptr_city_list);
            time_now += 5;
            if (time_now > TIME_NUM)break;
        }
        if (time_now % 60 == 5) {
            // 忠诚度下降到0及以下的lion逃跑
            for (int i = 0; i < CITY_NUM + 2; ++i) {
                Lion_ran(i, time_now, ptr_city_list);
            }
            time_now += 5;
            if (time_now > TIME_NUM)break;
        }
        if (time_now % 60 == 10) {
            bool one_win = false;
            // 进军之前，先将所有城市中的红武士指针移动到辅助位置上
            for (int i = 0; i < CITY_NUM + 1; ++i) {
                ptr_city_list[i].warrior_red_tmp = ptr_city_list[i].warrior_red;
                ptr_city_list[i].warrior_red = NULL;
            }
            // 双方武士前进，注意触发iceman的前进属性
            for (int i = 0; i < CITY_NUM + 1; ++i) {
                int march_result = march_city(i, time_now, ptr_city_list, red_quarter, blue_quarter);
                if (march_result != 0)one_win = true;
            }
            // 确保和司令部占领同时发生的事情得到输出，因此不要在循环里面返回
            if (one_win)return;
            time_now += 10;
            if (time_now > TIME_NUM)break;
        }
        if (time_now % 60 == 20) {
            // 每个城市产出10个生命元，生命元留着城市，直到被武士取走
            for (int i = 1; i < CITY_NUM + 1; ++i) {
                ptr_city_list[i].life_element += 10;
            }
            time_now += 10;
            if (time_now > TIME_NUM)break;
        }
        if (time_now % 60 == 30) {
            // 若某个城市只有一个武士，则武士取走生命元传回司令部
            for (int i = 1; i < CITY_NUM + 1; ++i) {
                take_element(i, time_now, ptr_city_list, red_quarter, blue_quarter);
            }
            time_now += 5;
            if (time_now > TIME_NUM)break;
        }
        if (time_now % 60 == 35) {
            // 拥有arrow的武士放箭
            for (int i = 1; i < CITY_NUM; ++i) {
                shoot_arrow(i, time_now, ptr_city_list);
            }
            // 输出放箭的结果
            for (int i = 1; i < CITY_NUM + 1; ++i) {
                shoot_result(i, time_now, ptr_city_list);
            }
            time_now += 3;
            if (time_now > TIME_NUM)break;
        }
        if (time_now % 60 == 38) {
            // 评估拥有bomb的武士是否会使用bomb
            for (int i = 1; i < CITY_NUM + 1; ++i) {
                throw_bomb(i, time_now, ptr_city_list);
            }
            time_now += 2;
            if (time_now > TIME_NUM)break;
        }
        if (time_now % 60 == 40) {
            // 在有两个武士的城市，会发生战斗
            for (int i = 1; i < CITY_NUM + 1; ++i) {
                fight_against(i, time_now, ptr_city_list);
            }
            // 红方司令部对获胜的武士进行奖励
            for (int i = CITY_NUM; i >= 1; --i) {
                inspire_warrior(i, ptr_city_list, red_quarter, blue_quarter, 1);
            }
            // 蓝方司令部对获胜的武士进行奖赏
            for (int i = 1; i < CITY_NUM + 1; ++i) {
                inspire_warrior(i, ptr_city_list, red_quarter, blue_quarter, -1);
            }
            // 清扫战场
            for (int i = 1; i < CITY_NUM + 1; ++i) {
                clean_city(i, ptr_city_list);
            }
            // 双方司令部实际获取各个城市的生命元，信息也在奖赏前输出
            for (int i = 1; i < CITY_NUM + 1; ++i) {
                gain_life_element(i, time_now, ptr_city_list, red_quarter, blue_quarter);
            }
            time_now += 10;
            if (time_now > TIME_NUM)break;
        }
        if (time_now % 60 == 50) {
            // 司令部报告它拥有的武器情况
            red_quarter.print_life_element_info(time_now);
            blue_quarter.print_life_element_info(time_now);
            time_now += 5;
            if (time_now > TIME_NUM)break;
        }
        if (time_now % 60 == 55) {
            // 每个武士报告其拥有的武器情况（到达敌方司令部的武士也要报告）
            for (int i = 0; i < CITY_NUM + 2; ++i) {
                if (ptr_city_list[i].warrior_red != NULL)ptr_city_list[i].warrior_red->print_wepon_info(time_now);
            }
            for (int i = 0; i < CITY_NUM + 2; ++i) {
                if (ptr_city_list[i].warrior_blue != NULL)ptr_city_list[i].warrior_blue->print_wepon_info(time_now);
            }
            time_now += 5;
            if (time_now > TIME_NUM)break;
        }
    }
    delete[]ptr_city_list;
    return;
}

int main() {
    initializeWeaponUseTime();
    // 接收测试样例数
    int case_total, case_num = 0;
    cin >> case_total;
    while (case_num != case_total) {
        ++case_num;
        make_war(case_num);
    }
    return 0;
}