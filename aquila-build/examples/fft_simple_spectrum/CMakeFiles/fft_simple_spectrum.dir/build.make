# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build

# Include any dependencies generated for this target.
include examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/depend.make

# Include the progress variables for this target.
include examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/progress.make

# Include the compile flags for this target's objects.
include examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/flags.make

examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o: examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/flags.make
examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o: /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/examples/fft_simple_spectrum/fft_simple_spectrum.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o"
	cd /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/fft_simple_spectrum && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o -c /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/examples/fft_simple_spectrum/fft_simple_spectrum.cpp

examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.i"
	cd /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/fft_simple_spectrum && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/examples/fft_simple_spectrum/fft_simple_spectrum.cpp > CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.i

examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.s"
	cd /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/fft_simple_spectrum && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/examples/fft_simple_spectrum/fft_simple_spectrum.cpp -o CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.s

examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o.requires:
.PHONY : examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o.requires

examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o.provides: examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o.requires
	$(MAKE) -f examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/build.make examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o.provides.build
.PHONY : examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o.provides

examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o.provides.build: examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o

# Object files for target fft_simple_spectrum
fft_simple_spectrum_OBJECTS = \
"CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o"

# External object files for target fft_simple_spectrum
fft_simple_spectrum_EXTERNAL_OBJECTS =

examples/fft_simple_spectrum/fft_simple_spectrum: examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o
examples/fft_simple_spectrum/fft_simple_spectrum: examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/build.make
examples/fft_simple_spectrum/fft_simple_spectrum: libAquila.a
examples/fft_simple_spectrum/fft_simple_spectrum: lib/libOoura_fft.a
examples/fft_simple_spectrum/fft_simple_spectrum: examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable fft_simple_spectrum"
	cd /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/fft_simple_spectrum && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fft_simple_spectrum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/build: examples/fft_simple_spectrum/fft_simple_spectrum
.PHONY : examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/build

examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/requires: examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/fft_simple_spectrum.cpp.o.requires
.PHONY : examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/requires

examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/clean:
	cd /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/fft_simple_spectrum && $(CMAKE_COMMAND) -P CMakeFiles/fft_simple_spectrum.dir/cmake_clean.cmake
.PHONY : examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/clean

examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/depend:
	cd /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/examples/fft_simple_spectrum /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/fft_simple_spectrum /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/fft_simple_spectrum/CMakeFiles/fft_simple_spectrum.dir/depend

