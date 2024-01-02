#Compiler
CC := g++
#Compiler flags
CFLAGS := -Wall -std=c++17
#SFML flags
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
#Directory
SRC_DIR := src
GAME_DIR := game
BUTIN_DIR := butin
CHECKERS_DIR := checkers
EXCEPT_DIR := exception
#Source files
SRC_EXCEPT_DIR := $(SRC_DIR)/$(EXCEPT_DIR)
SRC_GAME_DIR := $(SRC_DIR)/$(GAME_DIR)
SRC_BUTIN_DIR := $(SRC_DIR)/$(GAME_DIR)/$(BUTIN_DIR)
SRC_CHECKERS_DIR := $(SRC_DIR)/$(GAME_DIR)/$(CHECKERS_DIR)
SRC := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_EXCEPT_DIR)/*.cpp) $(wildcard $(SRC_GAME_DIR)/*.cpp) $(wildcard $(SRC_BUTIN_DIR)/*.cpp) $(wildcard $(SRC_CHECKERS_DIR)/*.cpp)
#Object directory
OBJ_DIR := obj
#Object files
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
#Executable name
EXE := boardgame

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(SFMLFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(EXE) $(OBJ_DIR)

.PHONY: all clean