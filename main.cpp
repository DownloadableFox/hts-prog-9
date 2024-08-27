#include <iostream>
#include "sudoku.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <sudoku>" << std::endl;
        return 1;
    }

    std::string s = argv[1];
    Sudoku sudoku(s);
    
    std::cout << "sudoku:\n" << sudoku.to_pretty_string() << std::endl;

    if (sudoku.solve()) {
        std::cout << "solved:\n" << sudoku.to_pretty_string() << std::endl;
        std::cout << "solution: " << sudoku.to_string() << std::endl;
    } else {
        std::cout << "unsolvable" << std::endl;
    }
}
