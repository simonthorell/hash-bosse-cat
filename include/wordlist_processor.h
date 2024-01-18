#ifndef WORDLIST_PROCESSOR_H
#define WORDLIST_PROCESSOR_H

#include "file_handler.h"
#include "salt_generator.h"
#include "hash_generator.h"
#include <set>
#include <unordered_map>
#include <vector>
#include <string>

enum class HashAlgorithm {
    MD5,
    SHA1,
    SHA256
};

class WordlistProcessor {
private:
    FileHandler fileHandler;
    SaltGenerator saltGen;
    HashGenerator hashGen;

    HashAlgorithm hashAlgorithm; // The algorithm to use for hashing (MD5, SHA1, SHA256)
    int numberOfVariants; // Number of salted variants to generate for each string
    int saltLength; // Length of salt to generate for each string
    std::set<std::string> hashSet; // Set of hashes that wordlist will be compared against
    std::unordered_map<std::string, std::string> crackedHashes; // Map of cracked hashes
public:
    // Constructor
    WordlistProcessor(const FileHandler& fileHandler, 
                      const std::set<std::string>& hashSet, 
                      HashAlgorithm algorithm, 
                      int numberOfVariants,
                      int saltLength);

    // Public Methods
    bool compareWordlistChunk(const std::string& filename);

    // Private Methods
    std::unordered_map<std::string, std::string> processString(const std::string& str);
    void saltString(std::string& str);
    void hashString(std::string& str);
};

#endif // WORDLIST_PROCESSOR_H