# Collects all .cpp files from current and subdirectories into SOURCE_FILES
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

# Creates a static library named MyProjectLib from the collected source files
add_library(MyProjectLib ${SOURCE_FILES})
target_include_directories(MyProjectLib PUBLIC ../include) # Use ../include here
target_link_libraries(MyProjectLib PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets) 

# Creates the main executable for the project.
add_executable(MyProject ${SOURCE_FILES})
target_include_directories(MyProject PUBLIC "../include")
target_link_libraries(MyProject PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)