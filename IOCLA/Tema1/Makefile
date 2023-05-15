CC = gcc
CFLAGS = -Wall -g

build: main

main: main.o operations.o myFunc.o sensorOperations.o
	$(CC) -o main $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

operations.o: operations.c
	$(CC) $(CFLAGS) -c $^

myFunc.o: myFunc.c
	$(CC) $(CFLAGS) -c $^

sensorOperations.o: sensorOperations.c
	$(CC) $(CFLAGS) -c $^

run: build
	./main

clean:
	rm -f *.o main