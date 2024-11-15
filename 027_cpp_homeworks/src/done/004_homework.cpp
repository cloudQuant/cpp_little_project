#include <iostream>
#include <cmath>

int max_odd_min_even_diff(){
    int max_odd=0;
    int min_even=100;
    int num=0;
    for (int i=0;i<6;++i){
        std::cin>>num;
        if (num%2==1){
            if (num>max_odd){
                max_odd=num;
            }
        }else{
            if (num<min_even){
                min_even=num;
            }
        }
    }
    std::cout << std::abs(max_odd-min_even) << std::endl;
    return std::abs(max_odd-min_even);
}

int main(){
    max_odd_min_even_diff();
    return 0;
}