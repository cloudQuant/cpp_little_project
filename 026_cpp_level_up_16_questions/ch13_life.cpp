// C++ Code Challenges, LinkedIn Learning

// Challenge #13: Conway's Game of Life
// Write an application that runs Conway's Game of Life, the best-known cellular automaton.
// Do this for a 10x10 grid.
// The grid wraps around in all directions, like the Pac-Man world.

// Rules:
// Any live cell with fewer than two live neighbors dies, as if by underpopulation.
// Any live cell with two or three live neighbors lives on to the next generation.
// Any live cell with more than three live neighbors dies, as if by overpopulation.
// Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>


#define N 10
#define M 10

// Conway's Game of Life, main()
// Summary: This application is a simulation of Conway's game of life.
void is_go_on_live(const char game[N][M],
                   const std::vector<std::pair<int,int>> & moves,
                   char result[N][M],
                   int i, int j){
    char status = game[i][j];
    int count = 0;
    for (auto p: moves){
        int new_i = i+p.first;
        int new_j = j+p.second;
        if (new_i>=0 && new_j<N && new_j>=0 && new_j < M){
            if (game[new_i][new_j]=='X'){
                count++;
            }
        }
    }
    if (status == 'X' && count < 2){
        result[i][j] = '-';}
    else if (status == 'X' && count <=3){
        result[i][j] = 'X';}
    else if (status == 'X' && count == 4){
        result[i][j] = '-';}
    else if (status == '-' && count == 3){
        result[i][j] = 'X';}
    else{
        result[i][j] = '-';
    }
}
int main(){    
    // The game, initialized with a glider and a blinker.
    char game[N][M];  
    std::memset(game,'-',N*M); // Initialize game with dashes.
    std::vector<std::pair<int,int>> moves = {{0,1},{0,-1},{-1,0},{-1,1},{-1,-1}, {1,0}, {1,-1}, {1,1}};
    char result[N][M];
    // A glider     // - - - - - - - - - -
    game[1][1]='X'; // - X - - - - - - - -
    game[2][2]='X'; // - - X - - - - - - -
    game[3][0]='X'; // X X X - - - - - - -
    game[3][1]='X';
    game[3][2]='X';

    // A blinker    // - - - - - - - - - -
    game[3][6]='X'; // - - - - - - - - - -
    game[3][7]='X'; // - - - - - - - - - -
    game[3][8]='X'; // - - - - - - X X X -
    
    int generation = 0;
    std::string go_on;
    do{
        std::cout << "Generation #" << generation++ << "\n";
        for (auto &str : game){
            for (auto &ch : str)
                std::cout << " " << ch;
            std::cout << "\n";
        }
        std::cout << "\n";

        // Write your code here
        for (int i=0; i<N;++i){
            for (int j=0;j<M;++j){
                is_go_on_live(game, moves, result, i, j);
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                game[i][j] = result[i][j];
            }
        }
        std::cout << "Press Enter for the next generation, or type \"Exit\": " << std::flush;
        std::getline(std::cin,go_on);
        std::transform(go_on.begin(), go_on.end(), go_on.begin(), toupper);
        std::cout << "\n" << std::flush;
    }while(go_on.compare("EXIT")!=0);
    
    return 0;
}
