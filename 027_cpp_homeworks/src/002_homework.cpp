#include <iostream>
#include <cmath>
static const double pi = M_PI;

int cal_elephant_drink_water(){
    int r = 0;
    int h = 0;
    std::cin >> h >> r;
    double v = pi * r * r * h;
    int result = std::ceil(20000/v);
    std::cout << result << std::endl;
    return result;
}

int main(){
    cal_elephant_drink_water();
    return 0;
}