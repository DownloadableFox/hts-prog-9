#include <iostream>
#include "crypto.h"
#include "sudoku.h"
#include "blowfish.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <sudoku> <base-64-encrypted-key>" << std::endl;
        return 1;
    }

    std::string s = argv[1];
    std::string k = argv[2];
    Sudoku sudoku(s);
    
    std::cout << "sudoku:\n" << sudoku.to_pretty_string() << std::endl;

    if (sudoku.solve()) {
        std::cout << "solved:\n" << sudoku.to_pretty_string() << std::endl;
        std::cout << "solution: " << sudoku.to_string() << std::endl;

        // calculate SHA1 hash of the solution
        std::string key = sha256(sudoku.to_string());
        std::cout << "hash: " << key << std::endl;

        // decode the base64 key
        std::vector<unsigned char> chipher = base64_decode(k);
        std::cout << "base64 encrypted text: " << k <<std::endl;

        for (int i = 0; i < chipher.size(); i++) {
            printf("%02x", chipher[i]);
        }
        std::cout << std::endl;

        // decrypt the hash with the key
        unsigned char decrypted[1024] = {0};

        Blowfish blowfish;
        blowfish.SetKey((unsigned char*)key.c_str(), key.size() + 1);
        blowfish.Decrypt(chipher.data(), decrypted, chipher.size());

        std::cout << "decrypted text: " << decrypted << std::endl;   
    } else {
        std::cout << "unsolvable" << std::endl;
    }
}
