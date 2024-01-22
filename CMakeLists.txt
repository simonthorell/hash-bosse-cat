cmake_minimum_required(VERSION 3.28.1)
project(MyProject VERSION 0.1 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch external libraries
include(FetchContent)

#======================= INCLUSION OF OpenSSL =======================#
FetchContent_Declare(
  openssl
  GIT_REPOSITORY https://github.com/openssl/openssl
  GIT_TAG openssl-3.2.0 # Update with latest version
)
FetchContent_MakeAvailable(openssl)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# set(CMAKE_PREFIX_PATH $ENV{QTDIR}) // Remove later

# Set the path to the Qt Framework
set(CMAKE_PREFIX_PATH "/Users/simonthorell/Qt/6.6.1/macos/lib/cmake")

# Find QT Framework libraries
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

## Fetch QT Base module (Not working properly! // Simon Thorell 2024-01-19)
# FetchContent_Declare(
#   qt
#   GIT_REPOSITORY https://github.com/qt/qtbase
#   GIT_TAG v6.6.1 # Update with latest version
# )
# FetchContent_MakeAvailable(qt)

#==================================================================#

# Add the subdirectories
add_subdirectory(src)
add_subdirectory(forms)
add_subdirectory(tests)

# Add compiler options
add_compile_options(
    -Werror    # Treat warnings as errors
    -Wall      # Enable all warnings
    -Wextra    # Enable extra warnings
    -pedantic  # Ensure standards-compliant code
    -O2        # Optimize code
)