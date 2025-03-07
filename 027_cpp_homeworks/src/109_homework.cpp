// FREEZE CODE BEGIN
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "CSVreader.h"
// FREEZE CODE END

// WRITE YOUR CODE HERE
std::string search(std::vector<std::string> &data, std::string &target){
    for (auto & s: data){
        std::stringstream ss(s);
        std::string account_number;
        std::string first_name;
        std::string last_name;
        std::string money;
        while (std::getline(ss, account_number, ',') && std::getline(ss, first_name, ',')
               && std::getline(ss, last_name, ',') && std::getline(ss, money, ',')){
            if (last_name == target){
                return s;
                // std::cout << "Account Details:"<<std::endl;
                // std::cout <<account_number << " " << first_name << " " << last_name << " " << money << std::endl;
            }

        }
    }
    return "";
}





// FREEZE CODE BEGIN
int main(int argc, char *argv[]) {
    std::string path = argv[1];
    std::string target = argv[2];

    std::vector<std::string> data = readCSV(path);
    std::string result = search(data, target);

    if (!result.empty()) {
        std::cout << "Account Details:" << std::endl;
        std::stringstream ss(result);
        std::string item;

        while (std::getline(ss, item, ',')) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "An account with " << target << " is not found." << std::endl;
    }

    return 0;
}


// FREEZE CODE END