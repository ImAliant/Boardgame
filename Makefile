#Compiler
CC := g++
#Compiler flags
CFLAGS := -Wall -std=c++17
#SFML flags
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
#Source files
SRC_DIR := src
SRC_EXCEPT_DIR := src/exception
SRC_GAME_DIR := src/game
SRC_BUTIN_DIR := src/game/butin
SRC_CHECKERS_DIR := src/game/checkers
SRC := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_EXCEPT_DIR)/*.cpp) $(wildcard $(SRC_GAME_DIR)/*.cpp) $(wildcard $(SRC_BUTIN_DIR)/*.cpp) $(wildcard $(SRC_CHECKERS_DIR)/*.cpp)
#Executable name
EXE := boardgame

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(SFMLFLAGS)

clean:
	rm -f $(EXE)

.PHONY: all clean