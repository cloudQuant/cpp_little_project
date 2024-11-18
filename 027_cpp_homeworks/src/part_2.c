//#include <iostream>
//using namespace std;
//class Sample{
//public:
//    int v;
//    Sample(int n):v(n) { }
// 在此处补充你的代码
    // Copy constructor
    Sample(const Sample &other) : v(other.v+5) { }
//};
//int main() {
//    Sample a(5);
//    Sample b = a;
//    cout << b.v;
//    return 0;
//}