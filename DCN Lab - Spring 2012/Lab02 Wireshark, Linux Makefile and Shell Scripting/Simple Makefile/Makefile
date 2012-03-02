# Lines starting with '#' are comments in a linux script.
# Format for Makefile 'rule'
#
# target: dependencies
# 	<rule>
#
# target is desired output file
# dependencies are files needed to obtain target
# rule is the actual command to obtain target from dependencies
# <rule> must be preceded by a 'tab'.

# Rule for output binary or exe file. This is linking rule.
# Output file name is 'out'. It can be named anything like, out.exe or out.bin etc.
out: main.obj
	g++ main.obj -o out

# Compile rule. Creates object file(s) out of cpp files.
main.obj: main.cpp
	g++ -c main.cpp -o main.obj

# Rule for running the binary file
run: out
	./out

# cleaning rule. Deletes files named out and main.obj
clean:
	rm -f out main.obj

# To pass arguments to make run, add $(ARGS) to the run rule and execute like this: make run ARGS="arg1 arg2 arg3 arg4 arg5"
# run: out
# 	./out $(ARGS)
#
