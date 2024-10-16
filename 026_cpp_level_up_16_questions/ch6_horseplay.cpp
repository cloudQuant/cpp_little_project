// C++ Code Challenges, LinkedIn Learning

// Challenge #6: Horseplay
// Write a function that takes in the location of a knight in a chessboard and returns a vector of strings with the possible locations it might move to.
// The locations are expressed as strings in algebraic notation.
// Print the list on the terminal.
// Don't worry about other pieces on the chessboard.

#include <iostream>
#include <vector>
#include <string>

// knight_moves()
// Summary: This function receives a string with the location of a knight in a chessboard and returns a vector of strings with the possible locations it might move to.
// Arguments:
//           knight: The knight's location.
// Returns: An STL vector of strings with the possible locations to move.
std::vector<std::string> knight_moves(std::string knight){
    std::vector<std::string> possible_moves;

    // 骑士的8种可能移动方式
    std::vector<std::pair<int, int>> directions = {
            {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
            {-1, -2}, {1, -2}, {-1, 2}, {1, 2}
    };

    // 获取当前位置的行和列
    char current_col = knight[0];  // 字母部分
    char current_row = knight[1];  // 数字部分

    int col = current_col - 'a' + 1;  // 转换为数值 1-8
    int row = current_row - '0';      // 数字字符转为整数

    // 遍历所有可能的移动方式
    for (auto& dir : directions) {
        int new_col = col + dir.first;  // 计算新的列
        int new_row = row + dir.second; // 计算新的行

        // 检查是否在棋盘范围内
        if (new_col >= 1 && new_col <= 8 && new_row >= 1 && new_row <= 8) {
            // 转换为代数符号形式，例如 "e5"
            std::string new_position;
            new_position += (char)(new_col + 'a' - 1);  // 数字转为字母
            new_position += std::to_string(new_row);    // 行转为字符串
            possible_moves.push_back(new_position);     // 添加到结果
        }
    }

    return possible_moves;
}

// Main function
int main(){
    std::string knight;
    
    std::cout << "Enter the location of the knight: " << std::flush;
    std::cin >> knight;

    std::vector<std::string> the_moves = knight_moves(knight);
    std::cout << std::endl << "Possible moves from " << knight << ": ";

    for (auto element : the_moves)
        std::cout << element << " ";
    std::cout << std::endl << std::endl << std::flush;
    return 0;
}