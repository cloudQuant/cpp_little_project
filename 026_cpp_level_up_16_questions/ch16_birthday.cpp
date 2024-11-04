// C++ Code Challenges, LinkedIn Learning

// Challenge #16: The Birthday Problem
// The birthday problem consists in finding the probability of having at least two people with the same birthday in a group of n people.
// Create an application that simulates the Birthday Problem 1 million times, with the number of people specified by the user.
// Use this application to prove (empirically) that the probability of having at least 2 people with the same birthday is approximately 0.5 for a group of 23 people. 
// https://en.wikipedia.org/wiki/Birthday_problem 

#include <iostream>
#include <chrono>
#include <iostream>
#include <random>
#include <set>

// Function to generate a random month
int generate_month() {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for the month (1 to 12)
    std::uniform_int_distribution<> month_dist(1, 12);
    return month_dist(gen);
}

// Function to generate a random day based on the given month
int generate_day(int month) {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for the day based on the month
    int days_in_month;
    if (month == 2) {
        days_in_month = 28; // Assume non-leap year for simplicity
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        days_in_month = 30;
    } else {
        days_in_month = 31;
    }
    std::uniform_int_distribution<> day_dist(1, days_in_month);
    return day_dist(gen);
}


// The Birthday Problem, main()
// Summary: This application simulates the birthday problem a large number of times to reveal the probability of a birthday match in a groupd of a given number of people.
int main(){    
    const int total = 1000000;
    int n, matches;
    std::cout << "Enter the number of people in the group: " << std::flush;
    std::cin >> n;
    // 获取起始时间
    auto start = std::chrono::high_resolution_clock::now();
    if(n > 366)
        matches = total;
    else{
        // Write your code here
        matches = 0;
        for (int j = 0; j < total; ++j){
            std::set<std::pair<int,int>> month_day_set;
            for (int i=0; i<n; ++i){
                int month = generate_month();
                // Generate a random day based on the generated month
                int day = generate_day(month);
                month_day_set.insert({month,day});
            }
            int num = n - month_day_set.size()?1:0;
            matches += num;
            //std::cout << "j = " << j << " matches = " << matches << std::endl;
        }
    }

    std::cout << "The probability of a birthday match is " << (double)matches/total << "\n\n" << std::flush;
    // 获取结束时间
    auto end = std::chrono::high_resolution_clock::now();

    // 计算持续时间，单位为毫秒
    std::chrono::duration<double, std::milli> duration_ms = end - start;

    // 输出运行时间
    std::cout << "The code took " << duration_ms.count() << " ms to run." << std::endl;

    return 0;
}
