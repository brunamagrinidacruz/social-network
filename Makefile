all: main

run: main
	./main

main: user.o list.o adjacency_list.o main.o
	gcc user.o list.o adjacency_list.o main.o -o main

main.o: main.c
	gcc main.c -c

adjacency_list.o: adjacency_list.c
	gcc adjacency_list.c -c

list.o: list.c
	gcc list.c -c

user.o: user.c
	gcc user.c -c