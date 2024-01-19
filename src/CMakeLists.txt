#=================== INCLUSION OF Project Files ====================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    "${FORMS_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

#=================== STATIC Library ====================#
# Create a static library named MyProjectLib from the collected source files
add_library(MyProjectLib ${SOURCE_FILES})
target_link_libraries(MyProjectLib PRIVATE OpenSSL::SSL OpenSSL::Crypto Qt6::Core Qt6::Gui Qt6::Widgets) 

#=================== SETUP EXECTUABLE ====================#
# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Add the executable
if (WIN32) 
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCES})
elseif(UNIX)
    add_executable(${CMAKE_PROJECT_NAME} main.cpp ${SOURCES})
endif()

# Add the target includes for MY_PROJECT 
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${FORMS_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCE_DIR})

#=================== LINKING LIBRARIES ====================#
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE MyProjectLib OpenSSL::SSL OpenSSL::Crypto Qt6::Widgets)