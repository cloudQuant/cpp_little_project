/*
 * 注意： 总时间限制: 1000ms 内存限制: 65536kB

    描述
    在一个字符串中找出元音字母a,e,i,o,u出现的次数。

    输入
    输入一行字符串（字符串中可能有空格，请用cin.getline(s,counts)方法把一行字符串输入到字符数组s中，
    其中counts是s的最大长度，这道题里面可以直接写80。），字符串长度小于80个字符。

    输出
    输出一行，依次输出a,e,i,o,u在输入字符串中出现的次数，整数之间用空格分隔。
 */

#include <iostream>
#include <cstring>

int main(){
    char s[80];
    std::cin.getline(s,80);
    int a_num = 0, e_num = 0, i_num = 0, o_num = 0, u_num = 0;
    for(int i = 0; i < strlen(s); i++){
        // std::cout << s[i] << std::endl;
        if(s[i] == 'a' ) {a_num++;}
        else if(s[i] == 'e') {e_num++;}
        else if(s[i] == 'i' ) {i_num++;}
        else if(s[i] == 'o' ) {o_num++;}
        else if(s[i] == 'u' ) {u_num++;}
    }
    std::cout << a_num << " " << e_num << " " << i_num << " " << o_num << " " << u_num << std::endl;
    return 0;
}