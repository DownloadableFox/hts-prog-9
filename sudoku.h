#pragma once
#include <string>

class Sudoku {
private:
    char board[9][9] = {0};
public:
    bool solve();
    bool is_solved();
    bool is_valid(int row, int col, char num);
    char get(int row, int col);
    void set(int row, int col, char num);
    std::string to_string();

    Sudoku();
    Sudoku(const std::string &s);
};