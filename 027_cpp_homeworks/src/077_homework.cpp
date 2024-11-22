#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Point {
    int x;
    int y;
    Point(int x_,int y_):x(x_),y(y_) { }
};

bool operator < ( const Point & p1, const Point & p2)
{
    if( p1.y < p2.y )
        return true;
    else if( p1.y == p2.y )
        return p1.x < p2.x;
    else
        return false;
}

void print_vector(const vector<Point> &v){
    std::cout << " ---------------- " << std::endl;
    for (int i = 0; i<v.size(); ++i){
        const Point &p = v[i];
        std::cout << p.x << " " << p.y << std::endl;
    }
}
int main()
{
    int t;
    int x,y;
    cin >> t;
    vector<Point> v;
    while( t -- ) {
        cin >> x >> y;
        v.push_back(Point(x,y));
    }
    vector<Point>::iterator i,j;
    int nTotalNum = 0;
    // 在此处补充你的代码
    // 对点进行排序
    std::sort(v.begin(), v.end());
    // print_vector(v);
    for( i = v.begin(); i < v.end() - 1;i ++ )
        for(j = v.begin()+1; j < v.end() ; j++) {
            // std::cout << "raw i " << i->x << " " << i->y << " j " << j->x << " " << j->y << std::endl;
            if(binary_search(v.begin(),v.end(),Point( j->x, i->y)) &&
               binary_search(v.begin(),v.end(),Point( i->x, j->y)) &&
               i->x<j->x && i->y<j->y){
                // std::cout << "i " << i->x << " " << i->y << " j " << j->x << " " << j->y << std::endl;
                nTotalNum ++;
            }

        }
    cout << nTotalNum;
    return 0;
}