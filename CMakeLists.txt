cmake_minimum_required(VERSION 3.28)
project(MyProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find QT Framework
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Add QT Framework include directories
include_directories(${Qt6Widgets_INCLUDES})
add_definitions(${Qt6Widgets_DEFINITIONS})

# Enable QT Meta Object Compiler
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add the subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# Add compiler options
add_compile_options(
    -Werror    # Treat warnings as errors
    -Wall      # Enable all warnings
    -Wextra    # Enable extra warnings
    -pedantic  # Ensure standards-compliant code
    -O2        # Optimize code
)