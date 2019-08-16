file(DOWNLOAD
    https://github.com/catchorg/Catch2/releases/download/v2.9.2/catch.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/catch2/catch.hpp
)

add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE include)
target_compile_features(catch2 INTERFACE cxx_std_11)
target_compile_definitions(catch2 INTERFACE CATCH_CONFIG_MAIN)