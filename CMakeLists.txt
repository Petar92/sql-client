cmake_minimum_required(VERSION 3.16)
project(Sql-Client VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Threads REQUIRED)

find_library(LIBPG_QUERY_LIB pg_query REQUIRED)
find_path(LIBPG_QUERY_INCLUDE_DIR pg_query.h REQUIRED)

include_directories(include)
include_directories(${LIBPG_QUERY_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} 
    ${Boost_LIBRARIES}
    ${LIBPG_QUERY_LIB}
    Threads::Threads
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()