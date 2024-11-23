//#include <iostream>
//#include <set>
//#include <iterator>
//#include <algorithm>
//using namespace std;
//// 在此处补充你的代码
//class A{
//private:
//    int age;
//public:
//    A(int age):age(age){};
//    virtual int get_age(){
//        return this->age;
//    }
//    virtual int get_name(){
//        return 1;
//    }
//};
//
//class B: public A{
//private:
//    int age1;
//public:
//    B(int age):A(age){this->age1 = age;};
//    int get_age(){
//        return this->age1;
//    }
//    int get_name(){
//        return 2;
//    }
//};
//
//void Print(A * a){
//    cout << (a->get_name()==1?"A":"B") << " " << a->get_age() << std::endl;
//}
//
//class Comp{
//public:
//    Comp(){};
//    bool operator()(A * a1, A * a2){
//        return a1->get_age() < a2->get_age();
//    }
//};
//int main()
//{
//
//    int t;
//    cin >> t;
//    set<A*,Comp> ct;
//    while( t -- ) {
//        int n;
//        cin >> n;
//        ct.clear();
//        for( int i = 0;i < n; ++i)	{
//            char c; int k;
//            cin >> c >> k;
//
//            if( c == 'A')
//                ct.insert(new A(k));
//            else
//                ct.insert(new B(k));
//        }
//        for_each(ct.begin(),ct.end(),Print);
//        cout << "****" << endl;
//    }
//}

#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;

// 基类 A
class A {
private:
    int age;
public:
    A(int age) : age(age) {}
    virtual ~A() {} // 虚析构函数，确保子类对象正确销毁
    virtual int get_age() const { return age; }
    virtual int get_name() const { return 1; } // 返回 1 表示类型 A
};

// 派生类 B
class B : public A {
private:
    int age1;
public:
    B(int age) : A(age), age1(age) {}
    virtual int get_age() const { return age1; }
    virtual int get_name() const { return 2; } // 返回 2 表示类型 B
};

// 打印函数
void Print(const A* a) {
    cout << (a->get_name() == 1 ? "A" : "B") << " " << a->get_age() << endl;
}

// 比较器类，用于 set 排序
class Comp {
public:
    bool operator()(const A* a1, const A* a2) const {
        return a1->get_age() < a2->get_age();
    }
};

int main() {
    int t;
    cin >> t;
    set<A*, Comp> ct; // 定义存储指针的 set 容器
    while (t--) {
        int n;
        cin >> n;

        // 清除上次的数据，并释放内存
        for (set<A*, Comp>::iterator it = ct.begin(); it != ct.end(); ++it) {
            delete *it; // 释放动态分配的对象
        }
        ct.clear(); // 清空 set 容器

        // 输入并创建对象
        for (int i = 0; i < n; ++i) {
            char c;
            int k;
            cin >> c >> k;

            if (c == 'A') {
                ct.insert(new A(k));
            } else {
                ct.insert(new B(k));
            }
        }

        // 打印容器中的元素
        for_each(ct.begin(), ct.end(), Print);
        cout << "****" << endl;
    }

    // 释放最后一轮动态分配的对象
    for (set<A*, Comp>::iterator it = ct.begin(); it != ct.end(); ++it) {
        delete *it;
    }

    return 0;
}