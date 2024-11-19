#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
public:
    int *ptr;
    int row;
    int col;

    Array2() {
        this->ptr = nullptr;
        this->row = 0;
        this->col = 0;
    }

    Array2(int row, int col) {
        this->row = row;
        this->col = col;
        this->ptr = new int[row * col];
    }

    ~Array2() {
        if (ptr){delete[] ptr;}
    }

    int* operator[](int row) {
        if (this->ptr){return this->ptr + row * this->col;}
        else{return nullptr;}

    }

    int operator()(int row, int col) {
        return this->ptr[row * this->col + col];
    }

    Array2& operator=(const Array2& a2) {
        if (this == &a2) {
            return *this;
        }

        this->row = a2.row;
        this->col = a2.col;

        if (ptr) {
            delete[] ptr;
        }

        this->ptr = new int[this->row * this->col];
        memcpy(this->ptr, a2.ptr, sizeof(int) * this->row * this->col);

        return *this;
    }
};

int main() {
    Array2 a(3, 4);
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 4; ++j)
            a[i][j] = i * 4 + j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 4; ++j) {
            cout << a(i, j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;

    Array2 b;
    b = a;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 4; ++j) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }

    return 0;
}