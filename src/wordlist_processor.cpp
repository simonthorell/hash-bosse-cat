//=====================================================================
// HashComparator Class Implementation
// Description: This class is used to compare a chunk of strings with
//              a hash set. The hash set is a set of hashes that should
//              be cracked by comparing them to the chunk of strings.
//              The chunk of strings is read from a file.
//=====================================================================
#include "wordlist_processor.h"

//=====================================================================
// Constructor: HashComparator
// Description: This constructor creates a HashComparator object.
//=====================================================================
WordlistProcessor::WordlistProcessor(const FileHandler& fileHandler, 
                               const std::unordered_set<std::string>& hashSet,
                               HashAlgorithm algorithm,
                               int numberOfVariants,
                               int saltLength)
: fileHandler(fileHandler), hashSet(hashSet) {}

//=====================================================================
// Method: compareNextChunk
// Description: This method compares a chunk of strings with the hashSet
//              and returns true if ready to receive next batch.
// Parameters:  filename - The name of the file to read from
// Return:      bool - True if ready to receive next batch
//=====================================================================
bool WordlistProcessor::compareNextChunk(const std::string& filename) {
    size_t linesRead = 0;
    auto strings = fileHandler.readStringsFromFile(filename, linesRead);
    
    if (linesRead == 0) {
        return false; // No more lines to read
    }

    /* TODO: Add logic to process each string using processString 
             which returns a vector of hashed variants of each string */

    /* TODO: Add logic to compare each hashed variant in the vector of
             hashed variants to the hashSet (hashes to crack) */

    return true; // Return true if ready to receive next batch
}

//=====================================================================
// Private Method: processString
// Description: This method processes a string by salting it and then
//              hashing it. The method returns a vector of hashed
//              variants of the string.
//=====================================================================
std::vector<std::string> WordlistProcessor::processString(const std::string& str) {
    std::vector<std::string> hashedVariants;

    // If numberOfVariants is 0, then we only want to hash the string
    if (numberOfVariants == 0) {
        std::string hashedStr = str; // Create a copy for hashing
        hashString(hashedStr);
        hashedVariants.push_back(hashedStr);
        return hashedVariants;
    }

    // Otherwise, we want to salt the string "numberOfVariants" times and hash them
    for (int i = 0; i < numberOfVariants; ++i) {
        std::string hashedSaltedStr = str; // Create a copy for salting and hashing
        saltString(hashedSaltedStr);
        hashString(hashedSaltedStr);
        hashedVariants.push_back(hashedSaltedStr);
    }

    return hashedVariants;
}

//=====================================================================
// Private Method: saltString, hashString
// Description: These methods salt and hash a string respectively.
//=====================================================================
void WordlistProcessor::saltString(std::string& str) {
    std::string salt = saltGen.generateSalt(saltLength);
    // Add salt to the original string
    str += salt;
}

void WordlistProcessor::hashString(std::string& str) {
    switch (hashAlgorithm) {
        case HashAlgorithm::MD5:
            str = hashGen.computeMD5(str);
            break;
        case HashAlgorithm::SHA1:
            str = hashGen.computeSHA1(str);
            break;
        case HashAlgorithm::SHA256:
            str = hashGen.computeSHA256(str);
            break;
        default:
            // Handle unknown hash algorithm or throw an exception
            break;
    }
}

//=====================================================================
// Example Implementation
//=====================================================================
// size_t chunkSize = 100000;
// FileHandler fileHandler(chunkSize);
// auto hashSet = fileHandler.readHashesFromFile("hashes.txt");
// WordlistProcessor processor(fileHandler, hashSet, HashAlgorithm::MD5, 10, 5);

// const std::string filename = "wordlist.txt";
// while (processor.compareNextChunk(filename)) {
//     // Continue comparing
//     // Optionally, synchronize with the file reading or handle results
// }