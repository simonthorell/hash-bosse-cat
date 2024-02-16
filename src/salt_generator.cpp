//=============================================================================
// SaltGenerator Class Implementation
//=============================================================================
#include "salt_generator.h"

SaltGenerator::SaltGenerator() {
    // Initialize common salts with a mix of years, numbers, and special characters
    commonSalts = {
        // TODO: Replace with a file-based approach
        "1970", "1971", "1972", "1973", "1974", "1975", "1976", "1977", "1978", "1979",
        "1980", "1981", "1982", "1983", "1984", "1985", "1986", "1987", "1988", "1989",
        "1990", "1991", "1992", "1993", "1994", "1995", "1996", "1997", "1998", "1999",
        "2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007", "2008", "2009",
        "2010", "2011", "2012", "2013", "2014", "2015", "2016", "2017", "2018", "2019",
        "2020", "2021", "2022", "2023", "2024" // 54 entries so far
        
        // Numeric sequences
        "123", "234", "345", "456", "567", "678", "789", "890", "901", "012",
        "111", "222", "333", "444", "555", "666", "777", "888", "999", // 19 more, 73 total
        
        // Special characters
        "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "=", "-", "[", "]", "{", "}", "|", 
        ":", ";", "'", "\"", ",", "<", ".", ">", "/", "?", // 20 more, 93 total
        
        // Adding a few more to reach 100
        "abc", "def", "ghi", "jkl", "mno", "pqr", "stu"
    };
}
//=====================================================================
// Constructor: SaltGenerator
// Description: This constructor creates a SaltGenerator object.
//=====================================================================
SaltGenerator::~SaltGenerator() = default;

//=====================================================================
// Public Method: stripAndAddSalts
// Description: Strips trailing digits from the password and appends a
//              variant of common salts based on the provided variantIndex.
//=====================================================================
std::string SaltGenerator::stripAndAddSalts(const std::string& password, int numberOfVariants, int variantIndex) {
    std::string strippedPassword = stripTrailingDigits(password);

    // Ensure variantIndex is within bounds
    variantIndex = variantIndex % commonSalts.size();
    
    // Append a variant of common salts based on the provided variantIndex
    if (numberOfVariants > 0 && variantIndex < commonSalts.size()) {
        strippedPassword += commonSalts[variantIndex];
    }

    return strippedPassword;
}

//=====================================================================
// Private Method: stripTrailingDigits
// Description: Strips trailing digits from the input string.
//=====================================================================
std::string SaltGenerator::stripTrailingDigits(const std::string& str) {
    auto it = std::find_if_not(str.rbegin(), str.rend(), ::isdigit).base();
    return std::string(str.begin(), it);
}