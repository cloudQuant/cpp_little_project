//#include <iostream>
//#include <cstring>
//#include <cstdlib>
//using namespace std;
// 在此处补充你的代码
class MyString: public std::string{
public:
    std::string str;
    MyString(){};
    MyString(const std::string & s){
        this->str = s;
    }
    MyString(const MyString & s){
        this->str = s.str;
    }
    MyString(const char * s){
        this->str = s;
    }
    std::string operator()(int a, int b){
        std::string s1(this->str.substr(a,b));
        return s1;
    }
    char & operator[](int a){
        char &s = this->str[a];
        return s;
    }
    MyString operator+(MyString & ms){
        MyString s(this->str + ms.str);
        return s;
    }
    MyString operator+(const char * ch){
        std::string s1(ch);
        MyString s(this->str + s1);
        return s;
    }
    friend MyString operator+(const char * ch, MyString & ms){
        std::string s1(ch);
        MyString s(s1 + ms.str);
        return s;
    }
    MyString & operator+=(const char * ch){
        std::string s(ch);
        this->str += s;
        return *this;
    }
    bool operator>(MyString & ms){
        return (this->str > ms.str);
    }
    bool operator<(MyString & ms){
        return (this->str < ms.str);
    }
    bool operator==(MyString & ms){
        return (this->str == ms.str);
    }
    friend ostream & operator<<(ostream & o, MyString & ms){
        o << ms.str;
        return o;
    }

};
//int CompareString( const void * e1, const void * e2) {
//    MyString * s1 = (MyString * ) e1;
//    MyString * s2 = (MyString * ) e2;
//    if( *s1 < *s2 )     return -1;
//    else if( *s1 == *s2 ) return 0;
//    else if( *s1 > *s2 ) return 1;
//    else {
//        return 0;
//    }
//}
//int main() {
//    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
//    MyString SArray[4] = {"big","me","about","take"};
//    cout << "1. " << s1 << s2 << s3<< s4<< endl;
//    s4 = s3;    s3 = s1 + s3;
//    cout << "2. " << s1 << endl;
//    cout << "3. " << s2 << endl;
//    cout << "4. " << s3 << endl;
//    cout << "5. " << s4 << endl;
//    cout << "6. " << s1[2] << endl;
//    s2 = s1;    s1 = "ijkl-";
//    s1[2] = 'A' ;
//    cout << "7. " << s2 << endl;
//    cout << "8. " << s1 << endl;
//    s1 += "mnop";
//    cout << "9. " << s1 << endl;
//    s4 = "qrst-" + s2;
//    cout << "10. " << s4 << endl;
//    s1 = s2 + s4 + " uvw " + "xyz";
//    cout << "11. " << s1 << endl;
//    qsort(SArray,4,sizeof(MyString), CompareString);
//    for( int i = 0;i < 4;++i )
//        cout << SArray[i] << endl;
//    //输出s1从下标0开始长度为4的子串
//    cout << s1(0,4) << endl;
//    //输出s1从下标为5开始长度为10的子串
//    cout << s1(5,10) << endl;
//    return 0;
//}