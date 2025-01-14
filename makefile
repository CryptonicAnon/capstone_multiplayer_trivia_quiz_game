ServerProgram : main.o server.o
	gcc main.o server.o -o ServerProgram

main.o : main.c
	gcc -c main.c main.o

server.o : server.c
	gcc -c server.c server.o

clean :
	rm *.o ServerProgram
