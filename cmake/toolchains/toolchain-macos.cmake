# Use the system's default C/C++ compiler (likely Apple Clang)
set(CMAKE_SYSTEM_NAME Darwin)

# Optionally set the macOS deployment target
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")

# Set the C/C++ compilers
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# You might want to specify architecture-specific flags, for example:
set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "macOS architecture to build; 64-bit is standard on macOS")

# Set the sysroot path, especially if you're targeting an older version of macOS or using a custom SDK
# set(CMAKE_OSX_SYSROOT /path/to/MacOSX.sdk)

# Set any macOS-specific flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# TO RUN THIS EXAMPLE:
# cmake -S . -B build-macos -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/toolchain-macos.cmake
