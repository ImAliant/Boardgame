# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src

# Include any dependencies generated for this target.
include CMakeFiles/boardgame.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/boardgame.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/boardgame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/boardgame.dir/flags.make

CMakeFiles/boardgame.dir/main.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/main.cpp.o: main.cpp
CMakeFiles/boardgame.dir/main.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/boardgame.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/main.cpp.o -MF CMakeFiles/boardgame.dir/main.cpp.o.d -o CMakeFiles/boardgame.dir/main.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/main.cpp

CMakeFiles/boardgame.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/main.cpp > CMakeFiles/boardgame.dir/main.cpp.i

CMakeFiles/boardgame.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/main.cpp -o CMakeFiles/boardgame.dir/main.cpp.s

CMakeFiles/boardgame.dir/AssetManager.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/AssetManager.cpp.o: AssetManager.cpp
CMakeFiles/boardgame.dir/AssetManager.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/boardgame.dir/AssetManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/AssetManager.cpp.o -MF CMakeFiles/boardgame.dir/AssetManager.cpp.o.d -o CMakeFiles/boardgame.dir/AssetManager.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/AssetManager.cpp

CMakeFiles/boardgame.dir/AssetManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/AssetManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/AssetManager.cpp > CMakeFiles/boardgame.dir/AssetManager.cpp.i

CMakeFiles/boardgame.dir/AssetManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/AssetManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/AssetManager.cpp -o CMakeFiles/boardgame.dir/AssetManager.cpp.s

CMakeFiles/boardgame.dir/StateManager.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/StateManager.cpp.o: StateManager.cpp
CMakeFiles/boardgame.dir/StateManager.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/boardgame.dir/StateManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/StateManager.cpp.o -MF CMakeFiles/boardgame.dir/StateManager.cpp.o.d -o CMakeFiles/boardgame.dir/StateManager.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/StateManager.cpp

CMakeFiles/boardgame.dir/StateManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/StateManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/StateManager.cpp > CMakeFiles/boardgame.dir/StateManager.cpp.i

CMakeFiles/boardgame.dir/StateManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/StateManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/StateManager.cpp -o CMakeFiles/boardgame.dir/StateManager.cpp.s

CMakeFiles/boardgame.dir/State.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/State.cpp.o: State.cpp
CMakeFiles/boardgame.dir/State.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/boardgame.dir/State.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/State.cpp.o -MF CMakeFiles/boardgame.dir/State.cpp.o.d -o CMakeFiles/boardgame.dir/State.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/State.cpp

CMakeFiles/boardgame.dir/State.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/State.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/State.cpp > CMakeFiles/boardgame.dir/State.cpp.i

CMakeFiles/boardgame.dir/State.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/State.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/State.cpp -o CMakeFiles/boardgame.dir/State.cpp.s

CMakeFiles/boardgame.dir/Launcher.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/Launcher.cpp.o: Launcher.cpp
CMakeFiles/boardgame.dir/Launcher.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/boardgame.dir/Launcher.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/Launcher.cpp.o -MF CMakeFiles/boardgame.dir/Launcher.cpp.o.d -o CMakeFiles/boardgame.dir/Launcher.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Launcher.cpp

CMakeFiles/boardgame.dir/Launcher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/Launcher.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Launcher.cpp > CMakeFiles/boardgame.dir/Launcher.cpp.i

CMakeFiles/boardgame.dir/Launcher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/Launcher.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Launcher.cpp -o CMakeFiles/boardgame.dir/Launcher.cpp.s

CMakeFiles/boardgame.dir/MainMenu.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/MainMenu.cpp.o: MainMenu.cpp
CMakeFiles/boardgame.dir/MainMenu.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/boardgame.dir/MainMenu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/MainMenu.cpp.o -MF CMakeFiles/boardgame.dir/MainMenu.cpp.o.d -o CMakeFiles/boardgame.dir/MainMenu.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/MainMenu.cpp

CMakeFiles/boardgame.dir/MainMenu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/MainMenu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/MainMenu.cpp > CMakeFiles/boardgame.dir/MainMenu.cpp.i

CMakeFiles/boardgame.dir/MainMenu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/MainMenu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/MainMenu.cpp -o CMakeFiles/boardgame.dir/MainMenu.cpp.s

CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.o: exception/PathNotFoundException.cpp
CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.o -MF CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.o.d -o CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/exception/PathNotFoundException.cpp

CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/exception/PathNotFoundException.cpp > CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.i

CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/exception/PathNotFoundException.cpp -o CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.s

CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.o: exception/GameTypeInvalidException.cpp
CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.o -MF CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.o.d -o CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/exception/GameTypeInvalidException.cpp

CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/exception/GameTypeInvalidException.cpp > CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.i

CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/exception/GameTypeInvalidException.cpp -o CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.s

CMakeFiles/boardgame.dir/exception/InitializationException.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/exception/InitializationException.cpp.o: exception/InitializationException.cpp
CMakeFiles/boardgame.dir/exception/InitializationException.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/boardgame.dir/exception/InitializationException.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/exception/InitializationException.cpp.o -MF CMakeFiles/boardgame.dir/exception/InitializationException.cpp.o.d -o CMakeFiles/boardgame.dir/exception/InitializationException.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/exception/InitializationException.cpp

CMakeFiles/boardgame.dir/exception/InitializationException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/exception/InitializationException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/exception/InitializationException.cpp > CMakeFiles/boardgame.dir/exception/InitializationException.cpp.i

CMakeFiles/boardgame.dir/exception/InitializationException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/exception/InitializationException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/exception/InitializationException.cpp -o CMakeFiles/boardgame.dir/exception/InitializationException.cpp.s

CMakeFiles/boardgame.dir/GameChoice.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/GameChoice.cpp.o: GameChoice.cpp
CMakeFiles/boardgame.dir/GameChoice.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/boardgame.dir/GameChoice.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/GameChoice.cpp.o -MF CMakeFiles/boardgame.dir/GameChoice.cpp.o.d -o CMakeFiles/boardgame.dir/GameChoice.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/GameChoice.cpp

CMakeFiles/boardgame.dir/GameChoice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/GameChoice.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/GameChoice.cpp > CMakeFiles/boardgame.dir/GameChoice.cpp.i

CMakeFiles/boardgame.dir/GameChoice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/GameChoice.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/GameChoice.cpp -o CMakeFiles/boardgame.dir/GameChoice.cpp.s

CMakeFiles/boardgame.dir/Board.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/Board.cpp.o: Board.cpp
CMakeFiles/boardgame.dir/Board.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/boardgame.dir/Board.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/Board.cpp.o -MF CMakeFiles/boardgame.dir/Board.cpp.o.d -o CMakeFiles/boardgame.dir/Board.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Board.cpp

CMakeFiles/boardgame.dir/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/Board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Board.cpp > CMakeFiles/boardgame.dir/Board.cpp.i

CMakeFiles/boardgame.dir/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/Board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Board.cpp -o CMakeFiles/boardgame.dir/Board.cpp.s

CMakeFiles/boardgame.dir/Piece.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/Piece.cpp.o: Piece.cpp
CMakeFiles/boardgame.dir/Piece.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/boardgame.dir/Piece.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/Piece.cpp.o -MF CMakeFiles/boardgame.dir/Piece.cpp.o.d -o CMakeFiles/boardgame.dir/Piece.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Piece.cpp

CMakeFiles/boardgame.dir/Piece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/Piece.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Piece.cpp > CMakeFiles/boardgame.dir/Piece.cpp.i

CMakeFiles/boardgame.dir/Piece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/Piece.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Piece.cpp -o CMakeFiles/boardgame.dir/Piece.cpp.s

CMakeFiles/boardgame.dir/Player.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/Player.cpp.o: Player.cpp
CMakeFiles/boardgame.dir/Player.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/boardgame.dir/Player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/Player.cpp.o -MF CMakeFiles/boardgame.dir/Player.cpp.o.d -o CMakeFiles/boardgame.dir/Player.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Player.cpp

CMakeFiles/boardgame.dir/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/Player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Player.cpp > CMakeFiles/boardgame.dir/Player.cpp.i

CMakeFiles/boardgame.dir/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/Player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/Player.cpp -o CMakeFiles/boardgame.dir/Player.cpp.s

CMakeFiles/boardgame.dir/game/Checkers.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/game/Checkers.cpp.o: game/Checkers.cpp
CMakeFiles/boardgame.dir/game/Checkers.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/boardgame.dir/game/Checkers.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/game/Checkers.cpp.o -MF CMakeFiles/boardgame.dir/game/Checkers.cpp.o.d -o CMakeFiles/boardgame.dir/game/Checkers.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/game/Checkers.cpp

CMakeFiles/boardgame.dir/game/Checkers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/game/Checkers.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/game/Checkers.cpp > CMakeFiles/boardgame.dir/game/Checkers.cpp.i

CMakeFiles/boardgame.dir/game/Checkers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/game/Checkers.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/game/Checkers.cpp -o CMakeFiles/boardgame.dir/game/Checkers.cpp.s

CMakeFiles/boardgame.dir/EventHandler.cpp.o: CMakeFiles/boardgame.dir/flags.make
CMakeFiles/boardgame.dir/EventHandler.cpp.o: EventHandler.cpp
CMakeFiles/boardgame.dir/EventHandler.cpp.o: CMakeFiles/boardgame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/boardgame.dir/EventHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boardgame.dir/EventHandler.cpp.o -MF CMakeFiles/boardgame.dir/EventHandler.cpp.o.d -o CMakeFiles/boardgame.dir/EventHandler.cpp.o -c /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/EventHandler.cpp

CMakeFiles/boardgame.dir/EventHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boardgame.dir/EventHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/EventHandler.cpp > CMakeFiles/boardgame.dir/EventHandler.cpp.i

CMakeFiles/boardgame.dir/EventHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boardgame.dir/EventHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/EventHandler.cpp -o CMakeFiles/boardgame.dir/EventHandler.cpp.s

# Object files for target boardgame
boardgame_OBJECTS = \
"CMakeFiles/boardgame.dir/main.cpp.o" \
"CMakeFiles/boardgame.dir/AssetManager.cpp.o" \
"CMakeFiles/boardgame.dir/StateManager.cpp.o" \
"CMakeFiles/boardgame.dir/State.cpp.o" \
"CMakeFiles/boardgame.dir/Launcher.cpp.o" \
"CMakeFiles/boardgame.dir/MainMenu.cpp.o" \
"CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.o" \
"CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.o" \
"CMakeFiles/boardgame.dir/exception/InitializationException.cpp.o" \
"CMakeFiles/boardgame.dir/GameChoice.cpp.o" \
"CMakeFiles/boardgame.dir/Board.cpp.o" \
"CMakeFiles/boardgame.dir/Piece.cpp.o" \
"CMakeFiles/boardgame.dir/Player.cpp.o" \
"CMakeFiles/boardgame.dir/game/Checkers.cpp.o" \
"CMakeFiles/boardgame.dir/EventHandler.cpp.o"

# External object files for target boardgame
boardgame_EXTERNAL_OBJECTS =

boardgame: CMakeFiles/boardgame.dir/main.cpp.o
boardgame: CMakeFiles/boardgame.dir/AssetManager.cpp.o
boardgame: CMakeFiles/boardgame.dir/StateManager.cpp.o
boardgame: CMakeFiles/boardgame.dir/State.cpp.o
boardgame: CMakeFiles/boardgame.dir/Launcher.cpp.o
boardgame: CMakeFiles/boardgame.dir/MainMenu.cpp.o
boardgame: CMakeFiles/boardgame.dir/exception/PathNotFoundException.cpp.o
boardgame: CMakeFiles/boardgame.dir/exception/GameTypeInvalidException.cpp.o
boardgame: CMakeFiles/boardgame.dir/exception/InitializationException.cpp.o
boardgame: CMakeFiles/boardgame.dir/GameChoice.cpp.o
boardgame: CMakeFiles/boardgame.dir/Board.cpp.o
boardgame: CMakeFiles/boardgame.dir/Piece.cpp.o
boardgame: CMakeFiles/boardgame.dir/Player.cpp.o
boardgame: CMakeFiles/boardgame.dir/game/Checkers.cpp.o
boardgame: CMakeFiles/boardgame.dir/EventHandler.cpp.o
boardgame: CMakeFiles/boardgame.dir/build.make
boardgame: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
boardgame: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
boardgame: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
boardgame: CMakeFiles/boardgame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable boardgame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/boardgame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/boardgame.dir/build: boardgame
.PHONY : CMakeFiles/boardgame.dir/build

CMakeFiles/boardgame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/boardgame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/boardgame.dir/clean

CMakeFiles/boardgame.dir/depend:
	cd /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src /home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/src/CMakeFiles/boardgame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/boardgame.dir/depend

