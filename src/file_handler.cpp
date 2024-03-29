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
// Public Method: countFilesLinesInMap
// Description: This method counts the number of lines in all files in a map
//              and returns the total number of lines.
//=============================================================================
size_t FileHandler::countFilesLinesInMap(const std::unordered_map<std::string, 
                                               std::string>& filesMap) {
    size_t totalLines = 0;
    for (auto const& [key, val] : filesMap) {
        std::ifstream file(val);
        std::string line;
        while (std::getline(file, line)) {
            totalLines++;
        }
        file.close();
    }
    return totalLines;
}

size_t FileHandler::countFileLines(const std::string& filename) {
    // count the lines in the file
    std::ifstream file(filename);
    size_t totalLines = 0;
    std::string line;
    while (std::getline(file, line)) {
        totalLines++;
    }
    file.close();
    return totalLines;
}

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
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return strings; // Return the empty vector
    }

    // Seek to the last known position for this file, if it exists
    if (filePositions.find(filename) != filePositions.end()) {
        file.seekg(filePositions[filename]);
    }

    std::string line;
    size_t currentLineCount = 0;
    while (std::getline(file, line) && currentLineCount < chunkSize) {
        strings.push_back(line);
        currentLineCount++;
        linesRead++; // Increment linesRead to keep track of the overall line number.
    }

    // Store the position for the next read, if not at the end of file
    if (!file.eof()) {
        filePositions[filename] = file.tellg();
    } else {
        filePositions.erase(filename); // If at the end, remove the entry as it's no longer needed
    }
    
    return strings;
}