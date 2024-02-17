#include "hash_generator.h"
#include <gtest/gtest.h>

class HashGeneratorTests : public ::testing::Test {
protected:
    HashGenerator hashGen; // Instance of HashGenerator to be used in tests
};

// Test MD5 hash computation
TEST_F(HashGeneratorTests, ComputeMD5) {
    std::string input = "hello";
    // Expected MD5 hash of "hello"
    std::string expectedMD5 = "5d41402abc4b2a76b9719d911017c592";
    std::string actualMD5 = hashGen.computeMD5(input);
    EXPECT_EQ(actualMD5, expectedMD5);
}

// Test SHA1 hash computation
TEST_F(HashGeneratorTests, ComputeSHA1) {
    std::string input = "hello";
    // Expected SHA1 hash of "hello"
    std::string expectedSHA1 = "aaf4c61ddcc5e8a2dabede0f3b482cd9aea9434d";
    std::string actualSHA1 = hashGen.computeSHA1(input);
    EXPECT_EQ(actualSHA1, expectedSHA1);
}

// Test SHA256 hash computation
TEST_F(HashGeneratorTests, ComputeSHA256) {
    std::string input = "hello";
    // Expected SHA256 hash of "hello"
    std::string expectedSHA256 = "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824";
    std::string actualSHA256 = hashGen.computeSHA256(input);
    EXPECT_EQ(actualSHA256, expectedSHA256);
}

// Test handling of empty string
TEST_F(HashGeneratorTests, HandleEmptyString) {
    std::string input = "";
    // Expected hashes for an empty string
    std::string expectedMD5 = "d41d8cd98f00b204e9800998ecf8427e";
    std::string expectedSHA1 = "da39a3ee5e6b4b0d3255bfef95601890afd80709";
    std::string expectedSHA256 = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    EXPECT_EQ(hashGen.computeMD5(input), expectedMD5);
    EXPECT_EQ(hashGen.computeSHA1(input), expectedSHA1);
    EXPECT_EQ(hashGen.computeSHA256(input), expectedSHA256);
}
