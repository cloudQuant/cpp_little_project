#include <iostream>
#include <ctime>

int main() {
    // 获取当前的日历时间
    time_t now = time(nullptr);

    // 将日历时间转换为本地时间的 tm 结构体
    tm* local_time = localtime(&now);

    // 输出当前时间
    std::cout << "Current local time: " << asctime(local_time);

    // 格式化时间
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_time);
    std::cout << "Formatted time: " << buffer << std::endl;

    return 0;
}