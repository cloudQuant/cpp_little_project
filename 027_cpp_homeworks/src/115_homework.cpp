// FREEZE CODE BEGIN
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
// FREEZE CODE END
struct Item {
  Item(double weight, double value) : weight(weight), value(value) {}
  double weight;
  double value;

};
// WRITE YOUR CODE HERE
double maximizeValue(std::vector<Item> items, double capacity){
    std::sort(items.begin(), items.end(), [](Item a, Item b){return a.value/a.weight>=b.value/b.weight;});
    double total_value = 0.0;
    for (auto i : items) {
      if (capacity > 0){
        if (capacity >= i.weight){
          capacity -= i.weight;
          total_value += i.value;
        }
        else{
          capacity = 0;
          total_value+= i.value * capacity/ i.weight;
        }
      }else{

      }
    }
    return total_value;
}




// FREEZE CODE BEGIN
std::vector<Item> parseItems(char* argv[], int argc) {
    std::vector<Item> items;

    for (int i = 1; i < argc - 1; i += 2) {
        double weight = std::stod(argv[i]);
        double value = std::stod(argv[i + 1]);
        items.emplace_back(Item(weight, value));
    }

    return items;
}

int main(int argc, char* argv[]) {
    int testCase = std::stoi(argv[1]);
    std::vector<Item> items = parseItems(argv, argc);

    double result = maximizeValue(items, 50);
    std::cout << "Total value: " << result << std::endl;

    return 0;
}
// FREEZE CODE END