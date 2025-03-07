// FREEZE CODE BEGIN
#include <iostream>
// FREEZE CODE END

// WRITE YOUR CODE HERE
int evenOrOdd(int arr[], int size, int target){
  for(int i = 0; i < size; i+=2){
    if(arr[i] == target){
      return i;
    }
  }
  for (int i=1; i < size; i+=2){
    if(arr[i] == target){
      return i;
    }
  }
  return -1;
}




// FREEZE CODE BEGIN
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./program <target>" << std::endl;
        return 1;
    }

    int target;
    std::sscanf(argv[1], "%d", &target);

    int arr[] = {20, -45, 7, 3325, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = evenOrOdd(arr, size, target);

    if (result != -1) {
        std::cout << "The target " << target << " was found at index: " << result << std::endl;
    } else {
        std::cout << "The target " << target << " was not found in the array." << std::endl;
    }

    return 0;
}
// FREEZE CODE END