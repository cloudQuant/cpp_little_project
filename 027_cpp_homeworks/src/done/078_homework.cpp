#include <iostream>
#include <string>
using namespace std;
// 自定义输入流迭代器
template<class T>
class CMyistream_iterator {
private:
    istream& is;  // 输入流引用
    T value;      // 当前读取的值
    bool end;     // 标记流是否结束

public:
    // 构造函数
    CMyistream_iterator(istream& input) : is(input), end(false) {
        ++(*this); // 初始化读取第一个值
    }

    // 解引用操作符：返回当前值
    T operator*() const {
        return value;
    }

    // 前置++操作符：读取下一个值
    CMyistream_iterator& operator++() {
        if (!(is >> value)) {
            end = true; // 如果读取失败，标记流结束
        }
        return *this;
    }

    // 后置++操作符
    CMyistream_iterator operator++(int) {
        CMyistream_iterator temp = *this;
        ++(*this);
        return temp;
    }

    // 判断迭代器是否有效
    bool operator!=(const CMyistream_iterator& other) const {
        return end != other.end;
    }
};
int main()
{
    CMyistream_iterator<int> inputInt(cin);
    int n1,n2,n3;
    n1 = * inputInt; //读入 n1
    int tmp = * inputInt;
    cout << tmp << endl;
    inputInt ++;
    n2 = * inputInt; //读入 n2
    inputInt ++;
    n3 = * inputInt; //读入 n3
    cout << n1 << "," << n2<< "," << n3 << endl;
    CMyistream_iterator<string> inputStr(cin);
    string s1,s2;
    s1 = * inputStr;
    inputStr ++;
    s2 = * inputStr;
    cout << s1 << "," << s2 << endl;
    return 0;
}