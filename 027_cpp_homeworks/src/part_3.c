//#include <iostream>
//using namespace std;
//class Base {
//public:
//    int k;
//    //Base(){};
//    Base(int n):k(n) { }
//};
//class Big  {
//public:
//    int v; Base b;
// 在此处补充你的代码
// 构造函数
    Big(int n) : v(n), b(n) { }

    // 复制构造函数
    Big(const Big &other) : v(other.v), b(other.b) { }
//};
//int main()  {
//    Big a1(5);    Big a2 = a1;
//    cout << a1.v << "," << a1.b.k << endl;
//    cout << a2.v << "," << a2.b.k << endl;
//    return 0;
//}