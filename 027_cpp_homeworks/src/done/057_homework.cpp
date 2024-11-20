#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
// 在此处补充你的代码
    Complex & operator=(const char * ch ){
        char buffer[20];
        strncpy(buffer, ch, sizeof(buffer));
        buffer[sizeof(buffer) - 1] = '\0';  // 确保字符串以 null 结尾

        // 查找加号位置
        char* plusPos = strchr(buffer, '+');
        if (plusPos == nullptr) {
            std::cerr << "Invalid format: missing '+' sign." << std::endl;
        }
        *plusPos = '\0';  // 将加号替换为 null 终止符

        // 提取实数部分
        double real = std::atof(buffer);

        // 查找虚数部分
        char* iPos = strchr(plusPos + 1, 'i');
        if (iPos == nullptr) {
            std::cerr << "Invalid format: missing 'i' sign." << std::endl;
        }
        *iPos = '\0';  // 将 'i' 替换为 null 终止符
        // 提取虚数部分
        double imag = std::atof(plusPos + 1);
        this->r = real;
        this->i = imag;
        return *this;
    }
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}