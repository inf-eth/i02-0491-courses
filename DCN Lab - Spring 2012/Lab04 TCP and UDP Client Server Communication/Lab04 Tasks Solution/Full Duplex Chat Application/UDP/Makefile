# Makefile to compile and run client and server.
# compile: make
# run server: make runS ARG="localhost 6001"
# server arguments are 'localhost' and '6001' assuming client is running on 127.0.0.1:6001
# run client: make runC ARG="localhost 6000"
# client arguments are 'localhost' and '6000' assuming server is running on 127.0.0.1:6000
# clean: make clean

# Output targets are binary files 'Client' and 'Server'
Client Server: Client.obj Server.obj
	g++ Client.obj -o Client -lpthread
	g++ Server.obj -o Server -lpthread

# Intermediate object files.
Client.obj: Client.cpp
	g++ -c Client.cpp -o Client.obj
Server.obj: Server.cpp
	g++ -c Server.cpp -o Server.obj

runS: Server
	./Server $(ARG)
runC: Client
	./Client $(ARG)

# Cleanup temprary files.
clean:
	rm -rf *.obj Client Server
