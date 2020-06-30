all: main

run: main
	./main

main: queue.o user.o list.o adjacency_list.o algorithms.o main.o
	gcc -g queue.o user.o list.o adjacency_list.o algorithms.o main.o -o main

main.o: main.c
	gcc -g main.c -c

algorithms.o: algorithms.c
	gcc -g algorithms.c -c

adjacency_list.o: adjacency_list.c
	gcc -g adjacency_list.c -c

list.o: list.c
	gcc -g list.c -c

user.o: user.c
	gcc -g user.c -c

queue.o: queue.c
	gcc -g queue.c -c