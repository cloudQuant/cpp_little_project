// FREEZE CODE BEGIN
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "CSVreader.h"

// FREEZE CODE END

// WRITE YOUR CODE HERE
std::vector<std::string> search(std::vector<std::string> &data, std::string &target){
  std::vector<std::string> results;
  for (auto & s: data){
        std::stringstream ss(s);
        std::string account_number;
        std::string first_name;
        std::string last_name;
        std::string money;
        while (std::getline(ss, account_number, ',') && std::getline(ss, first_name, ',')
               && std::getline(ss, last_name, ',') && std::getline(ss, money, ',')){
            if (first_name == target){
                results.push_back(s);
                // return s;
                // std::cout << "Account Details:"<<std::endl;
                // std::cout <<account_number << " " << first_name << " " << last_name << " " << money << std::endl;
            }

        }
    }
    return results;
}




// FREEZE CODE BEGIN
int main(int argc, char* argv[]) {
    std::string path = argv[1];
    std::string target = argv[2];
    std::vector<std::string> data = readCSV(path);
    std::vector<std::string> results = search(data, target);

    if (results.empty()) {
        std::cout << "No matching records found." << std::endl;
    } else {
        std::cout << "Matching Records:" << std::endl;
        for (const std::string& record : results) {
            std::istringstream iss(record);
            std::string token;

            while (std::getline(iss, token, ',')) {
                std::cout << token << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
// FREEZE CODE END