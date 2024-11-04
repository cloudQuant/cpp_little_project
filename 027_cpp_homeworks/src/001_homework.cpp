#include <iostream>

int cal_apple_worms(){
    int n = 0; // 苹果总数
    int x = 0; // 虫子x小时吃一个苹果
    int y = 0; // 经过y小时
    std::cin >> n >> x >> y;
    int eat_num = 1.0*y/x;
    if (n < eat_num){
        std::cout << 0 << std::endl;
        return 0;
    }
    else{
        int result = static_cast<int>((n - 1.0*y/x));
        std::cout << result << std::endl;
        return result;
    }

}

int main(){
    cal_apple_worms();
    return 0;
}