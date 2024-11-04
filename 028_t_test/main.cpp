#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

// Function to calculate the mean of a vector
double calculate_mean(const std::vector<int>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

// Function to calculate the sample standard deviation
double calculate_std(const std::vector<int>& data, double mean) {
    double sum = 0.0;
    for (int value : data) {
        sum += (value - mean) * (value - mean);
    }
    return std::sqrt(sum / (data.size() - 1));  // Sample standard deviation (ddof=1)
}

// Function to calculate the t-statistic
double calculate_t_statistic(double sample_mean, double population_mean, double sample_std, int sample_size) {
    return (sample_mean - population_mean) / (sample_std / std::sqrt(sample_size));
}

// Main function
int main() {
    // IQ scores data
    std::vector<int> iq_scores = {116, 111, 101, 120, 99, 94, 106, 115, 107, 101, 110, 92};
    double population_mean = 100.0;
    double alpha = 0.05;

    // Calculate sample mean and standard deviation
    double sample_mean = calculate_mean(iq_scores);
    double sample_std = calculate_std(iq_scores, sample_mean);
    int sample_size = iq_scores.size();

    // Calculate the t-statistic
    double t_statistic = calculate_t_statistic(sample_mean, population_mean, sample_std, sample_size);

    // Since we don't have a direct function for p-value, we can approximate it or use statistical tables
    // In this example, we will output the t-statistic and interpret manually
    std::cout << "Sample mean: " << sample_mean << std::endl;
    std::cout << "Sample standard deviation: " << sample_std << std::endl;
    std::cout << "T-statistic: " << t_statistic << std::endl;

    // Determine the conclusion based on the t-statistic and manually checking with a t-distribution table
    if (t_statistic > 1.796) { // Approximate critical t-value for one-tailed test, df=11, alpha=0.05
        std::cout << "Reject the null hypothesis: There is evidence that the mean IQ is greater than 100." << std::endl;
    } else {
        std::cout << "Fail to reject the null hypothesis: There is not enough evidence that the mean IQ is greater than 100." << std::endl;
    }

    return 0;
}