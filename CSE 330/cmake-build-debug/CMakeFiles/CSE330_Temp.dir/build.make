# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/kumalpatel/Desktop/clion-2020.1.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/kumalpatel/Desktop/clion-2020.1.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/sf_ASU_Courses/CSE330/CSE330-Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/sf_ASU_Courses/CSE330/CSE330-Project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CSE330_Temp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CSE330_Temp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CSE330_Temp.dir/flags.make

CMakeFiles/CSE330_Temp.dir/proj-4.c.o: CMakeFiles/CSE330_Temp.dir/flags.make
CMakeFiles/CSE330_Temp.dir/proj-4.c.o: ../proj-4.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/sf_ASU_Courses/CSE330/CSE330-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CSE330_Temp.dir/proj-4.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CSE330_Temp.dir/proj-4.c.o   -c /media/sf_ASU_Courses/CSE330/CSE330-Project/proj-4.c

CMakeFiles/CSE330_Temp.dir/proj-4.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CSE330_Temp.dir/proj-4.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/sf_ASU_Courses/CSE330/CSE330-Project/proj-4.c > CMakeFiles/CSE330_Temp.dir/proj-4.c.i

CMakeFiles/CSE330_Temp.dir/proj-4.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CSE330_Temp.dir/proj-4.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/sf_ASU_Courses/CSE330/CSE330-Project/proj-4.c -o CMakeFiles/CSE330_Temp.dir/proj-4.c.s

# Object files for target CSE330_Temp
CSE330_Temp_OBJECTS = \
"CMakeFiles/CSE330_Temp.dir/proj-4.c.o"

# External object files for target CSE330_Temp
CSE330_Temp_EXTERNAL_OBJECTS =

CSE330_Temp: CMakeFiles/CSE330_Temp.dir/proj-4.c.o
CSE330_Temp: CMakeFiles/CSE330_Temp.dir/build.make
CSE330_Temp: CMakeFiles/CSE330_Temp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/sf_ASU_Courses/CSE330/CSE330-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CSE330_Temp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CSE330_Temp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CSE330_Temp.dir/build: CSE330_Temp

.PHONY : CMakeFiles/CSE330_Temp.dir/build

CMakeFiles/CSE330_Temp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CSE330_Temp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CSE330_Temp.dir/clean

CMakeFiles/CSE330_Temp.dir/depend:
	cd /media/sf_ASU_Courses/CSE330/CSE330-Project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/sf_ASU_Courses/CSE330/CSE330-Project /media/sf_ASU_Courses/CSE330/CSE330-Project /media/sf_ASU_Courses/CSE330/CSE330-Project/cmake-build-debug /media/sf_ASU_Courses/CSE330/CSE330-Project/cmake-build-debug /media/sf_ASU_Courses/CSE330/CSE330-Project/cmake-build-debug/CMakeFiles/CSE330_Temp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CSE330_Temp.dir/depend
