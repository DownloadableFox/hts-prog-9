#include "sudoku.h"
#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>

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

bool Sudoku::solve() {
    std::stack<Sudoku> stack;
    stack.push(*this);

    while (!stack.empty()) {
        Sudoku current = stack.top();
        stack.pop();

        if (current.is_solved()) {
            *this = current;
            return true;
        }

        std::vector<std::pair<int, std::pair<int, int>>> empty_cells;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                int possibilities = 0;

                for (int k = 1; k <= 9; k++) {
                    if (current.is_valid(i, j, k + '0')) {
                        possibilities++;
                    }
                }

                if (current.board[i][j] == 0) {
                    auto pos = std::make_pair(i, j);
                    empty_cells.push_back(std::make_pair(possibilities, pos));
                }
            }
        }

        // sort from least possibilities to most
        std::sort(empty_cells.rbegin(), empty_cells.rend());

        for (auto cell : empty_cells) {
            int row = cell.second.first;
            int col = cell.second.second;

            for (int k = 1; k <= 9; k++) {
                if (current.is_valid(row, col, k + '0')) {
                    Sudoku next = current;
                    next.set(row, col, k + '0');
                    stack.push(next);
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
