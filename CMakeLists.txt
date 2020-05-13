cmake_minimum_required(VERSION 3.0.0)
project(megcc 
    VERSION 0.1.0
    DESCRIPTION "meg c compilerr"
    LANGUAGES C
)
add_subdirectory(./meglex)

include(CTest)
enable_testing()

add_executable(megcc ./megcc/main.c)
target_link_libraries(megcc meglex megsym)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
