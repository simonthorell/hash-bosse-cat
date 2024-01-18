//=============================================================================
// FileHandler Class Implementation
//=============================================================================
#include "file_handler.h"
#include <fstream>
#include <iostream>

//=============================================================================
// Constructor: FileHandler
//=============================================================================
FileHandler::FileHandler(size_t chunkSize) : chunkSize(chunkSize) {}

//=============================================================================
// Public Methods: readHashesFromFile, readStringsFromFile
// Description: These methods read hashes or strings from a file and return
//              them in a set or vector respectively.
//=============================================================================
// TODO: Compare if this is faster than std::unordered_set ???
std::set<std::string> FileHandler::readHashesFromFile(const std::string& filename) {
    std::set<std::string> hashSet; // Keep in sorted order for faster lookup
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return hashSet; // Return the empty set
    }

    std::string line;
    while (std::getline(file, line)) {
        hashSet.insert(line);
    }
    
    file.close(); // Close the file when done
    return hashSet;
}

std::vector<std::string> FileHandler::readStringsFromFile(const std::string& filename, 
                                                          size_t &linesRead) {
    std::vector<std::string> strings;
    std::ifstream file(filename);
    std::string line;
    size_t currentCount = 0;
    
    while (std::getline(file, line) && currentCount < chunkSize) {
        strings.push_back(line);
        currentCount++;
    }
    
    linesRead = currentCount;
    return strings;
}

//=============================================================================
// Example usage:
//=============================================================================
/*
FileHandler fileHandler;
auto hashedPasswords = fileHandler.readHashesFromFile("hashes.txt");
auto wordlistStrings = fileHandler.readStringsFromFile("wordlist.txt");
*/

