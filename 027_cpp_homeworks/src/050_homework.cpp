/*
 * 描述
在一个平面上，如果有两个点(x,y),(a,b),如果说(x,y)支配了(a,b)，这是指x>=a,y>=b;

用图形来看就是(a,b)坐落在以(x,y)为右上角的一个无限的区域内。

给定n个点的集合，一定存在若干个点，它们不会被集合中的任何一点所支配，这些点叫做极大值点。

编程找出所有的极大点，按照x坐标由小到大，输出极大点的坐标。

本题规定：n不超过100，并且不考虑点的坐标为负数的情况。

输入
输入包括两行，第一行是正整数n，表示是点数，第二行包含n个点的坐标，坐标值都是整数，
 坐标范围从0到100，输入数据中不存在坐标相同的点。

输出
按x轴坐标最小到大的顺序输出所有极大点。

输出格式为:(x1,y1),(x2,y2),...(xk,yk)

注意：输出的每个点之间有","分隔,最后一个点之后没有",",少输出和多输出都会被判错
 */

#include <iostream>
#include <vector>
#include <algorithm>

struct point{
    int x;
    int y;
};

bool compare(point p1, point p2 ){
    return p1.x < p2.x;
}

int main(){
     std::vector<point> content;
     int n=0;
     int x=0, y=0;
     // 获取有多少个数据，并保存到vector中
     std::cin >> n;
     for (int i=0;i<n;i++){
         std::cin >> x >> y;
         point p;
         p.x = x;
         p.y = y;
         content.push_back(p);
     }
     // 进行排序
     std::sort(content.begin(), content.end(), compare);
     bool first_point = true;
     // 计算是否是极大值点
     for (int i=0; i<n;++i){
         bool large_point = true;
         point p1 = content[i];
         for (int j=i+1; j < n; j++){
             point p2 = content[j];
             if (p1.y<p2.y){
                 large_point = false;
                 break;
             }
         }
         if (large_point){
             if (first_point){std::cout << "(" << p1.x << "," << p1.y << ")";first_point=false;}
             else{std::cout << ",(" << p1.x << "," << p1.y << ")";}

         }
     }
     return 0;

}