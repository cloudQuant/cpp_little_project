/*
 * 描述
脱氧核糖核酸（DNA）由两条互补的碱基链以双螺旋的方式结合而成。而构成DNA的碱基共有4种，
 分别为腺瞟呤（A）、鸟嘌呤（G）、胸腺嘧啶（T）和胞嘧啶（C）。我们知道，在两条互补碱基链的对应位置上，
 腺瞟呤总是和胸腺嘧啶配对，鸟嘌呤总是和胞嘧啶配对。
 你的任务就是根据一条单链上的碱基序列，给出对应的互补链上的碱基序列。

输入
第一行是一个正整数n，表明共有n条要求解的碱基链。

以下共有n行，每行用一个字符串表示一条碱基链。这个字符串只含有大写字母A、T、G、C，分别表示腺瞟呤、胸腺嘧啶、鸟嘌呤和胞嘧啶。每条碱基链的长度都不超过255。

输出
共有n行，每行为一个只含有大写字母A、T、G、C的字符串。分别为与输入的各碱基链互补的碱基链。
 */

//#include <iostream>
//#include <cstring>
//
//// 获取互补碱基
//char get_complementary_base(char base) {
//    if (base == 'A') {
//        return 'T';
//    } else if (base == 'T') {
//        return 'A';
//    } else if (base == 'G') {
//        return 'C';
//    } else if (base == 'C') {
//        return 'G';
//    } else {
//        return 'X'; // 无效碱基的默认返回值
//    }
//}
//
//int main() {
//    int n;
//    std::cin >> n;
//    std::cin.ignore(); // 忽略换行符，避免影响后续输入
//
//    char dna[255]; // 保存输入的 DNA 序列
//
//    // 读取 n 行 DNA 序列
//    for (int i = 0; i < n; ++i) {
//        std::cin.getline(dna, 255); // 读取一行 DNA 序列
//
//        // 计算并输出互补序列
//        int len = std::strlen(dna);
//        for (int j = 0; j < len; ++j) {
//            std::cout << get_complementary_base(dna[j]);
//        }
//        std::cout << std::endl;
//    }
//
//    return 0;
//}
#include <iostream>
#include <string>

char get_complementary_base(char base) {
    if (base == 'A') {
        return 'T';
    } else if (base == 'T') {
        return 'A';
    } else if (base == 'G') {
        return 'C';
    } else if (base == 'C') {
        return 'G';
    } else {
        return 'X';  // 如果输入的不是 A、T、G、C，返回 'X'
    }
}

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();  // 忽略换行符

    for (int i = 0; i < n; ++i) {
        std::string dna;
        std::getline(std::cin, dna);

        std::string complementary_dna;
        for (std::string::iterator it = dna.begin(); it != dna.end(); ++it) {
            complementary_dna += get_complementary_base(*it);
        }

        std::cout << complementary_dna << std::endl;
    }

    return 0;
}