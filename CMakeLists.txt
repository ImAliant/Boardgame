cmake_minimum_required(VERSION 3.5)
project(boardgame VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

set(SOURCES 
    src/BoardGame.cpp
    src/CheckersGame.cpp
    src/CheckersRules.cpp
    src/Player.cpp
    src/exception/FontNotFoundException.cpp
    src/exception/GameTypeNotFoundException.cpp
    src/Menu.cpp
    # Add other source files here
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
