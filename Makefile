#Compiler
CC := g++
#Compiler flags
CFLAGS := -Wall -std=c++17
#SFML flags
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
#Source files
SRC_DIR := src
SRC_EXCEPT_DIR := $(SRC_DIR)/exception
SRC_GAME_DIR := $(SRC_DIR)/game
SRC_BUTIN_DIR := $(SRC_DIR)/game/butin
SRC_CHECKERS_DIR := $(SRC_DIR)/game/checkers
SRC := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_EXCEPT_DIR)/*.cpp) $(wildcard $(SRC_GAME_DIR)/*.cpp) $(wildcard $(SRC_BUTIN_DIR)/*.cpp) $(wildcard $(SRC_CHECKERS_DIR)/*.cpp)
#Object files
OBJ := $(SRC:.cpp=.o)
#Executable name
EXE := boardgame

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(SFMLFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXE) $(OBJ)

.PHONY: all clean