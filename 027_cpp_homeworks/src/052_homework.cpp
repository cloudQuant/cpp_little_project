/*
 * 注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在一个学生信息处理程序中，要求实现一个代表学生的类，并且所有成员变量都应该是私有的。

（注：评测系统无法自动判断变量是否私有。我们会在结束之后统一对作业进行检查，请同学们严格按照题目要求完成，否则可能会影响作业成绩。）

输入
姓名，年龄，学号，第一学年平均成绩，第二学年平均成绩，第三学年平均成绩，第四学年平均成绩。

其中姓名、学号为字符串，不含空格和逗号；年龄为正整数；成绩为非负整数。

各部分内容之间均用单个英文逗号","隔开，无多余空格。

输出
一行，按顺序输出：姓名，年龄，学号，四年平均成绩（向下取整）。

各部分内容之间均用单个英文逗号","隔开，无多余空格。

 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

class StudentInfo{
public:
    StudentInfo(){};
    StudentInfo(std::string line){
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // 检查切分结果
        if (tokens.size() != 7) {
            std::cerr << "Invalid input format" << std::endl;
        }
        // 提取各个字段
        this->name = tokens[0];
        this->age = std::stoi(tokens[1]);
        this->id = tokens[2];
        this->first_year_grade = std::stoi(tokens[3]);
        this->second_year_grade = std::stoi(tokens[4]);
        this->three_year_grade = std::stoi(tokens[5]);
        this->four_year_grade = std::stoi(tokens[6]);
    }
    StudentInfo(std::string name, int age, std::string id, double f, double s, double t, double four){
        this->name = name;
        this->age = age;
        this->id = id;
        this->first_year_grade = f;
        this->second_year_grade = s;
        this->three_year_grade = t;
        this->four_year_grade = four;
    }

    void print_info(){
        double avg_score = (first_year_grade+second_year_grade+three_year_grade+four_year_grade)/4;
        int floor_avg_score = std::floor(avg_score);
        std::cout << this->name << ","
                  << this->age << ","
                  << this->id << ","
                  << floor_avg_score
                  << std::endl;
    }
    void set_name(std::string name){
        this->name = name;
    }
    void set_age(int age){
        this->age = age;
    }
    void set_id(std::string id){
        this->id = id;
    }
    void set_first_year_grade(double grade){
        this->first_year_grade = grade;
    }
    void set_second_year_grade(double grade){
        this->second_year_grade = grade;
    }
    void set_three_year_grade(double grade){
        this->three_year_grade = grade;
    }
    void set_four_year_grade(double grade){
        this->four_year_grade = grade;
    }

    std::string get_name(){
        return this->name;
    }
    std::string get_id(){
        return this->id;
    }
    int get_age(){
        return this->age;
    }
    double get_first_year_grade(){
        return this->first_year_grade;
    }
    double get_second_year_grade(){
        return this->second_year_grade;
    }
    double get_three_year_grade(){
        return this->three_year_grade;
    }
    double get_four_year_grade(){
        return this->four_year_grade;
    }
private:
    std::string name;
    int age;
    std::string id;
    double first_year_grade;
    double second_year_grade;
    double three_year_grade;
    double four_year_grade;

};

int main(){
    std::string line;
    std::getline(std::cin, line);
    StudentInfo student_info(line);
    student_info.print_info();
}