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
#include <random> // Include for std::random_device and std::mt19937
#include <mutex>

std::mutex globalGenMutex;
std::mt19937 globalGen(std::random_device{}());

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
bool WordlistProcessor::compareWordlistChunk(const std::vector<std::string>& chunk) {
    // Process each string in parallel & compare to hashSet (hashes to crack)
    std::for_each(std::execution::par, chunk.begin(), chunk.end(), 
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
    std::cout << "Number of variants: " << numberOfVariants << std::endl;
    std::cout << "Processing: " << str << std::endl;

    // Map to store salted and hashed strings
    std::unordered_map<std::string, std::string> hashedVariants;

    // First, hash the original string regardless of numberOfVariants
    std::string baseHashedStr = str;
    std::cout << "Hashing: " << baseHashedStr << std::endl;
    hashString(baseHashedStr); // Hash the original string
    hashedVariants[str] = baseHashedStr;

    // If numberOfVariants is 0, then we are done
    if (numberOfVariants == 0) {
        return hashedVariants;
    }

    // Vector to store salted and hashed strings
    std::vector<std::pair<std::string, std::string>> tempResults(numberOfVariants);

    // Execute in parallel
    std::transform(std::execution::par, tempResults.begin(), tempResults.end(), tempResults.begin(),
                   [&](auto& pair) -> std::pair<std::string, std::string> {

                       // Use random variantIndex in commonSalts
                       // Lock to safely generate a unique seed for this thread
                       std::unique_lock<std::mutex> lock(globalGenMutex);
                       unsigned int seed = globalGen();
                       lock.unlock();
                       // Initialize thread-local generator with the unique seed
                       std::mt19937 localGen(seed);
                       std::uniform_int_distribution<> distrib(0, saltGen.commonSaltsSize() - 1);
                       int variantIndex = distrib(localGen); // Use local generator

                       // Alternative 2 -- index is derived from the iterator position
                       // int variantIndex = &pair - &tempResults[0];

                       // Apply salt and hash to the string
                       std::string saltedStr = str;
                       saltString(saltedStr, variantIndex); // Apply salt variant based on index
                       std::string hashed = saltedStr;
                       std::cout << "Hashing: " << hashed << "using random common salt index: " << variantIndex << std::endl;
                       hashString(hashed); // Hash the salted string
                       return {saltedStr, hashed}; // Return the pair
                   });

    // Merge results into a map (single-threaded part)
    for (const auto& pair : tempResults) {
        hashedVariants[pair.first] = pair.second;
    }

    return hashedVariants;
}

//=====================================================================
// Private Method: saltString, hashString
// Description: These methods salt and hash a string respectively.
//=====================================================================
void WordlistProcessor::saltString(std::string& str, int variantIndex) {
    str = saltGen.stripAndAddSalts(str, numberOfVariants, variantIndex);
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