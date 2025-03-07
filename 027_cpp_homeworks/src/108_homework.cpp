// FREEZE CODE BEGIN
#include <iostream>
// FREEZE CODE END

// WRITE YOUR CODE HERE
using namespace std;
#include <string>
int binarySearch(int array[], int size, int target) {
    int mid = -1;
    int left = 0;
    int right = size;

    while (left <= right) {

        mid = left + (right - left) / 2;
        //cout << "left = " << left << " right = " << right << " mid = " << mid << endl;
        if (array[mid] == target)
            break;

        if (array[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
        if (left == right){
            if (array[left] == target){
                mid = left;
                break;
            }else{
                mid = -1;
                break;
            }
        }
    }
    return mid;
}




// FREEZE CODE BEGIN
int main(int argc, char* argv[]) {
    int arr[] = {-2, 4, 6, 7, 9, 11}; // TEST ARRAY
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <target>" << std::endl;
        return 1;
    }
    int target = std::stoi(argv[1]);
    int result = binarySearch(arr, sizeof(arr) / sizeof(arr[0]), target);

    if(result != -1) {
        std::cout << "The target " << target << " was found at index: " << result << std::endl;
    } else {
        std::cout << "The target " << target << " was not found in the array." << std::endl;
    }
    return 0;
}
// FREEZE CODE END