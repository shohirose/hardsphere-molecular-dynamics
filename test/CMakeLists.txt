function(add_unit_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PUBLIC catch2 hardsphere)
    add_test(
        NAME ${name}
        COMMAND $<TARGET_FILE:${name}>
        # WORKING_DIRECTORY
    )
endfunction()

add_unit_test(vector2d)
add_unit_test(collision)