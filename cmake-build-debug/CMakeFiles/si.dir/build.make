# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\esteb\Desktop\Teoria\si

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\esteb\Desktop\Teoria\si\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/si.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/si.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/si.dir/flags.make

CMakeFiles/si.dir/main.cpp.obj: CMakeFiles/si.dir/flags.make
CMakeFiles/si.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\esteb\Desktop\Teoria\si\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/si.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\si.dir\main.cpp.obj -c C:\Users\esteb\Desktop\Teoria\si\main.cpp

CMakeFiles/si.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/si.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\esteb\Desktop\Teoria\si\main.cpp > CMakeFiles\si.dir\main.cpp.i

CMakeFiles/si.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/si.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\esteb\Desktop\Teoria\si\main.cpp -o CMakeFiles\si.dir\main.cpp.s

CMakeFiles/si.dir/DFA.cpp.obj: CMakeFiles/si.dir/flags.make
CMakeFiles/si.dir/DFA.cpp.obj: ../DFA.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\esteb\Desktop\Teoria\si\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/si.dir/DFA.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\si.dir\DFA.cpp.obj -c C:\Users\esteb\Desktop\Teoria\si\DFA.cpp

CMakeFiles/si.dir/DFA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/si.dir/DFA.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\esteb\Desktop\Teoria\si\DFA.cpp > CMakeFiles\si.dir\DFA.cpp.i

CMakeFiles/si.dir/DFA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/si.dir/DFA.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\esteb\Desktop\Teoria\si\DFA.cpp -o CMakeFiles\si.dir\DFA.cpp.s

CMakeFiles/si.dir/NFA.cpp.obj: CMakeFiles/si.dir/flags.make
CMakeFiles/si.dir/NFA.cpp.obj: ../NFA.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\esteb\Desktop\Teoria\si\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/si.dir/NFA.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\si.dir\NFA.cpp.obj -c C:\Users\esteb\Desktop\Teoria\si\NFA.cpp

CMakeFiles/si.dir/NFA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/si.dir/NFA.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\esteb\Desktop\Teoria\si\NFA.cpp > CMakeFiles\si.dir\NFA.cpp.i

CMakeFiles/si.dir/NFA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/si.dir/NFA.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\esteb\Desktop\Teoria\si\NFA.cpp -o CMakeFiles\si.dir\NFA.cpp.s

# Object files for target si
si_OBJECTS = \
"CMakeFiles/si.dir/main.cpp.obj" \
"CMakeFiles/si.dir/DFA.cpp.obj" \
"CMakeFiles/si.dir/NFA.cpp.obj"

# External object files for target si
si_EXTERNAL_OBJECTS =

si.exe: CMakeFiles/si.dir/main.cpp.obj
si.exe: CMakeFiles/si.dir/DFA.cpp.obj
si.exe: CMakeFiles/si.dir/NFA.cpp.obj
si.exe: CMakeFiles/si.dir/build.make
si.exe: CMakeFiles/si.dir/linklibs.rsp
si.exe: CMakeFiles/si.dir/objects1.rsp
si.exe: CMakeFiles/si.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\esteb\Desktop\Teoria\si\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable si.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\si.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/si.dir/build: si.exe

.PHONY : CMakeFiles/si.dir/build

CMakeFiles/si.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\si.dir\cmake_clean.cmake
.PHONY : CMakeFiles/si.dir/clean

CMakeFiles/si.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\esteb\Desktop\Teoria\si C:\Users\esteb\Desktop\Teoria\si C:\Users\esteb\Desktop\Teoria\si\cmake-build-debug C:\Users\esteb\Desktop\Teoria\si\cmake-build-debug C:\Users\esteb\Desktop\Teoria\si\cmake-build-debug\CMakeFiles\si.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/si.dir/depend

