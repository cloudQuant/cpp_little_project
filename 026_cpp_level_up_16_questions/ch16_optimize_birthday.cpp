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

// The Birthday Problem, main()
// Summary: This application simulates the birthday problem a large number of times to reveal the probability of a birthday match in a groupd of a given number of people.
int main(){
    const int total = 1000000;
    int n, matches;
    std::cout << "Enter the number of people in the group: " << std::flush;
    std::cin >> n;
    // 获取起始时间
    auto start = std::chrono::high_resolution_clock::now();
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> month_dist(1, 365);
    if(n > 366)
        matches = total;
    else{
        // Write your code here
        matches = 0;
        for (int j = 0; j < total; ++j){
            std::set<int> month_day_set;
            for (int i=0; i<n; ++i){
                int num = month_dist(gen);
                month_day_set.insert(num);
            }
            int num = n - month_day_set.size()?1:0;
            matches += num;
            // std::cout << "j = " << j << " matches = " << matches << std::endl;
        }
    }
    // 获取结束时间
    auto end = std::chrono::high_resolution_clock::now();

    // 计算持续时间，单位为毫秒
    std::chrono::duration<double, std::milli> duration_ms = end - start;

    // 输出运行时间
    std::cout << "The code took " << duration_ms.count() << " ms to run." << std::endl;
    std::cout << "The probability of a birthday match is " << (double)matches/total << "\n\n" << std::flush;

    return 0;
}