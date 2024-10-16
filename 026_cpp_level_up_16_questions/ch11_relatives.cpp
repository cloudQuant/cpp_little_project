#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

// Helper function to parse each full name and return a pair of (name, family).
std::pair<std::string, std::string> parse_name(const std::string& full_name) {
    std::stringstream ss(full_name);
    std::string name, family;

    // Separate the first word as the name and the last word as the family.
    std::getline(ss, name, ' ');    // Get the first name.
    std::getline(ss, family);       // Get the rest as family name.

    return {name, family};
}

int main() {
    std::ifstream file("names.csv");

    if (!file.is_open()) {
        std::cerr << "Failed to open the file.\n";
        return 1;
    }

    std::unordered_map<std::string, std::vector<std::string>> family_map;
    std::string line;

    // Read the CSV file line by line.
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;  // Skip empty lines
        }

        std::stringstream ss(line);
        std::string full_name;

        // Split each line by commas to get individual full names.
        while (std::getline(ss, full_name, ',')) {
            // Trim whitespace (in case there are spaces after commas)
            full_name.erase(0, full_name.find_first_not_of(' '));  // Remove leading spaces
            full_name.erase(full_name.find_last_not_of(' ') + 1);  // Remove trailing spaces

            // Parse the name and family from the full name
            auto [name, family] = parse_name(full_name);
            std::cout << "name = " << name << " family = " << family << std::endl;

            family_map[family].push_back(name); // Group names by family name.

            // If we find more than one person with the same family name, output the relatives.
            if (family_map[family].size() > 1) {
                std::cout << "Possible relatives found with the family name: " << family << "\n";
                for (const auto& person : family_map[family]) {
                    std::cout << person << " " << family << "\n";
                }
                return 0;  // Exit after finding the first pair of relatives.
            }
        }
    }

    std::cout << "No relatives found.\n";
    return 0;
}


 