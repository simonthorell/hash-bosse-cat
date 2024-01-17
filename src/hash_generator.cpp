#include "hash_generator.h"
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>

HashGenerator::HashGenerator() {
    // TODO: add constructor code (if needed)
}

HashGenerator::~HashGenerator() {
    // TODO: add destructor code (if needed)
}

std::string HashGenerator::computeMD5(const std::string& input) {
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_md5(), nullptr);
    EVP_DigestUpdate(mdctx, input.c_str(), input.size());
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    return bytesToHexString(md_value, md_len);
}

std::string HashGenerator::computeSHA1(const std::string& input) {
    unsigned char sha1_value[EVP_MAX_MD_SIZE];
    unsigned int sha1_len;

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_sha1(), nullptr);
    EVP_DigestUpdate(mdctx, input.c_str(), input.size());
    EVP_DigestFinal_ex(mdctx, sha1_value, &sha1_len);
    EVP_MD_CTX_free(mdctx);

    return bytesToHexString(sha1_value, sha1_len);
}

std::string HashGenerator::computeSHA256(const std::string& input) {
    unsigned char sha256_value[EVP_MAX_MD_SIZE];
    unsigned int sha256_len;

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(mdctx, input.c_str(), input.size());
    EVP_DigestFinal_ex(mdctx, sha256_value, &sha256_len);
    EVP_MD_CTX_free(mdctx);

    return bytesToHexString(sha256_value, sha256_len);
}

std::string HashGenerator::bytesToHexString(const unsigned char* data, unsigned int length) {
    std::stringstream ss;
    for (unsigned int i = 0; i < length; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }
    return ss.str();
}