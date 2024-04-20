all: main

main: main.o struct.o
	@echo "linking aplication"
	gcc -o main main.o struct.o 
	chmod +X main

main.o: main.c
	@echo "Compiling main file"
	gcc -c main.c 

struct.o: struct.c
	@echo "Compiling struct file"
	gcc -c struct.c 


clean:
	@echo "removing all but the source files"
	rm main.o struct.o main


