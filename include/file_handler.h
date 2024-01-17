#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <unordered_set>
#include <string>
#include <vector>

class FileHandler {
private:
    size_t chunkSize; // Size of chunks to read from file
public:
    // Constructor
    FileHandler(size_t chunkSize);

    // Public Methods
    std::unordered_set<std::string> readHashesFromFile(const std::string& filename);
    std::vector<std::string> readStringsFromFile(const std::string& filename, size_t &linesRead);
};

#endif // FILEHANDLER_H