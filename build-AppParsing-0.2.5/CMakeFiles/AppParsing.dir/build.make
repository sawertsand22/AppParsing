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
CMAKE_SOURCE_DIR = /home/sawert/qtprojects/AppParsing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sawert/qtprojects/build-AppParsing-unknown-Debug

# Include any dependencies generated for this target.
include CMakeFiles/AppParsing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AppParsing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AppParsing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AppParsing.dir/flags.make

CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.o: CMakeFiles/AppParsing.dir/flags.make
CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.o: AppParsing_autogen/mocs_compilation.cpp
CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.o: CMakeFiles/AppParsing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sawert/qtprojects/build-AppParsing-unknown-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.o -MF CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.o -c /home/sawert/qtprojects/build-AppParsing-unknown-Debug/AppParsing_autogen/mocs_compilation.cpp

CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sawert/qtprojects/build-AppParsing-unknown-Debug/AppParsing_autogen/mocs_compilation.cpp > CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.i

CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sawert/qtprojects/build-AppParsing-unknown-Debug/AppParsing_autogen/mocs_compilation.cpp -o CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.s

CMakeFiles/AppParsing.dir/main.cpp.o: CMakeFiles/AppParsing.dir/flags.make
CMakeFiles/AppParsing.dir/main.cpp.o: /home/sawert/qtprojects/AppParsing/main.cpp
CMakeFiles/AppParsing.dir/main.cpp.o: CMakeFiles/AppParsing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sawert/qtprojects/build-AppParsing-unknown-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AppParsing.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AppParsing.dir/main.cpp.o -MF CMakeFiles/AppParsing.dir/main.cpp.o.d -o CMakeFiles/AppParsing.dir/main.cpp.o -c /home/sawert/qtprojects/AppParsing/main.cpp

CMakeFiles/AppParsing.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppParsing.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sawert/qtprojects/AppParsing/main.cpp > CMakeFiles/AppParsing.dir/main.cpp.i

CMakeFiles/AppParsing.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppParsing.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sawert/qtprojects/AppParsing/main.cpp -o CMakeFiles/AppParsing.dir/main.cpp.s

CMakeFiles/AppParsing.dir/mainwindow.cpp.o: CMakeFiles/AppParsing.dir/flags.make
CMakeFiles/AppParsing.dir/mainwindow.cpp.o: /home/sawert/qtprojects/AppParsing/mainwindow.cpp
CMakeFiles/AppParsing.dir/mainwindow.cpp.o: CMakeFiles/AppParsing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sawert/qtprojects/build-AppParsing-unknown-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/AppParsing.dir/mainwindow.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AppParsing.dir/mainwindow.cpp.o -MF CMakeFiles/AppParsing.dir/mainwindow.cpp.o.d -o CMakeFiles/AppParsing.dir/mainwindow.cpp.o -c /home/sawert/qtprojects/AppParsing/mainwindow.cpp

CMakeFiles/AppParsing.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppParsing.dir/mainwindow.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sawert/qtprojects/AppParsing/mainwindow.cpp > CMakeFiles/AppParsing.dir/mainwindow.cpp.i

CMakeFiles/AppParsing.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppParsing.dir/mainwindow.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sawert/qtprojects/AppParsing/mainwindow.cpp -o CMakeFiles/AppParsing.dir/mainwindow.cpp.s

CMakeFiles/AppParsing.dir/database.cpp.o: CMakeFiles/AppParsing.dir/flags.make
CMakeFiles/AppParsing.dir/database.cpp.o: /home/sawert/qtprojects/AppParsing/database.cpp
CMakeFiles/AppParsing.dir/database.cpp.o: CMakeFiles/AppParsing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sawert/qtprojects/build-AppParsing-unknown-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/AppParsing.dir/database.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AppParsing.dir/database.cpp.o -MF CMakeFiles/AppParsing.dir/database.cpp.o.d -o CMakeFiles/AppParsing.dir/database.cpp.o -c /home/sawert/qtprojects/AppParsing/database.cpp

CMakeFiles/AppParsing.dir/database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppParsing.dir/database.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sawert/qtprojects/AppParsing/database.cpp > CMakeFiles/AppParsing.dir/database.cpp.i

CMakeFiles/AppParsing.dir/database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppParsing.dir/database.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sawert/qtprojects/AppParsing/database.cpp -o CMakeFiles/AppParsing.dir/database.cpp.s

# Object files for target AppParsing
AppParsing_OBJECTS = \
"CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/AppParsing.dir/main.cpp.o" \
"CMakeFiles/AppParsing.dir/mainwindow.cpp.o" \
"CMakeFiles/AppParsing.dir/database.cpp.o"

# External object files for target AppParsing
AppParsing_EXTERNAL_OBJECTS =

AppParsing: CMakeFiles/AppParsing.dir/AppParsing_autogen/mocs_compilation.cpp.o
AppParsing: CMakeFiles/AppParsing.dir/main.cpp.o
AppParsing: CMakeFiles/AppParsing.dir/mainwindow.cpp.o
AppParsing: CMakeFiles/AppParsing.dir/database.cpp.o
AppParsing: CMakeFiles/AppParsing.dir/build.make
AppParsing: /usr/lib/x86_64-linux-gnu/libcurl.so
AppParsing: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.74.0
AppParsing: /usr/lib/x86_64-linux-gnu/libmysqlcppconn.so
AppParsing: /usr/lib/x86_64-linux-gnu/libQt5WebKitWidgets.so.5.212.0
AppParsing: /usr/lib/x86_64-linux-gnu/libxml2.so
AppParsing: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
AppParsing: /usr/lib/x86_64-linux-gnu/libQt5WebKit.so.5.212.0
AppParsing: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
AppParsing: /usr/lib/x86_64-linux-gnu/libQt5Network.so.5.15.3
AppParsing: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
AppParsing: CMakeFiles/AppParsing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sawert/qtprojects/build-AppParsing-unknown-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable AppParsing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AppParsing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AppParsing.dir/build: AppParsing
.PHONY : CMakeFiles/AppParsing.dir/build

CMakeFiles/AppParsing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AppParsing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AppParsing.dir/clean

CMakeFiles/AppParsing.dir/depend:
	cd /home/sawert/qtprojects/build-AppParsing-unknown-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sawert/qtprojects/AppParsing /home/sawert/qtprojects/AppParsing /home/sawert/qtprojects/build-AppParsing-unknown-Debug /home/sawert/qtprojects/build-AppParsing-unknown-Debug /home/sawert/qtprojects/build-AppParsing-unknown-Debug/CMakeFiles/AppParsing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AppParsing.dir/depend
