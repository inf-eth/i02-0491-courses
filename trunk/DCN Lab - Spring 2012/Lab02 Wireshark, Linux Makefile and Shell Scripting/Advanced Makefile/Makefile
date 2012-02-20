# Lines starting with '#' are comments in a linux script.
# Format
# target: dependencies
# 	<rule>

# Rule for output binary
binfile: main.obj complex.obj
	g++ main.obj complex.obj -o binfile
main.obj: main.cpp
	g++ -c main.cpp -o main.obj
complex.obj: complex.cpp
	g++ -c complex.cpp -o complex.obj

# Rule for run
run: binfile
	./binfile
# cleaning rule
clean:
	rm -f binfile *.obj

# To pass arguments to make run, add $(ARGS) to the run rule and execute like this: make run ARGS="arg1 arg2 arg3 arg4 arg5"
# run: binfile
# 	./binfile $(ARGS)
#
