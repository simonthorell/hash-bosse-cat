#=================== INCLUSION OF Project Files ====================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${FORMS_DIR})
include_directories(${RESOURCES_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    # "${FORMS_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE RESOURCES
    "${RESOURCES_DIR}/*.qrc"
)
qt6_add_resources(RESOURCE_ADDED ${RESOURCES})

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
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCES} ${RESOURCE_ADDED})
elseif(APPLE)
    # Add debugging binary to run in VS code
    add_executable(${CMAKE_PROJECT_NAME} main.cpp ${SOURCES} ${RESOURCE_ADDED})

    #Executable for macOS - build/src/MyProject.app
    add_executable(HashBosseCat MACOSX_BUNDLE ${SOURCES} ${RESOURCE_ADDED})
    set_target_properties(HashBosseCat PROPERTIES
                        MACOSX_BUNDLE_ICON_FILE icons/favicon.icns
                        RESOURCE "${RESOURCES}")
elseif(UNIX)
    add_executable(${CMAKE_PROJECT_NAME} main.cpp ${SOURCES} ${RESOURCE_ADDED})
endif()

# Add the target includes for MY_PROJECT 
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${FORMS_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCE_DIR})

# Add the target includes for MAC OS
target_include_directories(HashBosseCat PRIVATE ${FORMS_DIR})
target_include_directories(HashBosseCat PRIVATE ${INCLUDE_DIR})
target_include_directories(HashBosseCat PRIVATE ${SOURCE_DIR})

#=================== LINKING LIBRARIES ====================#
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE MyProjectLib OpenSSL::SSL OpenSSL::Crypto Qt6::Widgets)
# For MacOS binary
target_link_libraries(HashBosseCat PRIVATE MyProjectLib OpenSSL::SSL OpenSSL::Crypto Qt6::Widgets)

#=================== APP ICON ====================#
if(APPLE)
    # Ensure the .icns file is copied to the macOS app bundle
    set_source_files_properties(${RESOURCES_DIR}/icons/favicon.icns PROPERTIES
                                MACOSX_PACKAGE_LOCATION "Resources")
elseif(WIN32)
    # Resource file for Windows is handled by .qrc
endif()