/*
 * 描述
给出两个正整数以及四则运算操作符（+ - * /），求运算结果。

输入
第一行：正整数a，长度不超过100

第二行：四则运算符o，o是“+”，“-”，“*”，“/”中的某一个

第三行：正整数b，长度不超过100

保证输入不含多余的空格或其它字符

输出
一行：表达式“a o b”的值。

补充说明：

1. 减法结果有可能为负数

2. 除法结果向下取整

3. 输出符合日常书写习惯，不能有多余的0、空格或其它字符
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

class LargeInt {
private:
    std::string numbers; // 存储绝对值部分
    bool is_negative;    // 是否是负数

    // 移除数字前导零
    static std::string removeLeadingZeros(const std::string &num) {
        size_t pos = num.find_first_not_of('0');
        return pos == std::string::npos ? "0" : num.substr(pos);
    }

    // 比较两个正整数的大小
    static int compare(const std::string &a, const std::string &b) {
        if (a.length() != b.length())
            return a.length() < b.length() ? -1 : 1;
        return a < b ? -1 : (a > b ? 1 : 0);
    }

    // 加法（两个正数字符串相加）
    static std::string addStrings(const std::string &a, const std::string &b) {
        int len1 = a.length(), len2 = b.length();
        int carry = 0, sum = 0;
        std::string result(std::max(len1, len2) + 1, '0'); // 预分配内存
        int k = result.length() - 1;

        for (int i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0 || carry > 0; --i, --j, --k) {
            int digitA = i >= 0 ? a[i] - '0' : 0;
            int digitB = j >= 0 ? b[j] - '0' : 0;
            sum = digitA + digitB + carry;
            carry = sum / 10;
            result[k] = (sum % 10) + '0';
        }
        return removeLeadingZeros(result);
    }

    // 减法（a >= b，两个正数字符串相减）
    static std::string subtractStrings(const std::string &a, const std::string &b) {
        int len1 = a.length(), len2 = b.length();
        int borrow = 0, diff = 0;
        std::string result(len1, '0'); // 预分配内存
        int k = len1 - 1;

        for (int i = len1 - 1, j = len2 - 1; i >= 0; --i, --j, --k) {
            int digitA = a[i] - '0';
            int digitB = j >= 0 ? b[j] - '0' : 0;
            diff = digitA - digitB - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result[k] = diff + '0';
        }
        return removeLeadingZeros(result);
    }

    // 乘法（优化实现）
    static std::string multiplyStrings(const std::string &a, const std::string &b) {
        int len1 = a.length(), len2 = b.length();
        std::string result(len1 + len2, '0');

        for (int i = len1 - 1; i >= 0; --i) {
            int carry = 0;
            for (int j = len2 - 1; j >= 0; --j) {
                int temp = (a[i] - '0') * (b[j] - '0') + (result[i + j + 1] - '0') + carry;
                carry = temp / 10;
                result[i + j + 1] = (temp % 10) + '0';
            }
            result[i] += carry;
        }
        return removeLeadingZeros(result);
    }

    // 除法（二分法实现）
    static std::string divideStrings(const std::string &a, const std::string &b) {
        if (b == "0") throw std::invalid_argument("Division by zero");
        if (compare(a, b) < 0) return "0";

        std::string result, remainder = "0";
        for (size_t i = 0; i < a.size(); ++i) {
            remainder += a[i];
            remainder = removeLeadingZeros(remainder);
            int quotient = 0;

            while (compare(remainder, b) >= 0) {
                remainder = subtractStrings(remainder, b);
                ++quotient;
            }
            result += (quotient + '0');
        }
        return removeLeadingZeros(result);
    }

public:
    LargeInt() : numbers("0"), is_negative(false) {}

    LargeInt(const std::string &str) {
        if (str[0] == '-') {
            is_negative = true;
            numbers = removeLeadingZeros(str.substr(1));
        } else if (str[0] == '+') {
            is_negative = false;
            numbers = removeLeadingZeros(str.substr(1));
        } else {
            is_negative = false;
            numbers = removeLeadingZeros(str);
        }

        // 如果值为 0，则确保是正数
        if (numbers == "0") is_negative = false;
    }

    // 加法
    LargeInt operator+(const LargeInt &b) const {
        if (is_negative == b.is_negative) {
            return LargeInt((is_negative ? "-" : "") + addStrings(numbers, b.numbers));
        } else if (compare(numbers, b.numbers) >= 0) {
            return LargeInt((is_negative ? "-" : "") + subtractStrings(numbers, b.numbers));
        } else {
            return LargeInt((b.is_negative ? "-" : "") + subtractStrings(b.numbers, numbers));
        }
    }

    // 减法
    LargeInt operator-(const LargeInt &b) const {
        if (is_negative != b.is_negative) {
            return LargeInt((is_negative ? "-" : "") + addStrings(numbers, b.numbers));
        } else if (compare(numbers, b.numbers) >= 0) {
            return LargeInt((is_negative ? "-" : "") + subtractStrings(numbers, b.numbers));
        } else {
            return LargeInt((!is_negative ? "-" : "") + subtractStrings(b.numbers, numbers));
        }
    }

    // 乘法
    LargeInt operator*(const LargeInt &b) const {
        std::string result = multiplyStrings(numbers, b.numbers);
        bool result_negative = (is_negative != b.is_negative);
        return LargeInt((result_negative && result != "0" ? "-" : "") + result);
    }

    // 除法
    LargeInt operator/(const LargeInt &b) const {
        std::string result = divideStrings(numbers, b.numbers);
        bool result_negative = (is_negative != b.is_negative);
        return LargeInt((result_negative && result != "0" ? "-" : "") + result);
    }

    void print() const {
        if (is_negative && numbers != "0") std::cout << "-";
        std::cout << numbers << std::endl;
    }
};

int main() {
    std::string a_str, op, b_str;
    std::cin >> a_str >> op >> b_str;

    LargeInt a(a_str), b(b_str);
    try {
        if (op == "+") {
            (a + b).print();
        } else if (op == "-") {
            (a - b).print();
        } else if (op == "*") {
            (a * b).print();
        } else if (op == "/") {
            (a / b).print();
        } else {
            std::cerr << "Invalid operator" << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
