#include <chrono>
#include <iostream>
#include <iomanip>

// 定义 TimePoint 类型
typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> TimePoint;

// 获取当前时间点
TimePoint getCurrentTimePoint() {
    return TimePoint(std::chrono::system_clock::now());
}

// 将 TimePoint 转换为时间戳（纳秒）
long long timePointToTimestamp(const TimePoint& tp) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count();
}

// 从时间戳转换为 TimePoint
TimePoint timestampToTimePoint(uint64_t timestamp) {
    return TimePoint(std::chrono::nanoseconds(timestamp));
}

// 为 TimePoint 添加 cout 输出功能
std::ostream& operator<<(std::ostream& os, const TimePoint& tp) {
    // 将 TimePoint 转换为 std::chrono::system_clock 类型
    auto systemTimePoint = std::chrono::time_point_cast<std::chrono::seconds>(tp);
    std::time_t t = std::chrono::system_clock::to_time_t(systemTimePoint);

    os << std::put_time(std::gmtime(&t), "%Y-%m-%d %H:%M:%S");

    // 添加毫秒信息
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count() % 1000;
    os << "." << millis;

    return os;
}

int main() {
    // 获取当前时间点
    TimePoint now = getCurrentTimePoint();
    std::cout << "Current TimePoint obtained: " << now << std::endl;

    // 转换时间戳
    long long timestamp = timePointToTimestamp(now);
    std::cout << "Current TimePoint as nanoseconds timestamp: " << timestamp << std::endl;

    // 转换回 TimePoint
    TimePoint tp = timestampToTimePoint(timestamp);
    std::cout << "Converted TimePoint from timestamp: " << tp << std::endl;

    return 0;
}
