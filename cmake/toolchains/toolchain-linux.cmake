# Use the system's default C/C++ compiler (likely GCC)
set(CMAKE_SYSTEM_NAME Linux)

# Set the C/C++ compilers
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

# Set any Linux-specific flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# TO RUN THIS EXAMPLE:
# cmake -S . -B build-linux -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/toolchain-linux.cmake