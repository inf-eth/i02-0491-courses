# AutomatedWormFingerprinting Makefile.
# Input names of cpp files (without .cpp extension) against CPPFILES separated by spaces.
# Mention output binary filename against TARGET.
#
# CC = compiler name
# DEPS = any additional folders containing header apart from system headers. Default is current directory.
# SRCDIR = directory containing source files. Default is current directory.
# CPPFILES = names of cpp files to be compiled.
# TARGET= output binary file name.
# LIBS= any libraries to link with (e.g. -lpthread). Default is none.

CC=g++
DEPS=-I./include
SRCDIR=./src
CPPFILES=TCP_Header_Analysis PacketManip
TARGET=TCP_Header_Analysis
LIBS=-lpcap

# debug or release configuration. Default is release.
# 'make dbg=1' will use debug configuration.
ifdef dbg
CFLAGS:=-g3
BINDIR:=bin/debug
ODIR:=obj/debug
else
CFLAGS:=-O3
BINDIR:=bin/release
ODIR:=obj/release
endif

OBJ=$(patsubst %,$(ODIR)/%.obj,$(CPPFILES))

$(BINDIR)/$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.obj: $(SRCDIR)/%.cpp
	$(CC) -c -o $@ $< $(DEPS) $(CFLAGS)

# Object and binary files must be placed in obj and bin directories.
# Create bin and obj directories if they do not exist before compiling.
$(OBJ): | $(ODIR) $(BINDIR)

$(ODIR):
	mkdir -p $(ODIR)
$(BINDIR):
	mkdir -p $(BINDIR)

# Default run.
run: $(BINDIR)/$(TARGET)
	./$(BINDIR)/$(TARGET) $(ARG)

all: $(BINDIR)/$(TARGET)

.PHONY: clean

clean:
	rm -rf bin obj
