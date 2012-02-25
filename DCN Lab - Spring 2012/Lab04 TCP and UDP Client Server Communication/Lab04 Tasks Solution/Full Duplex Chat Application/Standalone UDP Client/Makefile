# Makefile to compile and run standalone UDP client.
# compile: make
# run client: make run ARG="[Their name/IP] [Their Port] [My Port]"
# e.g. make run ARG="localhost 6001 6000"
# client arguments are 'localhost', '6001' and '6000'; assuming remote host is running on 127.0.0.1:6001 and client at 6000 port.
# clean: make clean

# Output target is UDPClient
UDPClient: UDPClient.obj
	g++ UDPClient.obj -o UDPClient -lpthread

# Intermediate object files.
UDPClient.obj: UDPClient.cpp
	g++ -c UDPClient.cpp -o UDPClient.obj

run: UDPClient
	./UDPClient $(ARG)

# Cleanup temprary files.
clean:
	rm -rf *.obj UDPClient
