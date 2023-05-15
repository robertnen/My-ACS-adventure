OBJS  = main.o essentials.o treeFunc.o
OUT	  = quadtree
FLAGS = -c -Wall -g

build: $(OBJS)
	gcc $(FLAGS) main.c
	gcc $(FLAGS) essentials.c
	gcc $(FLAGS) treeFunc.c
	gcc $(OBJS) -o $(OUT)

clean:
	rm -f $(OBJS) $(OUT)