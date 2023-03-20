OBJS	= tema1.o list.o operation.o
SOURCE	= tema1.c list.c operation.c
HEADER	= list.h operation.h
OUT	= tema1
FLAGS	 = -c -Wall

build: $(OBJS)
	gcc -g $(FLAGS) tema1.c
	gcc -g $(FLAGS) list.c
	gcc -g $(FLAGS) operation.c
	gcc -g $(OBJS) -o $(OUT)

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)