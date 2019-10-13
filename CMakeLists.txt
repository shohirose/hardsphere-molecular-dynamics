cmake_minimum_required(VERSION 3.13)
project(hardsphere-molecular-dynamics CXX)

cmake_policy(SET CMP0076 NEW)
add_subdirectory(external)

add_library(hardsphere)
target_compile_features(hardsphere PUBLIC cxx_std_17)
target_compile_options(hardsphere PUBLIC
    -Wall
    -Wextra
    -Wpedantic
)
target_include_directories(hardsphere PUBLIC include)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)