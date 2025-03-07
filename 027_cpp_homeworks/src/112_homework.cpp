// FREEZE CODE BEGIN
#include <iostream>
#include <vector>
#include <string>
#include "Reader.h"
// FREEZE CODE END

// WRITE YOUR CODE HERE
int linearSearch(std::vector<std::string> &data, int i,  std::string target){
      int size = data.size();
      if (i==size){
            return -1;
      }
    if (data[i].find(target) != std::string::npos){
        return i;
    }
    return linearSearch(data, i+1, target);
};




// FREEZE CODE BEGIN
int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <path_to_csv> <target_element> <data_type>" << std::endl;
        return 1;
    }
    std::string path = argv[1];
    std::string target = argv[2];
    std::string type = argv[3];
    std::vector<std::string> data = Reader::parseCSV(path, type);

    int result = linearSearch(data, 0, target);
    if (result != -1) {
        std::cout << "Element " << target << " found at index: " << result << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    return 0;
}
// FREEZE CODE END