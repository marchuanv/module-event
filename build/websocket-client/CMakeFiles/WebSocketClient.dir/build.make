# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\github\module-event

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\github\module-event\build

# Include any dependencies generated for this target.
include websocket-client/CMakeFiles/WebSocketClient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include websocket-client/CMakeFiles/WebSocketClient.dir/compiler_depend.make

# Include the progress variables for this target.
include websocket-client/CMakeFiles/WebSocketClient.dir/progress.make

# Include the compile flags for this target's objects.
include websocket-client/CMakeFiles/WebSocketClient.dir/flags.make

websocket-client/CMakeFiles/WebSocketClient.dir/main.cpp.obj: websocket-client/CMakeFiles/WebSocketClient.dir/flags.make
websocket-client/CMakeFiles/WebSocketClient.dir/main.cpp.obj: websocket-client/CMakeFiles/WebSocketClient.dir/includes_CXX.rsp
websocket-client/CMakeFiles/WebSocketClient.dir/main.cpp.obj: D:/github/module-event/websocket-client/main.cpp
websocket-client/CMakeFiles/WebSocketClient.dir/main.cpp.obj: websocket-client/CMakeFiles/WebSocketClient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\github\module-event\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object websocket-client/CMakeFiles/WebSocketClient.dir/main.cpp.obj"
	cd /d D:\github\module-event\build\websocket-client && D:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT websocket-client/CMakeFiles/WebSocketClient.dir/main.cpp.obj -MF CMakeFiles\WebSocketClient.dir\main.cpp.obj.d -o CMakeFiles\WebSocketClient.dir\main.cpp.obj -c D:\github\module-event\websocket-client\main.cpp

websocket-client/CMakeFiles/WebSocketClient.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/WebSocketClient.dir/main.cpp.i"
	cd /d D:\github\module-event\build\websocket-client && D:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\github\module-event\websocket-client\main.cpp > CMakeFiles\WebSocketClient.dir\main.cpp.i

websocket-client/CMakeFiles/WebSocketClient.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/WebSocketClient.dir/main.cpp.s"
	cd /d D:\github\module-event\build\websocket-client && D:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\github\module-event\websocket-client\main.cpp -o CMakeFiles\WebSocketClient.dir\main.cpp.s

# Object files for target WebSocketClient
WebSocketClient_OBJECTS = \
"CMakeFiles/WebSocketClient.dir/main.cpp.obj"

# External object files for target WebSocketClient
WebSocketClient_EXTERNAL_OBJECTS =

websocket-client/WebSocketClient.exe: websocket-client/CMakeFiles/WebSocketClient.dir/main.cpp.obj
websocket-client/WebSocketClient.exe: websocket-client/CMakeFiles/WebSocketClient.dir/build.make
websocket-client/WebSocketClient.exe: external/libexternal.a
websocket-client/WebSocketClient.exe: websocket-client/CMakeFiles/WebSocketClient.dir/linkLibs.rsp
websocket-client/WebSocketClient.exe: websocket-client/CMakeFiles/WebSocketClient.dir/objects1.rsp
websocket-client/WebSocketClient.exe: websocket-client/CMakeFiles/WebSocketClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\github\module-event\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable WebSocketClient.exe"
	cd /d D:\github\module-event\build\websocket-client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\WebSocketClient.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
websocket-client/CMakeFiles/WebSocketClient.dir/build: websocket-client/WebSocketClient.exe
.PHONY : websocket-client/CMakeFiles/WebSocketClient.dir/build

websocket-client/CMakeFiles/WebSocketClient.dir/clean:
	cd /d D:\github\module-event\build\websocket-client && $(CMAKE_COMMAND) -P CMakeFiles\WebSocketClient.dir\cmake_clean.cmake
.PHONY : websocket-client/CMakeFiles/WebSocketClient.dir/clean

websocket-client/CMakeFiles/WebSocketClient.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\github\module-event D:\github\module-event\websocket-client D:\github\module-event\build D:\github\module-event\build\websocket-client D:\github\module-event\build\websocket-client\CMakeFiles\WebSocketClient.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : websocket-client/CMakeFiles/WebSocketClient.dir/depend

