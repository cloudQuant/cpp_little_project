#include <iostream>
#include <type_traits>

// 使用std::enable_if限制模板仅对整数类型启用
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type printIfIntegral(T value) {
    std::cout << "Integral value: " << value << std::endl;
}

// 重载：非整数类型会报编译错误
template <typename T>
typename std::enable_if<!std::is_integral<T>::value, void>::type printIfIntegral(T value) {
    std::cout << "Non-integral value: " << value << std::endl;
}

int main() {
    printIfIntegral(42);        // 调用整数版本
    printIfIntegral(3.14);      // 调用非整数版本
    printIfIntegral("Hello");   // 调用非整数版本
    return 0;
}