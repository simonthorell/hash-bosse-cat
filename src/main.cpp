#include <iostream>
#include <openssl/evp.h>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iomanip>    // for std::setw and std::setfill

// Function to compute MD5 hash
std::string compute_md5(const std::string& input) {
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_md5(), nullptr);
    EVP_DigestUpdate(mdctx, input.c_str(), input.size());
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    // Convert the hash to a hex string
    std::stringstream ss;
    for (unsigned int i = 0; i < md_len; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)md_value[i];
    }
    return ss.str();
}

int main() {
    // Prompt user to enter a string to hash
    std::cout << "Please enter a string to hash: ";
    std::string input_string;
    std::cin >> input_string;

    // Compute MD5 hash
    std::string hash = compute_md5(input_string);
    
    // Output the hash
    std::cout << "MD5 Hash: " << hash << std::endl;

    return 0;
}