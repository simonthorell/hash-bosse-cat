#include <gtest/gtest.h>
#include "test_file_handler.cpp"
// #include "test_hash_generator.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
