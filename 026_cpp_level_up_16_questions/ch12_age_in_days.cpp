// C++ Code Challenges, LinkedIn Learning

// Challenge #12: Age in Days Calculator
// Write an application that asks the user's birth date and responds with the user's age in days. 
// If the user claims to be over 120 years old, output a message calling the bluff.

#include <iostream>
#include <string>
#include <ctime>
#include <vector>

// Age in Days, main()
// Summary: This application asks the user's birth date and prints their age in days.
int main(){
    int birth_y, birth_m, birth_d, today_y, today_m, today_d, age;

    // 获取当前的日历时间
    time_t now = time(nullptr);

    // 将日历时间转换为本地时间的 tm 结构体
    tm* local_time = localtime(&now);

    std::cout << "Enter your birth date's month as a number: " << std::flush;
    std::cin >> birth_m;
    std::cout << "Enter your birth date's day: " << std::flush;
    std::cin >> birth_d;
    std::cout << "Enter your birth date's year: " << std::flush;
    std::cin >> birth_y;
    
    if(birth_m < 1)
        birth_m = 1;
    if(birth_m > 12)
        birth_m = 12;

    // Write your code here
    std::vector<int> month_day = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    today_y = local_time->tm_year+1900;
    today_m = local_time->tm_mon+1;
    today_d = local_time->tm_mday;
    age = 0;
    std::cout << "today = " << today_y << " " << today_m << " " << today_d;
    // 计算年份的时间
    for (int i = birth_y+1; i < today_y; ++i){
        if (i%400==0 || (i%4==0 && i%100!=0)){
            age+=366;
        }
        else{
            age+=365;
        }
    }
    // 计算月份
    bool birth_run = birth_y%400==0 || (birth_y%100!=0 && birth_y%4==0);
    for (int m = birth_m; m<=12;++m){
        if (m==2 && birth_run && birth_d!=29){age++;}
        age+=month_day[m];
    }
    age -= (birth_d-1);

    bool now_run = today_y%400==0 || (today_y%100!=0 && today_y%4==0);
    for (int m = 1; m<today_m;++m){
        if (m==2 && birth_run){age++;}
        age+=month_day[m];
    }
    age += today_d;

    if(age < 43830)
        std::cout << "You are " << age << " days old.";
    else
        std::cout << "Come on. You can't be " << age << " days old!";
    std::cout << "\n\n" << std::flush;
}
