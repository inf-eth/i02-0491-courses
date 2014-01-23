# Lines starting with '#' are comments in a linux script.
# Format for Makefile 'rule'
#
# target: dependencies
# 	<recipe>
#
# target is desired output file
# dependencies are files needed to obtain target
# recipe is the actual command to obtain target from dependencies
# <recipe> must be preceded by a 'tab'.

# Rule for output binary or exe file. This is linking rule.
# Output file name is 'out'. It can be named anything like, out.exe or out.bin etc.
binfile: main.obj complex.obj
	g++ main.obj complex.obj -o binfile

# Compile rules. Creates object file(s) out of cpp files.
main.obj: main.cpp
	g++ -c main.cpp -o main.obj

complex.obj: complex.cpp
	g++ -c complex.cpp -o complex.obj
	
# Rule for running the binary file.
run: binfile
	./binfile

# cleaning rule. Deletes binary file and any object files
clean:
	rm -f binfile *.obj