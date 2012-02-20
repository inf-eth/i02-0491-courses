# Lines starting with '#' are comments in a linux script.
# Format
# target: dependices
# 	<rule>

# Rule for output binary
out: main.cpp
	g++ main.cpp -o out

# Rule for run
run: out
	./out
# cleaning rule
clean:
	rm -f out

# To pass arguments to make run, add $(ARGS) to the run rule and execute like this: make run ARGS="arg1 arg2 arg3 arg4 arg5"
# run: out
# 	./out $(ARGS)
#
