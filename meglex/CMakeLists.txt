cmake_minimum_required(VERSION 3.0.0)
project(meglex 
    VERSION 0.1.0
    DESCRIPTION "megcc lexer"
    LANGUAGES C)
add_subdirectory(../megsym ${CMAKE_CURRENT_BINARY_DIR}/megsym)

include(CTest)
enable_testing()

add_library(meglex ./src/meglex.c)
target_include_directories(meglex INTERFACE ./include)
target_link_libraries(meglex megsym)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
