//#include <iostream>
//#include <string>
//#include <map>
//#include <iterator>
//#include <algorithm>
//using namespace std;

// 自定义多重映射类 MyMultimap
template <typename KeyType, typename ValueType, typename Compare = greater<KeyType> >
class MyMultimap {
public:
    // 使用 std::multimap 来存储数据
    typedef multimap<KeyType, ValueType, Compare> MapType;
    typedef typename MapType::iterator iterator;
    typedef typename MapType::const_iterator const_iterator;

    // 插入键值对
    void insert(const pair<KeyType, ValueType>& p) {
        mp.insert(p);  // 直接插入
    }

    // 查找特定的键，返回所有相同键的第一个元素
    iterator find(const KeyType& key) {
        return mp.find(key);  // 返回第一次出现该键的迭代器
    }

    // 获取整个集合的开始迭代器
    iterator begin() {
        return mp.begin();
    }

    // 获取整个集合的结束迭代器
    iterator end() {
        return mp.end();
    }

    // 清空容器
    void clear() {
        mp.clear();
    }

    // Set 方法：将指定的 key 对应的所有值修改
    void Set(const KeyType& key, const ValueType& newValue) {
        // 遍历所有元素，找到所有匹配的键并修改其值
        for (iterator it = mp.begin(); it != mp.end(); ++it) {
            if (it->first == key) {
                it->second = newValue;
            }
        }
    }

    // 检查是否存在相同的键
    bool exists(const KeyType& key) {
        return mp.find(key) != mp.end();  // 查找是否有该键
    }

private:
    MapType mp;
};
// 重载 operator<< 以便能够直接输出 pair 对象
template <typename KeyType, typename ValueType>
ostream& operator<<(ostream& os, const pair<KeyType, ValueType>& p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

//// 学生数据结构
//struct Student
//{
//    string name;
//    int score;
//};
//
//
//
//// 新的 Print 函数
//template <class T>
//void Print(T first, T last) {
//    for (; first != last; ++first)
//        cout << *first << ",";
//    cout << endl;
//}
//
//int main()
//{
//
//    Student s[] = { {"Tom",80},{"Jack",70},
//                    {"Jone",90},{"Tom",70},{"Alice",100} };
//    MyMultimap<string,int> mp;
//    for(int i = 0; i<5; ++ i)
//        mp.insert(make_pair(s[i].name,s[i].score));
//    Print(mp.begin(),mp.end()); //按姓名从大到小输出
//
//    mp.Set("Tom",78); //把所有名为"Tom"的学生的成绩都设置为78
//    Print(mp.begin(),mp.end());
//
//
//    MyMultimap<int,string,less<int> > mp2;
//    for(int i = 0; i<5; ++ i)
//        mp2.insert(make_pair(s[i].score,s[i].name));
//
//    Print(mp2.begin(),mp2.end()); //按成绩从小到大输出
//    mp2.Set(70,"Error");          //把所有成绩为70的学生，名字都改为"Error"
//    Print(mp2.begin(),mp2.end());
//    cout << "******" << endl;
//
//    mp.clear();
//
//    string name;
//    string cmd;
//    int score;
//    while(cin >> cmd ) {
//        if( cmd == "A") {
//            cin >> name >> score;
//            if(mp.find(name) != mp.end() ) {
//                cout << "erroe" << endl;
//            }
//            mp.insert(make_pair(name,score));
//        }
//        else if(cmd == "Q") {
//            cin >> name;
//            MyMultimap<string,int>::iterator p = mp.find(name);
//            if( p!= mp.end()) {
//                cout << p->second << endl;
//            }
//            else {
//                cout << "Not Found" << endl;
//            }
//        }
//    }
//    return 0;
//}
