cmake_minimum_required(VERSION 3.5)
project(boardgame VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

set(SOURCES 
    src/main.cpp
    src/AssetManager.cpp
    src/StateManager.cpp
    src/Launcher.cpp
    src/GameChoice.cpp
    src/Piece.cpp
    src/Board.cpp
    src/Player.cpp
    src/EventHandler.cpp
    src/UIHandler.cpp

    src/game/checkers/Checkers.cpp
    src/game/checkers/CheckersController.cpp
    src/game/checkers/CheckersView.cpp
    src/game/checkers/CheckersBoard.cpp
    src/game/checkers/CheckersPiece.cpp
    src/game/checkers/CheckersFlags.cpp

    src/game/butin/Butin.cpp
    src/game/butin/ButinController.cpp
    src/game/butin/ButinView.cpp
    src/game/butin/ButinBoard.cpp
    src/game/butin/ButinPiece.cpp
    src/game/butin/ButinFlags.cpp

    src/game/bulltricker/Bulltricker.cpp
    src/game/bulltricker/BulltrickerController.cpp
    src/game/bulltricker/BulltrickerView.cpp
    src/game/bulltricker/BulltrickerBoard.cpp
    src/game/bulltricker/BulltrickerPiece.cpp
    src/game/bulltricker/BulltrickerFlags.cpp

    src/game/Model.cpp
    src/game/View.cpp
    src/game/Controller.cpp
    
    src/game/ModelFlags.cpp

    src/exception/PathNotFoundException.cpp
    src/exception/InitializationException.cpp
    src/exception/InvalidUsageException.cpp
    src/exception/InvalidCoordinatesException.cpp
    src/exception/AssetNotFoundException.cpp

    # Add other source files here
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)
