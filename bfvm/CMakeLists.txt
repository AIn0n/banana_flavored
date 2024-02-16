cmake_minimum_required(VERSION 3.14)

project(BFVM)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER g++)

# Globbing source files
file(GLOB_RECURSE src CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cc)

# Create a library from the source files
add_library(bfvm_lib ${src})
target_include_directories(bfvm_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_target_properties(bfvm_lib PROPERTIES OUTPUT_NAME "bfvm")

# Executable target
add_executable(bfvm_exec src/main.cc)
target_link_libraries(bfvm_exec PRIVATE bfvm_lib)

# Add Catch2 single-header directly to your project
set(CATCH2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third_party/catch2)
include_directories(${CATCH2_INCLUDE_DIR})

# Test executable target
add_executable(tests test/test.cc)
target_link_libraries(tests PRIVATE bfvm_lib)

# Enable testing
enable_testing()
