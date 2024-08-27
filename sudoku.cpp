#include "sudoku.h"
#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>

bool is_better(const std::pair<std::vector<char>, std::pair<int, int>> &a, const std::pair<std::vector<char>, std::pair<int, int>> &b) {
    return a.first.size() > b.first.size();
}

Sudoku::Sudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
    }
}

Sudoku::Sudoku(const std::string &s) {
    unsigned char current = 0;

    for (size_t i = 0; i < s.size(); i++) {
        if (current >= 81) {
            return;
        }

        if (s[i] == ',') {
            current++;
        } else {
            board[current / 9][current % 9] = s[i] - '0';
        }
    }
}

std::string Sudoku::to_string() {
    std::string s = "";

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            s += board[i][j] + '0';

            if (j * 9 + i < 80) {
                s += ",";
            }
        }
    }

    return s;
}

std::string Sudoku::to_pretty_string() {
    std::string s = "";

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            s += board[i][j] + '0';

            if (j < 8) {
                s += " ";
            }
        }

        if (i < 8) {
            s += "\n";
        }
    }

    return s;
}

bool Sudoku::solve() {
    std::stack<Sudoku> stack;
    stack.push(*this);

    while (!stack.empty()) {
        Sudoku current = stack.top();
        stack.pop();

        // std::cout << "forking: " << current.to_string() << std::endl;

        if (current.is_solved()) {
            *this = current;
            return true;
        }
        
        std::vector<std::pair<std::vector<char>, std::pair<int, int>>> empty_cells;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (current.board[i][j] == 0) {
                    std::vector<char> possibilities;
                    for (int k = 1; k <= 9; k++) {
                        if (current.is_valid(i, j, k)) {
                            possibilities.push_back(k);
                        }
                    }

                    std::pair<int, int> pos = std::make_pair(i, j);
                    empty_cells.push_back(std::make_pair(possibilities, pos));
                }
            }
        }

        // custom sort to prioritize cells with fewer possibilities
        std::sort(empty_cells.begin(), empty_cells.end(), is_better);

        for (auto cell : empty_cells) {
            int row = cell.second.first;
            int col = cell.second.second;

            // try all possibilities
            // std::cout << "-> trying: " << row << ", " << col << " (possiblities: " << cell.first.size() << ")" << std::endl;

            for (int k = 1; k <= 9; k++) {
                if (current.is_valid(row, col, k)) {
                    Sudoku next = current;
                    next.set(row, col, k);
                    stack.push(next);

                    // std::cout << "-> pushing: " << next.to_string() << std::endl;
                }
            }
        }
    }

    return false;
}

bool Sudoku::is_solved() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::is_valid(int row, int col, char num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    int start_row = row - row % 3;
    int start_col = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + start_row][j + start_col] == num) {
                return false;
            }
        }
    }

    return true;
}

char Sudoku::get(int row, int col) {
    return board[row][col];
}

void Sudoku::set(int row, int col, char num) {
    board[row][col] = num;
}
