#include <iostream>
#include <random>
#include <vector>

// Function to simulate the birthday problem
bool has_duplicate_birthday(int n, std::mt19937 &gen, std::uniform_int_distribution<> &dist) {
    // Boolean array to mark birthdays (index from 1 to 365)
    std::vector<bool> birthdays(365, false);

    // Generate random birthdays and check for duplicates
    for (int i = 0; i < n; ++i) {
        int birthday = dist(gen);
        if (birthdays[birthday]) { // If this birthday has already occurred
            return true; // Duplicate found
        }
        birthdays[birthday] = true; // Mark this birthday as taken
    }
    return false; // No duplicate found
}

int main() {
    const int total_simulations = 1000000;
    int n;
    int matches = 0;

    // Ask for the number of people in the group
    std::cout << "Enter the number of people in the group: " << std::flush;
    std::cin >> n;
    // 获取起始时间
    auto start = std::chrono::high_resolution_clock::now();

    // If more than 366 people, we are guaranteed a match
    if (n > 366) {
        matches = total_simulations;
    } else {
        // Initialize random number generator and distribution (1-364 inclusive)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 364); // Days from 0 to 364

        // Run the simulation `total_simulations` times
        for (int i = 0; i < total_simulations; ++i) {
            if (has_duplicate_birthday(n, gen, dist)) {
                ++matches;
            }
        }
    }
    // 获取结束时间
    auto end = std::chrono::high_resolution_clock::now();

    // 计算持续时间，单位为毫秒
    std::chrono::duration<double, std::milli> duration_ms = end - start;

    // 输出运行时间
    std::cout << "The code took " << duration_ms.count() << " ms to run." << std::endl;
    // Output the empirical probability
    std::cout << "The probability of a birthday match is " << static_cast<double>(matches) / total_simulations << "\n\n" << std::flush;

    return 0;
}
