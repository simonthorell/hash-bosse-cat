#include <iostream>
#include "hash_generator.h"

int main() {
    HashGenerator hashGen;
    // Prompt user to enter a string to hash
    std::cout << "Please enter a string to hash: ";
    std::string input_string;
    std::cin >> input_string;

    // Compute MD5 hash
    std::string hash = hashGen.computeMD5(input_string);
    
    // Output the hash
    std::cout << "MD5 Hash: " << hash << std::endl;

    // Logic Test to compare two hashes (hashToCrack is the hash of "stefan")
    std::string hashToCrack = "2e970e822e1a8834203d06abb60f59ec";
    
    if (hash == hashToCrack) {
        std::cout << "Hashes Match!" << std::endl;
    } else {
        std::cout << "Hashes Do Not Match! Try again..." << std::endl;
    }

    return 0;
}