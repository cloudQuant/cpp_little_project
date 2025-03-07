// FREEZE CODE BEGIN
#include "Reader.h"
#include <iostream>
#include <vector>
#include <algorithm>
// FREEZE CODE END

int minMoney(std::vector<int> moneyArr, int amount) {
    std::sort(moneyArr.begin(), moneyArr.end(), std::greater<int>()); // Sort in descending order
    int count = 0;
    for (int i = 0; i < moneyArr.size(); ++i) {
        if (amount == 0) break; // If amount is zero, we are done
        if (moneyArr[i] <= amount) {
            count += amount / moneyArr[i]; // Add the maximum number of this denomination
            amount %= moneyArr[i]; // Update the remaining amount
        }
    }
    return (amount == 0) ? count : -1; // Return -1 if amount cannot be made with given denominations
}




// FREEZE CODE BEGIN
int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <path> <index> <amount>" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    int index = std::stoi(argv[2]);
    int amount = std::stoi(argv[3]);

    std::vector<int> moneyArr = Reader::parseIntArray(path, index);

    int result = minMoney(moneyArr, amount);

    if (result != -1) {
        std::cout << "Minimum bills required: " << result << std::endl;
    } else {
        std::cout << "Cannot make exact change with given denominations" << std::endl;
    }

    return 0;
}
// FREEZE CODE END