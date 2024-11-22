#include<iostream>
using namespace std;
class Number {
public:
    int num;
    Number(int n=0): num(n) {}
    // 在此处补充你的代码
    Number & operator*(Number & n1){
        this->num = this->num * n1.num;
        return *this;
       }
    void operator=(Number & n1){
      this->num = n1.num;
    }
    operator int() const {
        return this->num;
    }

};


int main() {
    Number n1(10), n2(20);
    Number n3;n3 = n1*n2;
    cout << int(n3) << endl;
    cout << n1.num<< std::endl;
    return 0;
}