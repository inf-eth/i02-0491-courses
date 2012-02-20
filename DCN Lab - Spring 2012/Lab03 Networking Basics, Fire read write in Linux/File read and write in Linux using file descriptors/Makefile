binfile: main.obj
	g++ main.obj -o binfile
main.obj:
	g++ -c main.cpp -o main.obj

clean:
	rm -rf main.obj binfile
run: binfile
	./binfile $(ARG)
	
	
	
