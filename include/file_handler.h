#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <set>
#include <string>
#include <vector>
#include <unordered_map>

class FileHandler {
private:
    size_t chunkSize; // Size of chunks to read from file
public:
    // Constructor
    FileHandler(size_t chunkSize);

    // Public Methods
    size_t countFilesLinesInMap(const std::unordered_map<std::string, std::string>& filesMap);
    size_t countFileLines(const std::string& filename);
    std::set<std::string> readHashesFromFile(const std::string& filename);
    std::vector<std::string> readStringsFromFile(const std::string& filename, size_t &linesRead);
};

#endif // FILEHANDLER_H