#include <iconv.h>
#include <iostream>

int main() {
    iconv_t cd = iconv_open("UTF-8", "ASCII");
    if (cd == (iconv_t)-1) {
        std::cerr << "Failed to open iconv" << std::endl;
        return 1;
    }
    std::cout << "iconv opened successfully!" << std::endl;
    iconv_close(cd);
    return 0;
}