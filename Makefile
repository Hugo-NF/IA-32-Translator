# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/hugo/Documentos/UnB/SB/IA-32-Translator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hugo/Documentos/UnB/SB/IA-32-Translator

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/hugo/Documentos/UnB/SB/IA-32-Translator/CMakeFiles /home/hugo/Documentos/UnB/SB/IA-32-Translator/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/hugo/Documentos/UnB/SB/IA-32-Translator/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named tradutor

# Build rule for target.
tradutor: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tradutor
.PHONY : tradutor

# fast build rule for target.
tradutor/fast:
	$(MAKE) -f CMakeFiles/tradutor.dir/build.make CMakeFiles/tradutor.dir/build
.PHONY : tradutor/fast

src/io_file.o: src/io_file.cpp.o

.PHONY : src/io_file.o

# target to build an object file
src/io_file.cpp.o:
	$(MAKE) -f CMakeFiles/tradutor.dir/build.make CMakeFiles/tradutor.dir/src/io_file.cpp.o
.PHONY : src/io_file.cpp.o

src/io_file.i: src/io_file.cpp.i

.PHONY : src/io_file.i

# target to preprocess a source file
src/io_file.cpp.i:
	$(MAKE) -f CMakeFiles/tradutor.dir/build.make CMakeFiles/tradutor.dir/src/io_file.cpp.i
.PHONY : src/io_file.cpp.i

src/io_file.s: src/io_file.cpp.s

.PHONY : src/io_file.s

# target to generate assembly for a file
src/io_file.cpp.s:
	$(MAKE) -f CMakeFiles/tradutor.dir/build.make CMakeFiles/tradutor.dir/src/io_file.cpp.s
.PHONY : src/io_file.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/tradutor.dir/build.make CMakeFiles/tradutor.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/tradutor.dir/build.make CMakeFiles/tradutor.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/tradutor.dir/build.make CMakeFiles/tradutor.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/translator.o: src/translator.cpp.o

.PHONY : src/translator.o

# target to build an object file
src/translator.cpp.o:
	$(MAKE) -f CMakeFiles/tradutor.dir/build.make CMakeFiles/tradutor.dir/src/translator.cpp.o
.PHONY : src/translator.cpp.o

src/translator.i: src/translator.cpp.i

.PHONY : src/translator.i

# target to preprocess a source file
src/translator.cpp.i:
	$(MAKE) -f CMakeFiles/tradutor.dir/build.make CMakeFiles/tradutor.dir/src/translator.cpp.i
.PHONY : src/translator.cpp.i

src/translator.s: src/translator.cpp.s

.PHONY : src/translator.s

# target to generate assembly for a file
src/translator.cpp.s:
	$(MAKE) -f CMakeFiles/tradutor.dir/build.make CMakeFiles/tradutor.dir/src/translator.cpp.s
.PHONY : src/translator.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... tradutor"
	@echo "... edit_cache"
	@echo "... src/io_file.o"
	@echo "... src/io_file.i"
	@echo "... src/io_file.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/translator.o"
	@echo "... src/translator.i"
	@echo "... src/translator.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

