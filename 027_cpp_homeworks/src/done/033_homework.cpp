/*
 * 描述
有一个小型的报账系统，它有如下功能：

（1）统计每个人所报发票的总钱数

（2）统计每类发票的总钱数

将此系统简化为如下：假设发票类别共有A、B、C三种;
 一共有三个人，ID分别为1、2、3。

输入
系统输入包含三行，每行第一个数为人员ID（整型，1或2或3），
 第二个数为发票总张数(张数不超过100)，
 之后是多个发票类别（字符型，A或B或C）和相应发票金额（单进度浮点型,不超过1000.0）。

输出
输出包含六行，前三行为每人（按ID由小到大输出）所报发票总钱数（保留两位小数），
 后三行为每类发票的总钱数（保留两位小数）。
 */

#include <iostream>
#include <iomanip>

int main(){
    int user, invoice_count;
    double invoice_amount;
    char invoice_type;
    double total_amount = 0.0;
    double user_a_total_amount = 0.0, user_b_total_amount = 0.0, user_c_total_amount = 0.0;
    double a_total_amount = 0.0, b_total_amount = 0.0, c_total_amount = 0.0;
    for (int i = 0; i < 3; i++){
        std::cin >> user >> invoice_count;
        for (int j = 0; j < invoice_count; j++){
            std::cin >> invoice_type >> invoice_amount;
            if (invoice_type == 'A'){
                a_total_amount += invoice_amount;
                total_amount += invoice_amount;
            }
            else if (invoice_type == 'B'){
                b_total_amount += invoice_amount;
                total_amount += invoice_amount;
            }
            else if (invoice_type == 'C'){
                c_total_amount += invoice_amount;
                total_amount += invoice_amount;
            }
        }
        if (user == 1){
            user_a_total_amount = total_amount;
        }
        else if (user == 2){
            user_b_total_amount = total_amount;
        }
        else if (user == 3){
            user_c_total_amount = total_amount;
        }
        total_amount = 0.0;
    }
    std::cout << 1 << " " << std::fixed << std::setprecision(2) << user_a_total_amount << std::endl;
    std::cout << 2 << " " << std::fixed << std::setprecision(2) << user_b_total_amount << std::endl;
    std::cout << 3 << " " << std::fixed << std::setprecision(2) << user_c_total_amount << std::endl;
    std::cout << "A " << std::fixed << std::setprecision(2) << a_total_amount << std::endl;
    std::cout << "B " << std::fixed << std::setprecision(2) << b_total_amount << std::endl;
    std::cout << "C " << std::fixed << std::setprecision(2) << c_total_amount << std::endl;
    return 0;


}