# Makefile for OpenSSL Commandline wrapper in C++
CC=g++
DEPS=-I./include
SRCDIR=./src

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

_OBJ=CliMain.o OpenSSLCli.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(BINDIR)/OpenSSLCli: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#$(ODIR)/%.o: $(SRCDIR)/%.cpp
$(ODIR)/CliMain.o: $(SRCDIR)/CliMain.cpp
	$(CC) -c -o $@ $< $(DEPS) $(CFLAGS)

$(ODIR)/OpenSSLCli.o: $(SRCDIR)/OpenSSLCli.cpp
	$(CC) -c -o $@ $< $(DEPS) $(CFLAGS)

# Object and binary files must be placed in obj and bin directories.
# Create bin and obj directories if they do not exist before compiling.

$(OBJ): | $(ODIR) $(BINDIR)

$(ODIR):
	mkdir -p $(ODIR)
$(BINDIR):
	mkdir -p $(BINDIR)

all: $(BINDIR)/OpenSSLCli

.PHONY: clean

run: $(BINDIR)/OpenSSLCli
	./$(BINDIR)/OpenSSLCli

clean:
	rm -f ./obj/debug/*.o ./obj/release/*.o ./bin/debug/OpenSSLCli ./bin/release/OpenSSLCli
