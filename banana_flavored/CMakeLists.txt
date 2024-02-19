cmake_minimum_required(VERSION 3.14)

project(banana_flavored)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER g++)

# Globbing source files
file(GLOB_RECURSE src CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cc)

# Create a library from the source files
add_library(banana ${src})
target_include_directories(banana PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_target_properties(banana PROPERTIES OUTPUT_NAME "bfvm")

# Executable target
add_executable(exec src/main.cc)
target_link_libraries(exec PRIVATE banana)

# Add Catch2 single-header directly to your project
set(CATCH2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third_party/catch2)
include_directories(${CATCH2_INCLUDE_DIR})

# Test executable target
add_executable(test_vm test/test_vm.cc)
target_link_libraries(test_vm PRIVATE banana)

# Enable testing
enable_testing()
