# Makefile for LinuxVsWindowsThreadTest. Portable on windows or linux.
CC=g++
DEPS=-I./
SRCDIR=./
TARGET=LinuxVsWindowsThreadTest
LIBS=-lpthread

# debug or release configuration. Default is release.
# 'make dbg=1' will use debug configuration.
ifdef dbg
CFLAGS:=-g3
BINDIR:=./bin/debug
ODIR:=./obj/debug
else
CFLAGS:=-O3
BINDIR:=./bin/release
ODIR:=./obj/release
endif

_OBJ=$(TARGET).o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(BINDIR)/$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c -o $@ $< $(DEPS) $(CFLAGS)

# Object and binary files must be placed in obj and bin directories.
# Create bin and obj directories if they do not exist before compiling.

$(OBJ): | $(ODIR) $(BINDIR)

$(ODIR):
	mkdir -p $(ODIR)
$(BINDIR):
	mkdir -p $(BINDIR)

run: $(BINDIR)/$(TARGET)
	./$(BINDIR)/$(TARGET)

.PHONY: clean

clean:
	rm -rf obj bin
