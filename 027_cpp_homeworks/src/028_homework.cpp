/*
 * 描述
    给定一组点(x,y)，求距离最远的两个点之间的距离。

    输入
    第一行是点数n（n大于等于2）

    接着每一行代表一个点，由两个浮点数x y组成。

    输出
    输出一行是最远两点之间的距离。

    使用cout << fixed << setprecision(4) << dis << endl;输出距离值并精确到小数点后4位。

    fixed和setprecision是在<iomanip>头文件里定义的格式控制操作符，需要#include <iomanip>.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

int main(){
    int n;
    std::cin >> n;
    std::vector< std::pair<double, double> > points;
    double x1, y1, dis = 0;
    for(int i = 0; i < n; i++){
        std::cin >> x1 >> y1;
        points.push_back(std::make_pair(x1, y1));
    }
    // 计算距离
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            x1 = points[i].first - points[j].first;
            y1 = points[i].second - points[j].second;
            double d = std::sqrt(x1*x1 + y1*y1);
            if(d > dis){
                dis = d;
            }
        }
    }
    std::cout << std::fixed << std::setprecision(4) << dis << std::endl;
    return 0;
}

