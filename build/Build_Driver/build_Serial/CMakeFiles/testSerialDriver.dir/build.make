# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build

# Include any dependencies generated for this target.
include Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/depend.make

# Include the progress variables for this target.
include Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/progress.make

# Include the compile flags for this target's objects.
include Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/flags.make

Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.o: Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/flags.make
Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.o: /home/seloisel/01_Projets/AGV/02_Code/03_Driver/Driver_SerialDriver/src/Driver_SerialDriver.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.o"
	cd /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/Build_Driver/build_Serial && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.o   -c /home/seloisel/01_Projets/AGV/02_Code/03_Driver/Driver_SerialDriver/src/Driver_SerialDriver.c

Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.i"
	cd /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/Build_Driver/build_Serial && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/seloisel/01_Projets/AGV/02_Code/03_Driver/Driver_SerialDriver/src/Driver_SerialDriver.c > CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.i

Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.s"
	cd /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/Build_Driver/build_Serial && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/seloisel/01_Projets/AGV/02_Code/03_Driver/Driver_SerialDriver/src/Driver_SerialDriver.c -o CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.s

Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.o: Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/flags.make
Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.o: /home/seloisel/01_Projets/AGV/02_Code/03_Driver/Driver_SerialDriver/test/TI_Driver_SerialDriver.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.o"
	cd /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/Build_Driver/build_Serial && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.o   -c /home/seloisel/01_Projets/AGV/02_Code/03_Driver/Driver_SerialDriver/test/TI_Driver_SerialDriver.c

Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.i"
	cd /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/Build_Driver/build_Serial && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/seloisel/01_Projets/AGV/02_Code/03_Driver/Driver_SerialDriver/test/TI_Driver_SerialDriver.c > CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.i

Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.s"
	cd /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/Build_Driver/build_Serial && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/seloisel/01_Projets/AGV/02_Code/03_Driver/Driver_SerialDriver/test/TI_Driver_SerialDriver.c -o CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.s

# Object files for target testSerialDriver
testSerialDriver_OBJECTS = \
"CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.o" \
"CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.o"

# External object files for target testSerialDriver
testSerialDriver_EXTERNAL_OBJECTS =

Build_Driver/build_Serial/testSerialDriver: Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/src/Driver_SerialDriver.o
Build_Driver/build_Serial/testSerialDriver: Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/test/TI_Driver_SerialDriver.o
Build_Driver/build_Serial/testSerialDriver: Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/build.make
Build_Driver/build_Serial/testSerialDriver: Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable testSerialDriver"
	cd /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/Build_Driver/build_Serial && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testSerialDriver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/build: Build_Driver/build_Serial/testSerialDriver

.PHONY : Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/build

Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/clean:
	cd /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/Build_Driver/build_Serial && $(CMAKE_COMMAND) -P CMakeFiles/testSerialDriver.dir/cmake_clean.cmake
.PHONY : Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/clean

Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/depend:
	cd /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700 /home/seloisel/01_Projets/AGV/02_Code/03_Driver/Driver_SerialDriver /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/Build_Driver/build_Serial /home/seloisel/01_Projets/AGV/02_Code/02_Middleware/Library_LibBatMngBmv700/build/Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Build_Driver/build_Serial/CMakeFiles/testSerialDriver.dir/depend
