OBJS  = main.o errorFuncs.o essentials.o
OUT	  = tema3
FLAGS = -c -Wall -g

build: $(OBJS)
	gcc $(FLAGS) main.c
	gcc $(FLAGS) errorFuncs.c
	gcc $(FLAGS) essentials.c
	gcc $(OBJS) -o $(OUT)
	touch tema3.out

debug: $(OBJS)
	gcc $(FLAGS) main.c -D DEBUG=1
	gcc $(FLAGS) errorFuncs.c -D DEBUG=1
	gcc $(FLAGS) essentials.c -D DEBUG=1
	gcc $(OBJS) -o $(OUT)
	touch tema3.out
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 ./tema3 1

# debug 2 e ca debug 1 doar ca argumentul e 2
debug2: $(OBJS)
	gcc $(FLAGS) main.c -D DEBUG=1
	gcc $(FLAGS) errorFuncs.c -D DEBUG=1
	gcc $(FLAGS) essentials.c -D DEBUG=1
	gcc $(OBJS) -o $(OUT)
	touch tema3.out
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 ./tema3 2

clean:
	rm -f $(OBJS) $(OUT)
	rm tema3.out