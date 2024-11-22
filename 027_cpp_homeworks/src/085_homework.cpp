//#include <iostream>
//using namespace std;
// 在此处补充你的代码
class CType{
  private:
    int num;
  public:
      CType(){}
      void setvalue(int n){
        this->num = n;
        }
      int operator++(int ){
        int temp = this->num;
        this->num = this->num * this->num;
        return temp;
      }
      friend ostream & operator<<(ostream & os, const CType & obj){
        os << obj.num;
        return os;
      }

};
//int main(int argc, char* argv[]) {
//    CType obj;
//    int n;
//    cin>>n;
//    while ( n ) {
//        obj.setvalue(n);
//        cout<<obj++<<" "<<obj<<endl;
//        cin>>n;
//    }
//    return 0;
//}