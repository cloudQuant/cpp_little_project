/*
 * 描述
输入一串长度不超过500个符号的字符串，输出在串中出现第2多的英语字母(大小写字母认为相同)和
 次数（如果串中有其它符号，则忽略不考虑）。如果有多个字母的次数都是第2多，
 则按串中字母出现的顺序输出第1个。

例 ab&dcAab&c9defgb

这里，a 和 b都出现3次，c和d都出现2次，e、f 和 g 各出现1次，
 其中的符号&和9均忽略不考虑。因此，出现第2多的应该是 c 和 d，
 但是 d 开始出现的位置在 c 的前面，因此，输出为

D+d:2

(假定在字符串中，次数第2多的字母总存在)

输入
一个字符串

输出
大写字母+小写字母: 个数

 需求分析：
 1. 需要把字符串转为小写或者大写
 2. 需要判断当前字符是否是字母
 3. 需要把出现的字符次数进行排序
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>

int main(){
    std::map<char, int> content;
    std::vector<char> ordered_char;
    char buffer[500];
    char ch;
    std::cin.getline(buffer, sizeof(buffer));
    // 读入所有的数据并保存到map中
    for (int i=0; i< 500; ++i){
        ch = buffer[i];
        if (ch == '\0'){
            //std::cout << " end for loop" << std::endl;
            break;
        }
        if (ch>='A' && ch <= 'Z'){
            ch+=32;
        }
        if (ch >= 'a' && ch <='z'){
            if (!content.count(ch)){
                ordered_char.push_back(ch);
            }
            content[ch]++;
        }
    }
    // 输出所有的map内容
    char maxKey = '\0', secondMaxKey = '\0';
    int maxValue = std::numeric_limits<int>::min();
    int secondMaxValue = std::numeric_limits<int>::min();

    // 遍历 map 找到最大值和第二大值
    for (int i=0; i<ordered_char.size(); i++) {
        char key = ordered_char[i];
        int value = content[key];
        std::cout << key << " " << value << std::endl;
        if (value > maxValue) {
            // 更新第二大值为原最大值
            secondMaxValue = maxValue;
            secondMaxKey = maxKey;
            // 更新最大值
            maxValue = value;
            maxKey = key;
        } else if (value > secondMaxValue && value < maxValue) {
            // 更新第二大值
            secondMaxValue = value;
            secondMaxKey = key;
        }
    }
    std::cout << secondMaxKey << secondMaxValue << std::endl;
    // 打印输出
    ch = static_cast<char>(secondMaxKey - 32);
    std::cout << ch << "+" << secondMaxKey << ":" << secondMaxValue << std::endl;
    return 0;
}

