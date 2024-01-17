//=============================================================================
// FileHandler Class Implementation
//=============================================================================
#include "file_handler.h"
#include <fstream>
//=============================================================================
// Constructor: FileHandler
//=============================================================================
FileHandler::FileHandler(size_t chunkSize) : chunkSize(chunkSize) {}
//=============================================================================
// Public Methods: FileHandler
//=============================================================================
std::unordered_set<std::string> FileHandler::readHashesFromFile(const std::string& filename) {
    std::unordered_set<std::string> hashSet;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        hashSet.insert(line);
    }
    
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

/* Example usage:
FileHandler fileHandler;
auto hashedPasswords = fileHandler.readHashesFromFile("hashes.txt");
auto wordlistStrings = fileHandler.readStringsFromFile("wordlist.txt");
*/

