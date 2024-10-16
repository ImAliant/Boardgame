cmake_minimum_required(VERSION 3.5.0)
project(boardgame VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp/fr/u_paris/boardgame/include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp/fr/u_paris/boardgame/src)

# Add the include directory to the build
include_directories(${INCLUDE_DIR})
# Find all source files in the src directory
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

# Add the include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})