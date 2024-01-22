//=====================================================================
// HashComparator Class Implementation
// Description: This class is used to compare a chunk of strings with
//              a hash set. The hash set is a set of hashes that should
//              be cracked by comparing them to the chunk of strings.
//              The chunk of strings is read from a file.
//=====================================================================
#include "wordlist_processor.h"
#include <ranges>
#include <algorithm>
#include <execution>
#include <iostream>

//=====================================================================
// Constructor: HashComparator
// Description: This constructor creates a HashComparator object.
//=====================================================================
WordlistProcessor::WordlistProcessor(const FileHandler& fileHandler, 
                                     const std::set<std::string>& hashSet,
                                     HashAlgorithm algorithm,
                                     int numberOfVariants,
                                     int saltLength)
    : fileHandler(fileHandler), hashSet(hashSet), hashAlgorithm(algorithm), 
      numberOfVariants(numberOfVariants), saltLength(saltLength) {
    // std::cout << "Constructor - hashAlgorithm: " << static_cast<int>(hashAlgorithm) << std::endl;
    // std::cout << "Constructor - numberOfVariants: " << numberOfVariants << std::endl;
    // std::cout << "Constructor - saltLength: " << saltLength << std::endl;
}
//=====================================================================
// Method: compareWordlistChunk
// Description: This method compares a chunk of strings with the hashSet
//              and returns true if ready to receive next batch.
//=====================================================================
bool WordlistProcessor::compareWordlistChunk(const std::string& filename) {
    size_t linesRead = 0;
    auto strings = fileHandler.readStringsFromFile(filename, linesRead);
    
    if (linesRead == 0) {
        return false; // No more lines to read
    }

    // Process each string in parallel & compare to hashSet (hashes to crack)
    std::for_each(std::execution::par, strings.begin(), strings.end(), 
                [&](const std::string& str) {
        // Vector of salted & hashed variants of each string from wordlist
        auto hashedVariants = processString(str);
        // Compare each hashed variant to the hashSet
        for (auto& [originalStr, hashedStr] : hashedVariants) {
            // std::cout << "Comparing: " << originalStr << " to " << hashedStr << std::endl;
            if (hashSet.find(hashedStr) != hashSet.end()) { // Binary search set
                // std::cout << "Found match: " << originalStr << " to " << hashedStr << std::endl;
                crackedHashes[hashedStr] = originalStr; // Handle cracked hash
                // Hash = key, String = value
            }
        }
    });

    /* By processing chunks we can display crackedHashes[] to user as
       they are being cracked. This is useful for long wordlists. In 
       The GUI we will also implement a progressbar by deviding chunk 
       by the total amount of lines in wordlist to get "% done". */

    return true; // Return true if ready to receive next batch of wordlist strings
}

//=====================================================================
// Private Method: processString
// Description: This method processes a string by salting it and then
//              hashing it. The method returns a vector of hashed
//              variants of the string.
//=====================================================================
std::unordered_map<std::string, std::string> 
WordlistProcessor::processString(const std::string& str) {
    std::unordered_map<std::string, std::string> hashedVariants;

    // If numberOfVariants is 0, then we only want to hash the string
    if (numberOfVariants == 0) {
        std::string hashedStr = str;
        hashString(hashedStr);
        hashedVariants[str] = hashedStr;
        return hashedVariants;
    }

    // Otherwise, we want to salt and hash the string "numberOfVariants" times
    std::vector<std::string> saltedStrings(numberOfVariants, str);
    std::vector<std::string> hashedStrings(numberOfVariants);

    std::transform( 
        std::execution::par, // Parallel computation of processed strings
        saltedStrings.begin(), saltedStrings.end(), hashedStrings.begin(),
        [&](std::string& s) {
            saltString(s);
            std::string hashed = s;
            hashString(hashed);
            return hashed;
        }
    );

    for (int i = 0; i < numberOfVariants; ++i) {
        hashedVariants[saltedStrings[i]] = hashedStrings[i];
    }

    return hashedVariants;
}

//=====================================================================
// Private Method: saltString, hashString
// Description: These methods salt and hash a string respectively.
//=====================================================================
void WordlistProcessor::saltString(std::string& str) {
    std::string salt = saltGen.generateSalt(saltLength);
    str += salt; // Add salt to the original string
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