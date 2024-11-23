//#include <iostream>
//#include <map>
//using namespace std;
// 在此处补充你的代码
class A {
public:
    static int count; // 静态计数器
    int value;

    A() : value(0) {
        count++; // 每次构造时增加计数
    }
    A(int a) : value(a) {
        count++;
    }
    A(const A& other) : value(other.value) {
        count++; // 拷贝构造函数增加计数
    }
    virtual ~A() {
        std::cout << "A::destructor" << std::endl;
        count--; // 析构时减少计数
    }
};

class B : public A {
public:
    B() : A() {}
    B(int b) : A(b) {}
    B(const B& other) : A(other) {} // 调用基类的拷贝构造函数
    virtual ~B() {
        std::cout << "B::destructor" << std::endl;
        //count--; // 析构时减少计数
    }
};

//int A::count = 0;
//void func(B b) { }
//int main()
//{
//    A a1(5),a2;
//    cout << A::count << endl;
//    B b1(4);
//    cout << A::count << endl;
//    func(b1);
//    cout << A::count << endl;
//    A * pa = new B(4);
//    cout << A::count << endl;
//    delete pa;
//    cout << A::count << endl;
//    //std::cout << " ------------- " << std::endl;
//    return 0;
//}