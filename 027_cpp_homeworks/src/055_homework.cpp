#include <iostream>
using namespace std;
class Base {
public:
    int k;
    Base(){};
    Base(int n):k(n) { }
};
class Big  {
public:
    int v; Base b;
// 在此处补充你的代码
    Big(int i){
      this->v = i;
      this->b = Base(i);
      }
    Big(const Big& b){
      this->v = b.v;
      this->b = b.b;
    }
};
int main()  {
    Big a1(5);    Big a2 = a1;
    cout << a1.v << "," << a1.b.k << endl;
    cout << a2.v << "," << a2.b.k << endl;
    return 0;
}