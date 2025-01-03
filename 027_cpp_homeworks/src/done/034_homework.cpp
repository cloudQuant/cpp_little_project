/*
 * 描述
甲壳虫的《A day in the life》和《Tomorrow never knows》脍炙人口，
 如果告诉你a day in the life,真的会是tomorrow never knows?
 相信学了计概之后这个不会是难题，现在就来实现吧。

读入一个格式为yyyy-mm-dd的日期（即年－月－日），输出这个日期下一天的日期。
 可以假定输入的日期不早于1600-01-01，也不晚于2999-12-30。

输入
输入仅一行，格式为yyyy-mm-dd的日期。

输出
输出也仅一行，格式为yyyy-mm-dd的日期

样例输入
1
2010-07-05
样例输出
1
2010-07-06
提示
闰年的标准：

(1)普通年能被4整除且不能被100整除的为闰年。（如2004年就是闰年,1901年不是闰年）

(2)世纪年能被400整除的是闰年。(如2000年是闰年，1100年不是闰年)

可以利用一个字符变量吃掉输入的短横线（减号），输出时请活用setfill和setw 控制符。
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void getNextDate(std::string date) {
    int year, month, day;
    char delimiter; // 用于吃掉输入的短横线
    std::istringstream iss(date);
    iss >> year >> delimiter >> month >> delimiter >> day;

    // 定义每个月的天数
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // 如果是闰年，二月有29天
    if (isLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    // 计算下一天的日期
    day++;
    if (day > daysInMonth[month - 1]) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    // 输出结果
    std::cout << std::setw(4) << std::setfill('0') << year << "-"
              << std::setw(2) << std::setfill('0') << month << "-"
              << std::setw(2) << std::setfill('0') << day << std::endl;
}

int main() {
    std::string date;
    std::cin >> date;
    getNextDate(date);
    return 0;
}