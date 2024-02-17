#include "file_handler.h"
#include <gtest/gtest.h>
#include <fstream>

class FileHandlerTest : public ::testing::Test {
protected:
    // Temporary files to be used in tests
    std::vector<std::string> tempFiles;

    // Function to create a temporary file with given content
    void createTempFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << content;
            file.close();
            tempFiles.push_back(filename);
        }
    }

    // Clean up temporary files
    virtual void TearDown() override {
        for (const auto& file : tempFiles) {
            std::remove(file.c_str());
        }
        tempFiles.clear();
    }
};