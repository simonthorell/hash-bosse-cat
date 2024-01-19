//==============================================================================
// Program: HashBosseCat - Advanced Password Recovery Tool
// Author: Simon Thorell
// Date: 2024-01-17
// Version: 1.0
// Description: Using the GUI to upload a file of hashes to crack, the program
//              will attempt to crack the hashes using a dictionary attack.
//              The program will also allow the user to enter a hash to crack
//              manually.
//==============================================================================
#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include "hash_generator.h" // MD5, SHA1, SHA256
#include "salt_generator.h" // Add salt to strings

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    // HashGenerator hashGen; // Create a HashGenerator object
    // SaltGenerator saltGen; // Create a SaltGenerator object

    // // Prompt user to enter a string to hash
    // std::cout << "Please enter a string to hash: ";
    // std::string input_string;
    // std::cin >> input_string;

    // // Example of random salt generation
    // std::string salt = saltGen.generateSalt(10);
    // std::cout << "Salt: " << salt << std::endl;
    // std::string salted_string = input_string + salt;
    // std::cout << "Salted String: " << salted_string << std::endl;
    
    // /* As salt is random, the salted string will be different each time
    //    we will not be able to compare the hash of the salted string to
    //    a hash we have already cracked. */

    // // Compute MD5 hash
    // std::string hash = hashGen.computeMD5(input_string);
    
    // // Output the hash
    // std::cout << "MD5 Hash: " << hash << std::endl;

    // // Logic Test to compare two hashes (hashToCrack is the hash of "stefan")
    // std::string hashToCrack = "2e970e822e1a8834203d06abb60f59ec";
    
    // if (hash == hashToCrack) {
    //     std::cout << "Hashes Match!" << std::endl;
    // } else {
    //     std::cout << "Hashes Do Not Match! Try again..." << std::endl;
    // }

    // return 0;
}