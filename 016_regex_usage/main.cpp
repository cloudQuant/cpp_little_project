#include <iostream>
#include <regex>
#include <string>

int main() {
    // 使用 std::regex_match 检查字符串是否完全匹配正则表达式
    std::string input = "123-45-6789";
    std::regex pattern(R"(\d{3}-\d{2}-\d{4})"); // 匹配美国社会安全号码的模式

    if (std::regex_match(input, pattern)) {
        std::cout << "Input matches the pattern." << std::endl;
    } else {
        std::cout << "Input does not match the pattern." << std::endl;
    }

    // 使用 std::regex_search 搜索字符串中的匹配项
    std::string input1 = "Email: user@example.com, Phone: 123-456-7890";
    std::regex pattern1(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)"); // 匹配电子邮件地址的模式

    std::smatch match;
    if (std::regex_search(input1, match, pattern1)) {
        std::cout << "Found email: " << match.str() << std::endl;
    } else {
        std::cout << "No email found." << std::endl;
    }

    // 使用 std::regex_replace 替换字符串中的匹配项
    std::string input2 = "Hello, World! Hello, Universe!";
    std::regex pattern2("Hello");
    std::string replacement = "Hi";

    std::string result = std::regex_replace(input2, pattern2, replacement);
    std::cout << "Result: " << result << std::endl;

    //  使用 std::regex_iterator 遍历所有匹配项
    std::string input3 = "123-456-7890, 987-654-3210, 111-222-3333";
    std::regex pattern3(R"(\d{3}-\d{3}-\d{4})"); // 匹配电话号码的模式

    std::sregex_iterator begin(input3.begin(), input3.end(), pattern3);
    std::sregex_iterator end;

    for (std::sregex_iterator it = begin; it != end; ++it) {
        std::smatch match = *it;
        std::cout << "Found phone number: " << match.str() << std::endl;
    }

    // 匹配网址
    std::regex ex("^(.*:)//([A-Za-z0-9\\-\\.]+)(:[0-9]+)?(.*)$");
    std::cmatch what;
    std::string urlStr = "https://www.fstream.binance.com:9943//ws";
    if (std::regex_match(urlStr.c_str(), what, ex)) {
        std::cout << "Found url: " << what[1] << std::endl;
        std::string protocol = std::string(what[1].first, what[1].second);
        std::string host = std::string(what[2].first, what[2].second);
        std::string port = std::string(what[3].first, what[3].second);
        std::string target = std::string(what[4].first, what[4].second);
        std::cout << "Protocol: " << protocol << std::endl;
        std::cout << "Host: " << host << std::endl;
        std::cout << "Port: " << port << std::endl;
        std::cout << "Target: " << target << std::endl;
    }

    return 0;
}