# Makefile for Server.
CC=g++
DEPS=-I./include
SRCDIR=src
CPPFILES=ServerMain Server
TARGET=ServerEXE
LIBS=-lpthread

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

OBJ =$(patsubst %,$(ODIR)/%.obj,$(CPPFILES))

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

run: $(BINDIR)/$(TARGET)
	./$(BINDIR)/$(TARGET) $(ARG)

.PHONY: clean

clean:
	rm -rf bin obj
