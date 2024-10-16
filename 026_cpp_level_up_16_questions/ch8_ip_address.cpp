// C++ Code Challenges, LinkedIn Learning

// Challenge #8: IP Address Validation
// Write an application that reads a string from the terminal and
// responds with a message indicating
// whether the string is a valid IP address or not.
// Assume decimal IP addresses.
// 158.25.0.33
// All numbers between 0 and 255.

#include <iostream>
#include <vector>
#include <string>

// is_valid_ip()
// Summary: This function validates an IP address.
// Arguments:
//           ip: The string to analyze with a potential ip address.
// Returns: A boolean value. True for valid ip addresses, false otherwise.
bool is_valid_ip(std::string ip){

    std::istringstream iss(ip);
    std::string segment;
    int num_segments = 0;

    while (std::getline(iss, segment, '.')) {
        // Check if the segment is empty or has leading zeros
        if (segment.empty() || (segment.size() > 1 && segment[0] == '0')) {
            return false;
        }

        // Convert segment to integer
        int num = 0;
        try {
            num = std::stoi(segment);
        } catch (const std::invalid_argument &) {
            return false;
        } catch (const std::out_of_range &) {
            return false;
        }

        // Check if the number is within the valid range
        if (num < 0 || num > 255) {
            return false;
        }

        num_segments++;
    }

    // There must be exactly 4 segments
    return num_segments == 4;
}

// Main function
int main(){
    std::string s;
    
    std::cout << std::endl << "Enter an IP address in decimal: " << std::flush;
    std::getline(std::cin,s);
    std::cout << " \n" << s << (is_valid_ip(s) ? " is" : " is not" ) << " a valid IP address.\n\n";
    return 0;
}
