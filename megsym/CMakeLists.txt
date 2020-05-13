cmake_minimum_required(VERSION 3.0.0)
project(megsym 
    VERSION 0.1.0
    DESCRIPTION "megcc symbol managerr"
    LANGUAGES C)

include(CTest)
enable_testing()

add_library(megsym ./src/megsym.c)
target_include_directories(megsym INTERFACE ./include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
