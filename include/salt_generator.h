#ifndef SALT_GENERATOR_H
#define SALT_GENERATOR_H

#include <string>
#include <vector>
#include <algorithm>

class SaltGenerator {
public:
    SaltGenerator();
    ~SaltGenerator();
    std::string stripAndAddSalts(const std::string& password, int numberOfVariants, int variantIndex);
    
    size_t commonSaltsSize() const {
        return commonSalts.size();
    }

private:
    std::string stripTrailingDigits(const std::string& str);
    std::vector<std::string> commonSalts;
};

#endif // SALT_GENERATOR_H