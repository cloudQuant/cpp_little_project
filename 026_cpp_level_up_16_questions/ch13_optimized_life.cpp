#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

#define N 10
#define M 10

// Function to check the next state of each cell
void update_cell(const char game[N][M], char result[N][M], int i, int j) {
    // Directions for neighbors: up, down, left, right and 4 diagonal directions
    std::vector<std::pair<int, int>> moves = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    int live_neighbors = 0;

    // Count live neighbors
    for (auto move : moves) {
        int new_i = (i + move.first + N) % N;  // Wrap around vertically
        int new_j = (j + move.second + M) % M; // Wrap around horizontally
        if (game[new_i][new_j] == 'X') {
            live_neighbors++;
        }
    }

    // Apply the Game of Life rules
    if (game[i][j] == 'X') {  // Cell is currently alive
        if (live_neighbors < 2 || live_neighbors > 3) {
            result[i][j] = '-';  // Dies
        } else {
            result[i][j] = 'X';  // Lives
        }
    } else {  // Cell is currently dead
        if (live_neighbors == 3) {
            result[i][j] = 'X';  // Becomes alive
        } else {
            result[i][j] = '-';  // Stays dead
        }
    }
}

int main() {
    // The game grid, initialized with a glider and a blinker.
    char game[N][M];
    std::memset(game, '-', N * M); // Initialize game with dashes
    char result[N][M];  // To store the next generation

    // Initialize a glider
    game[1][1] = 'X';
    game[2][2] = 'X';
    game[3][0] = 'X';
    game[3][1] = 'X';
    game[3][2] = 'X';

    // Initialize a blinker
    game[3][6] = 'X';
    game[3][7] = 'X';
    game[3][8] = 'X';

    int generation = 0;
    std::string go_on;

    do {
        // Print the current generation
        std::cout << "Generation #" << generation++ << "\n";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                std::cout << " " << game[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        // Update the game state for the next generation
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                update_cell(game, result, i, j);
            }
        }

        // Copy result back to game
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                game[i][j] = result[i][j];
            }
        }

        // Ask the user if they want to continue or exit
        std::cout << "Press Enter for the next generation, or type \"Exit\": " << std::flush;
        std::getline(std::cin, go_on);
        std::transform(go_on.begin(), go_on.end(), go_on.begin(), ::toupper);
        std::cout << "\n" << std::flush;

    } while (go_on.compare("EXIT") != 0);

    return 0;
}
