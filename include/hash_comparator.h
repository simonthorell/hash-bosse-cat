#ifndef HASH_COMPARATOR_H
#define HASH_COMPARATOR_H

#include "file_handler.h"
#include <unordered_set>
#include <vector>
#include <string>

class HashComparator {
private:
    FileHandler fileHandler;
    std::unordered_set<std::string> hashSet;
public:
    // Constructor
    HashComparator(const FileHandler& fileHandler, const std::unordered_set<std::string>& hashSet);

    // Public Methods
    bool compareNextChunk(const std::string& filename);
};

#endif // HASHCOMPARATOR_H