# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/lucas/dev/QBDL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucas/dev/QBDL/build

# Include any dependencies generated for this target.
include examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/depend.make

# Include the progress variables for this target.
include examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/progress.make

# Include the compile flags for this target's objects.
include examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/flags.make

examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/classpath.cpp.o: examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/flags.make
examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/classpath.cpp.o: ../examples/tools/android_native_run/classpath.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucas/dev/QBDL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/classpath.cpp.o"
	cd /home/lucas/dev/QBDL/build/examples/tools/android_native_run && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/android_nativ_run.dir/classpath.cpp.o -c /home/lucas/dev/QBDL/examples/tools/android_native_run/classpath.cpp

examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/classpath.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/android_nativ_run.dir/classpath.cpp.i"
	cd /home/lucas/dev/QBDL/build/examples/tools/android_native_run && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucas/dev/QBDL/examples/tools/android_native_run/classpath.cpp > CMakeFiles/android_nativ_run.dir/classpath.cpp.i

examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/classpath.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/android_nativ_run.dir/classpath.cpp.s"
	cd /home/lucas/dev/QBDL/build/examples/tools/android_native_run && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucas/dev/QBDL/examples/tools/android_native_run/classpath.cpp -o CMakeFiles/android_nativ_run.dir/classpath.cpp.s

# Object files for target android_nativ_run
android_nativ_run_OBJECTS = \
"CMakeFiles/android_nativ_run.dir/classpath.cpp.o"

# External object files for target android_nativ_run
android_nativ_run_EXTERNAL_OBJECTS =

examples/tools/android_native_run/libandroid_nativ_run.so: examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/classpath.cpp.o
examples/tools/android_native_run/libandroid_nativ_run.so: examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/build.make
examples/tools/android_native_run/libandroid_nativ_run.so: examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lucas/dev/QBDL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libandroid_nativ_run.so"
	cd /home/lucas/dev/QBDL/build/examples/tools/android_native_run && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/android_nativ_run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/build: examples/tools/android_native_run/libandroid_nativ_run.so

.PHONY : examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/build

examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/clean:
	cd /home/lucas/dev/QBDL/build/examples/tools/android_native_run && $(CMAKE_COMMAND) -P CMakeFiles/android_nativ_run.dir/cmake_clean.cmake
.PHONY : examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/clean

examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/depend:
	cd /home/lucas/dev/QBDL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucas/dev/QBDL /home/lucas/dev/QBDL/examples/tools/android_native_run /home/lucas/dev/QBDL/build /home/lucas/dev/QBDL/build/examples/tools/android_native_run /home/lucas/dev/QBDL/build/examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/tools/android_native_run/CMakeFiles/android_nativ_run.dir/depend

