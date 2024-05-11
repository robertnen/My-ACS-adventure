CFLAGS = -Wall -std=c11 -lm

build: server subscriber

subscriber: client.c
	gcc client.c -o subscriber $(CFLAGS)

server: server.c
	gcc server.c -o server $(CFLAGS)

clean:
	rm -f server subscriber
