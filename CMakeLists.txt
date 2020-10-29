cmake_minimum_required(VERSION 3.17)

project(DZ2)

##
### Test definitions ###
##
set(INC_DIR ${DIR}/include)

set(SRC_DIR ${DIR}/DZ2/src)

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)

add_library(without_fork STATIC
        ${PROJECT_SOURCE_DIR}/include/DZ2/without_fork.h
        ${PROJECT_SOURCE_DIR}/src/without_fork.c
        ${PROJECT_SOURCE_DIR}/include/DZ2/utils.h
        ${PROJECT_SOURCE_DIR}/src/utils.c)

add_library(with_fork SHARED
        ${PROJECT_SOURCE_DIR}/include/DZ2/with_fork.h
        ${PROJECT_SOURCE_DIR}/src/with_fork.c
        ${PROJECT_SOURCE_DIR}/include/DZ2/utils.h
        ${PROJECT_SOURCE_DIR}/src/utils.c)


##
### Source definitions ###
##

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/DZ2/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(DZ2 ${sources})

#add_executable(DZ2 src/main.c src/without_fork.c include/without_fork.h src/with_fork.c include/with_fork.h)