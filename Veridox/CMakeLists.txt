cmake_minimum_required(VERSION 3.16)
project(Veridox VERSION 0.0.1)

# Set C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Include directories
include_directories(
    "${PROJECT_SOURCE_DIR}/Public/include"
    "${PROJECT_SOURCE_DIR}/Private/include"
    "${PROJECT_SOURCE_DIR}/../Dependencies/include"
)

# Locate source files
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/Public/source/*.cpp"
    "${PROJECT_SOURCE_DIR}/Private/source/*.cpp"
    "${PROJECT_SOURCE_DIR}/Public/include/*.h"
    "${PROJECT_SOURCE_DIR}/Private/include/*.h"
)

# Create a static library
add_library(Veridox STATIC ${SOURCES})

target_compile_features(Veridox PUBLIC cxx_std_20)

# Set output directories
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/lib")
set_target_properties(Veridox PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
)

# Ensure static runtime linking on MSVC (matches premake setting `staticruntime "On"`)
if(MSVC)
    foreach(flag_var
        CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif()
    endforeach()
endif()

# ------------------------------
# INSTALL TARGET
# ------------------------------

# Install the static library
install(TARGETS Veridox
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install header files into include/Veridox/
install(DIRECTORY Public/include/ DESTINATION include/Veridox
    FILES_MATCHING PATTERN "*.h"
)
