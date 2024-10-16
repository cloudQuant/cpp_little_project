#include <iostream>
#include <string>
#include <chrono>

// is_leap_year()
// Summary: This function returns true if the argument is a leap year.
// Arguments:
//           year: The year to examine.
// Returns: A boolean value. True for leap years, false otherwise.
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// days_in_month()
// Summary: This function returns the number of days in a given month and year.
int days_in_month(int month, int year) {
    const int month_lengths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return month_lengths[month - 1];
}

// calculate_age_in_days()
// Summary: This function calculates the user's age in days based on the birth date and current date.
int calculate_age_in_days(int birth_y, int birth_m, int birth_d, int today_y, int today_m, int today_d) {
    std::tm birth_tm = {0};
    birth_tm.tm_year = birth_y - 1900;  // std::tm year starts from 1900
    birth_tm.tm_mon = birth_m - 1;      // std::tm month starts from 0
    birth_tm.tm_mday = birth_d;

    std::tm today_tm = {0};
    today_tm.tm_year = today_y - 1900;
    today_tm.tm_mon = today_m - 1;
    today_tm.tm_mday = today_d;

    auto birth_time = std::chrono::system_clock::from_time_t(std::mktime(&birth_tm));
    auto today_time = std::chrono::system_clock::from_time_t(std::mktime(&today_tm));

    auto age_duration = std::chrono::duration_cast<std::chrono::days>(today_time - birth_time);
    return age_duration.count();
}

// main()
// Summary: This application asks the user's birth date and prints their age in days.
int main() {
    int birth_y, birth_m, birth_d;

    // Input the birth date
    std::cout << "Enter your birth date's year: ";
    std::cin >> birth_y;
    std::cout << "Enter your birth date's month (1-12): ";
    std::cin >> birth_m;
    std::cout << "Enter your birth date's day: ";
    std::cin >> birth_d;

    // Validate the input for month and day
    if (birth_m < 1 || birth_m > 12 || birth_d < 1 || birth_d > days_in_month(birth_m, birth_y)) {
        std::cerr << "Invalid birth date.\n";
        return 1;
    }

    // Get the current date
    std::time_t now = std::time(nullptr);
    std::tm* current_tm = std::localtime(&now);
    int today_y = current_tm->tm_year + 1900;
    int today_m = current_tm->tm_mon + 1;
    int today_d = current_tm->tm_mday;

    // Check if the user hasn't been born yet
    if (birth_y > today_y || (birth_y == today_y && (birth_m > today_m || (birth_m == today_m && birth_d > today_d)))) {
        std::cout << "You haven't been born yet!\n";
        return 0;
    }

    // Calculate the age in days
    int age_in_days = calculate_age_in_days(birth_y, birth_m, birth_d, today_y, today_m, today_d);

    // Output the result
    if (age_in_days < 120 * 365) {  // 120 years in days
        std::cout << "You are " << age_in_days << " days old.\n";
    } else {
        std::cout << "Come on. You can't be " << age_in_days << " days old!\n";
    }

    return 0;
}
