//=====================================================================
// HashComparator Class Implementation
// Description: This class is used to compare a chunk of strings with
//              a hash set. The hash set is a set of hashes that should
//              be cracked by comparing them to the chunk of strings.
//              The chunk of strings is read from a file.
//=====================================================================
#include "hash_comparator.h"
//=====================================================================
// Constructor: HashComparator
// Description: This constructor creates a HashComparator object.
//=====================================================================
HashComparator::HashComparator(const FileHandler& fileHandler, 
                               const std::unordered_set<std::string>& hashSet)
: fileHandler(fileHandler), hashSet(hashSet) {}

//=====================================================================
// Method: compareNextChunk
// Description: This method compares a chunk of strings with the hashSet
//              and returns true if ready to receive next batch.
// Parameters:  filename - The name of the file to read from
// Return:      bool - True if ready to receive next batch
//=====================================================================
bool HashComparator::compareNextChunk(const std::string& filename) {
    size_t linesRead = 0;
    auto strings = fileHandler.readStringsFromFile(filename, linesRead);
    
    if (linesRead == 0) {
        return false; // No more lines to read
    }

    // TODO: Add logic to salt each string in the chunk in 
    //       multiple variations, then hash each variation.

    // TODO: Add logic to compare the salted/hashed strings
    //       with the hashSet of passwords to crack.


    return true; // Return true if ready to receive next batch
}

/* EXAMPLE IDEA FOR USING THE HASHCOMPARATOR CLASS: 
size_t chunkSize = 100000;
FileHandler fileHandler(chunkSize);
auto hashSet = fileHandler.readHashesFromFile("hashes.txt");
HashComparator hashComparator(fileHandler, hashSet);

const std::string filename = "wordlist.txt";
while (hashComparator.compareNextChunk(filename)) {
    // Continue comparing
    // Optionally, synchronize with the file reading or handle results
}
*/