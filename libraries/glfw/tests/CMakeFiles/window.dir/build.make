# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw

# Include any dependencies generated for this target.
include tests/CMakeFiles/window.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/window.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/window.dir/flags.make

tests/CMakeFiles/window.dir/window.c.o: tests/CMakeFiles/window.dir/flags.make
tests/CMakeFiles/window.dir/window.c.o: tests/window.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/window.dir/window.c.o"
	cd /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/window.dir/window.c.o   -c /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests/window.c

tests/CMakeFiles/window.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/window.dir/window.c.i"
	cd /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests/window.c > CMakeFiles/window.dir/window.c.i

tests/CMakeFiles/window.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/window.dir/window.c.s"
	cd /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests/window.c -o CMakeFiles/window.dir/window.c.s

tests/CMakeFiles/window.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/window.dir/flags.make
tests/CMakeFiles/window.dir/__/deps/glad_gl.c.o: deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/window.dir/__/deps/glad_gl.c.o"
	cd /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/window.dir/__/deps/glad_gl.c.o   -c /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/deps/glad_gl.c

tests/CMakeFiles/window.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/window.dir/__/deps/glad_gl.c.i"
	cd /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/deps/glad_gl.c > CMakeFiles/window.dir/__/deps/glad_gl.c.i

tests/CMakeFiles/window.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/window.dir/__/deps/glad_gl.c.s"
	cd /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/deps/glad_gl.c -o CMakeFiles/window.dir/__/deps/glad_gl.c.s

# Object files for target window
window_OBJECTS = \
"CMakeFiles/window.dir/window.c.o" \
"CMakeFiles/window.dir/__/deps/glad_gl.c.o"

# External object files for target window
window_EXTERNAL_OBJECTS =

tests/window: tests/CMakeFiles/window.dir/window.c.o
tests/window: tests/CMakeFiles/window.dir/__/deps/glad_gl.c.o
tests/window: tests/CMakeFiles/window.dir/build.make
tests/window: src/libglfw3.a
tests/window: /usr/lib/x86_64-linux-gnu/libm.so
tests/window: /usr/lib/x86_64-linux-gnu/librt.so
tests/window: /usr/lib/x86_64-linux-gnu/libm.so
tests/window: tests/CMakeFiles/window.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable window"
	cd /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/window.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/window.dir/build: tests/window

.PHONY : tests/CMakeFiles/window.dir/build

tests/CMakeFiles/window.dir/clean:
	cd /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/window.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/window.dir/clean

tests/CMakeFiles/window.dir/depend:
	cd /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests /home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/libraries/glfw/tests/CMakeFiles/window.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/window.dir/depend

