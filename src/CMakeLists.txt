# Collects all .cpp files from current and subdirectories into SOURCE_FILES
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
# Find OpenSSL & QT Framework libraries
find_package(OpenSSL REQUIRED)
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Add QT Framework include directories
include_directories(${Qt6Widgets_INCLUDES})
add_definitions(${Qt6Widgets_DEFINITIONS})

# Enable QT Meta Object Compiler
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Creates a static library named MyProjectLib from the collected source files
add_library(MyProjectLib ${SOURCE_FILES})
target_include_directories(MyProjectLib PUBLIC ../include) # Use ../include here
target_link_libraries(MyProjectLib PRIVATE OpenSSL::SSL OpenSSL::Crypto Qt6::Core Qt6::Gui Qt6::Widgets) 

# Creates the main executable for the project.
add_executable(MyProject ${SOURCE_FILES})
target_include_directories(MyProject PUBLIC "../include")
target_link_libraries(MyProject PRIVATE OpenSSL::SSL OpenSSL::Crypto Qt6::Core Qt6::Gui Qt6::Widgets)