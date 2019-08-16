cmake_minimum_required(VERSION 3.8)
project(hardsphere-molecular-dynamics CXX)

add_subdirectory(external)

add_library(hardsphere INTERFACE)
target_compile_features(hardsphere INTERFACE cxx_std_14)
target_compile_options(hardsphere INTERFACE
    -Wall
    -Wextra
    -Wpedantic
)
target_include_directories(hardsphere INTERFACE include)

enable_testing()
add_subdirectory(test)