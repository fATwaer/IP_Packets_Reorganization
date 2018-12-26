# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/moonlight/IP_Packets_Reorganization

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/moonlight/IP_Packets_Reorganization

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/moonlight/IP_Packets_Reorganization/CMakeFiles /home/moonlight/IP_Packets_Reorganization/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/moonlight/IP_Packets_Reorganization/CMakeFiles 0
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
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named pktreorg

# Build rule for target.
pktreorg: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pktreorg
.PHONY : pktreorg

# fast build rule for target.
pktreorg/fast:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/build
.PHONY : pktreorg/fast

client.o: client.c.o

.PHONY : client.o

# target to build an object file
client.c.o:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/client.c.o
.PHONY : client.c.o

client.i: client.c.i

.PHONY : client.i

# target to preprocess a source file
client.c.i:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/client.c.i
.PHONY : client.c.i

client.s: client.c.s

.PHONY : client.s

# target to generate assembly for a file
client.c.s:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/client.c.s
.PHONY : client.c.s

ipf_opt.o: ipf_opt.c.o

.PHONY : ipf_opt.o

# target to build an object file
ipf_opt.c.o:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/ipf_opt.c.o
.PHONY : ipf_opt.c.o

ipf_opt.i: ipf_opt.c.i

.PHONY : ipf_opt.i

# target to preprocess a source file
ipf_opt.c.i:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/ipf_opt.c.i
.PHONY : ipf_opt.c.i

ipf_opt.s: ipf_opt.c.s

.PHONY : ipf_opt.s

# target to generate assembly for a file
ipf_opt.c.s:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/ipf_opt.c.s
.PHONY : ipf_opt.c.s

ipq_opt.o: ipq_opt.c.o

.PHONY : ipq_opt.o

# target to build an object file
ipq_opt.c.o:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/ipq_opt.c.o
.PHONY : ipq_opt.c.o

ipq_opt.i: ipq_opt.c.i

.PHONY : ipq_opt.i

# target to preprocess a source file
ipq_opt.c.i:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/ipq_opt.c.i
.PHONY : ipq_opt.c.i

ipq_opt.s: ipq_opt.c.s

.PHONY : ipq_opt.s

# target to generate assembly for a file
ipq_opt.c.s:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/ipq_opt.c.s
.PHONY : ipq_opt.c.s

main.o: main.c.o

.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i

.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s

.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/main.c.s
.PHONY : main.c.s

netpkt.o: netpkt.c.o

.PHONY : netpkt.o

# target to build an object file
netpkt.c.o:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/netpkt.c.o
.PHONY : netpkt.c.o

netpkt.i: netpkt.c.i

.PHONY : netpkt.i

# target to preprocess a source file
netpkt.c.i:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/netpkt.c.i
.PHONY : netpkt.c.i

netpkt.s: netpkt.c.s

.PHONY : netpkt.s

# target to generate assembly for a file
netpkt.c.s:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/netpkt.c.s
.PHONY : netpkt.c.s

paser.o: paser.c.o

.PHONY : paser.o

# target to build an object file
paser.c.o:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/paser.c.o
.PHONY : paser.c.o

paser.i: paser.c.i

.PHONY : paser.i

# target to preprocess a source file
paser.c.i:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/paser.c.i
.PHONY : paser.c.i

paser.s: paser.c.s

.PHONY : paser.s

# target to generate assembly for a file
paser.c.s:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/paser.c.s
.PHONY : paser.c.s

server.o: server.c.o

.PHONY : server.o

# target to build an object file
server.c.o:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/server.c.o
.PHONY : server.c.o

server.i: server.c.i

.PHONY : server.i

# target to preprocess a source file
server.c.i:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/server.c.i
.PHONY : server.c.i

server.s: server.c.s

.PHONY : server.s

# target to generate assembly for a file
server.c.s:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/server.c.s
.PHONY : server.c.s

unit_test.o: unit_test.c.o

.PHONY : unit_test.o

# target to build an object file
unit_test.c.o:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/unit_test.c.o
.PHONY : unit_test.c.o

unit_test.i: unit_test.c.i

.PHONY : unit_test.i

# target to preprocess a source file
unit_test.c.i:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/unit_test.c.i
.PHONY : unit_test.c.i

unit_test.s: unit_test.c.s

.PHONY : unit_test.s

# target to generate assembly for a file
unit_test.c.s:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/unit_test.c.s
.PHONY : unit_test.c.s

utility.o: utility.c.o

.PHONY : utility.o

# target to build an object file
utility.c.o:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/utility.c.o
.PHONY : utility.c.o

utility.i: utility.c.i

.PHONY : utility.i

# target to preprocess a source file
utility.c.i:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/utility.c.i
.PHONY : utility.c.i

utility.s: utility.c.s

.PHONY : utility.s

# target to generate assembly for a file
utility.c.s:
	$(MAKE) -f CMakeFiles/pktreorg.dir/build.make CMakeFiles/pktreorg.dir/utility.c.s
.PHONY : utility.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... pktreorg"
	@echo "... edit_cache"
	@echo "... client.o"
	@echo "... client.i"
	@echo "... client.s"
	@echo "... ipf_opt.o"
	@echo "... ipf_opt.i"
	@echo "... ipf_opt.s"
	@echo "... ipq_opt.o"
	@echo "... ipq_opt.i"
	@echo "... ipq_opt.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... netpkt.o"
	@echo "... netpkt.i"
	@echo "... netpkt.s"
	@echo "... paser.o"
	@echo "... paser.i"
	@echo "... paser.s"
	@echo "... server.o"
	@echo "... server.i"
	@echo "... server.s"
	@echo "... unit_test.o"
	@echo "... unit_test.i"
	@echo "... unit_test.s"
	@echo "... utility.o"
	@echo "... utility.i"
	@echo "... utility.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
