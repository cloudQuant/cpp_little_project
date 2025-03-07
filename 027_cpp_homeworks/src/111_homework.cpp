// FREEZE CODE BEGIN
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "CSVreader.h"

// Function to split a string based on a delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
// FREEZE CODE END

// WRITE YOUR CODE HERE
bool compare(const std::string& str1, const std::string& str2) {
  std::vector<std::string> v1 = split(str1, ',');
  std::vector<std::string> v2 = split(str2, ',');
 return v1[1] >  v2[1];
}
void sort(std::vector<std::string> &data){
  std::sort(data.begin(), data.end(), compare);
}




// FREEZE CODE BEGIN
int main(int argc, char* argv[]) {
    std::string path = argv[1];
    std::vector<std::string> data = readCSV(path);

    sort(data);

    // Print the first and last elements after sorting
    std::cout << data.front() << std::endl;
    std::cout << data.back() << std::endl;

    return 0;
}
// FREEZE CODE END