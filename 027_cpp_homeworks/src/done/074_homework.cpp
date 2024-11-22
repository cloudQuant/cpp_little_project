#include <iostream>
#include <iterator>
#include <set>
using namespace std;
int main() {
    int a[] = {8,7,8,9,6,2,1};
    // 在此处补充你的代码
    std::set<int> v;
    for (int i=0; i<sizeof(a)/sizeof(a[0]); ++i){
        v.insert(a[i]);
    }
    ostream_iterator<int> o(cout," ");
    copy( v.begin(),v.end(),o);
    return 0;
}