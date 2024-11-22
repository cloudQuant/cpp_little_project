#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class CArray3D {
private:
    T*** arr;    // 三维数组指针
    int a, b, c; // 三维数组的维度

    // 释放内存的统一函数
    void freeMemory() {
        if (arr) {
            for (int i = 0; i < a; ++i) {
                if (arr[i]) {
                    for (int j = 0; j < b; ++j) {
                        delete[] arr[i][j];
                    }
                    delete[] arr[i];
                }
            }
            delete[] arr;
            arr = nullptr; // 防止悬挂指针
        }
    }

public:
    // 构造函数
    CArray3D(int a, int b, int c) : arr(nullptr), a(a), b(b), c(c) {
        if (a <= 0 || b <= 0 || c <= 0)
            throw invalid_argument("Dimensions must be positive");

        arr = new T**[a];
        for (int i = 0; i < a; ++i) {
            arr[i] = nullptr; // 初始化为 nullptr 防止部分分配
            try {
                arr[i] = new T*[b];
                for (int j = 0; j < b; ++j) {
                    arr[i][j] = nullptr; // 初始化为 nullptr 防止部分分配
                    arr[i][j] = new T[c];
                }
            } catch (...) {
                freeMemory(); // 出现异常时释放已分配的资源
                throw;        // 重新抛出异常
            }
        }
    }

    // 重载下标操作符，返回二维数组的引用
    T** operator[](int i) {
        if (i < 0 || i >= this->a)
            throw out_of_range("First dimension index out of bounds");
        return this->arr[i];
    }

    // 禁止复制操作，避免资源管理问题
    CArray3D(const CArray3D&) { throw invalid_argument("Copy constructor not allowed"); }
    CArray3D& operator=(const CArray3D&) { throw invalid_argument("Assignment operator not allowed"); }

    // 析构函数，释放内存
    ~CArray3D() {
        freeMemory(); // 使用统一的释放函数
    }
};


int main()
{
    CArray3D<int> a(3,4,5);
    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                cout << a[i][j][k] << ",";
    return 0;
}