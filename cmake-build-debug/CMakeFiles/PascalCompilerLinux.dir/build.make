# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /snap/clion/175/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/175/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/matthew/CLionProjects/PascalCompilerLinux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PascalCompilerLinux.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/PascalCompilerLinux.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PascalCompilerLinux.dir/flags.make

CMakeFiles/PascalCompilerLinux.dir/main.cpp.o: CMakeFiles/PascalCompilerLinux.dir/flags.make
CMakeFiles/PascalCompilerLinux.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PascalCompilerLinux.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PascalCompilerLinux.dir/main.cpp.o -c /home/matthew/CLionProjects/PascalCompilerLinux/main.cpp

CMakeFiles/PascalCompilerLinux.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PascalCompilerLinux.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matthew/CLionProjects/PascalCompilerLinux/main.cpp > CMakeFiles/PascalCompilerLinux.dir/main.cpp.i

CMakeFiles/PascalCompilerLinux.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PascalCompilerLinux.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matthew/CLionProjects/PascalCompilerLinux/main.cpp -o CMakeFiles/PascalCompilerLinux.dir/main.cpp.s

CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.o: CMakeFiles/PascalCompilerLinux.dir/flags.make
CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.o: Emitter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.o -c /home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug/Emitter.cpp

CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug/Emitter.cpp > CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.i

CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug/Emitter.cpp -o CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.s

CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.o: CMakeFiles/PascalCompilerLinux.dir/flags.make
CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.o: ../MyEmulator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.o -c /home/matthew/CLionProjects/PascalCompilerLinux/MyEmulator.cpp

CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matthew/CLionProjects/PascalCompilerLinux/MyEmulator.cpp > CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.i

CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matthew/CLionProjects/PascalCompilerLinux/MyEmulator.cpp -o CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.s

# Object files for target PascalCompilerLinux
PascalCompilerLinux_OBJECTS = \
"CMakeFiles/PascalCompilerLinux.dir/main.cpp.o" \
"CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.o" \
"CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.o"

# External object files for target PascalCompilerLinux
PascalCompilerLinux_EXTERNAL_OBJECTS =

PascalCompilerLinux: CMakeFiles/PascalCompilerLinux.dir/main.cpp.o
PascalCompilerLinux: CMakeFiles/PascalCompilerLinux.dir/Emitter.cpp.o
PascalCompilerLinux: CMakeFiles/PascalCompilerLinux.dir/MyEmulator.cpp.o
PascalCompilerLinux: CMakeFiles/PascalCompilerLinux.dir/build.make
PascalCompilerLinux: CMakeFiles/PascalCompilerLinux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable PascalCompilerLinux"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PascalCompilerLinux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PascalCompilerLinux.dir/build: PascalCompilerLinux
.PHONY : CMakeFiles/PascalCompilerLinux.dir/build

CMakeFiles/PascalCompilerLinux.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PascalCompilerLinux.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PascalCompilerLinux.dir/clean

CMakeFiles/PascalCompilerLinux.dir/depend:
	cd /home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matthew/CLionProjects/PascalCompilerLinux /home/matthew/CLionProjects/PascalCompilerLinux /home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug /home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug /home/matthew/CLionProjects/PascalCompilerLinux/cmake-build-debug/CMakeFiles/PascalCompilerLinux.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PascalCompilerLinux.dir/depend

