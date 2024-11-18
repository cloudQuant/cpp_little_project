#include <iostream>
using namespace std;
class A {
public:
    int val;
// 在此处补充你的代码
    A(){this->val=0;}
    int & GetObj(){
        int &v = this->val;
        return v;
      }
};
int main()  {
    A a;
    cout << a.val << endl;
    a.GetObj() = 5;
    cout << a.val << endl;
}