cmake_minimum_required(VERSION 3.0.0)
project(meglex 
    VERSION 0.1.0
    DESCRIPTION "megcc lexer"
    LANGUAGES C)
add_subdirectory(../megsym ${CMAKE_CURRENT_BINARY_DIR}/megsym)

include(CTest)
enable_testing()

file(GLOB_RECURSE MEGLEX_SOURCES ./src/*)

add_library(meglex ${MEGLEX_SOURCES})
target_include_directories(meglex INTERFACE ./include)
target_link_libraries(meglex megsym)

add_executable(test_dynamic_buffer ./tests/test_dynamic_buffer.c ./src/dynamic_buffer.c ./src/pattern.c)


file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/tmp)
file(GLOB_RECURSE TEST_MATERIALS "./tests/materials/*")
file(REMOVE_RECURSE ${PROJECT_BINARY_DIR}/tmp/*)
file(COPY ${TEST_MATERIALS} DESTINATION ${PROJECT_BINARY_DIR}/tmp)

add_test(
    NAME test_dynamic_buffer-a_char
    COMMAND $<TARGET_FILE:test_dynamic_buffer> a_char
    CONFIGURATIONS Debug
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tmp
)

add_test(
    NAME test_dynamic_buffer-two_chars
    COMMAND $<TARGET_FILE:test_dynamic_buffer> two_chars
    CONFIGURATIONS Debug
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tmp
)

add_test(
    NAME test_dynamic_buffer-too_many_chars
    COMMAND $<TARGET_FILE:test_dynamic_buffer> too_many_chars
    CONFIGURATIONS Debug
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tmp
)

add_test(
    NAME test_dynamic_buffer-marks
    COMMAND $<TARGET_FILE:test_dynamic_buffer> marks
    CONFIGURATIONS Debug
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tmp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
