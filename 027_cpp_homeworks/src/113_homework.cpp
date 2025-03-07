// FREEZE CODE BEGIN
#include <iostream>
#include <vector>
#include "Reader.h"
// FREEZE CODE END

// WRITE YOUR CODE HERE
int binarySearch(std::vector<int> &data, int begin, int end, int target){
  do {
    int mid = begin + (end - begin) / 2;
    if (data[mid] == target){
      return mid;
    }
    else if (data[mid] < target){
      begin = mid + 1;
    }else{
      end = mid;
    }
  } while (begin!=end);

  return -1;
}




// FREEZE CODE BEGIN
int main(int argc, char* argv[]) {
    // Check if the correct number of arguments are provided
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <index> <target>" << std::endl;
        return 1;
    }

    // Parse command line arguments
    std::string path = argv[1];    // File name
    int index = std::stoi(argv[2]); // Index of the array in the file
    int target = std::stoi(argv[3]); // Target element to search for

    // Parse the array from the file
    std::vector<int> data = Reader::parseIntArray(path, index);

    // Perform binary search on the array
    int result = binarySearch(data, 0, data.size() - 1, target);

    // Print the result
    if (result != -1) {
        std::cout << "Element " << target << " is located at index: " << result << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    return 0;
}
// FREEZE CODE END