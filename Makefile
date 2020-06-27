all: main

run: main
	./main

main: user.o list.o adjacency_list.o main.o
	gcc -g user.o list.o adjacency_list.o main.o -o main

main.o: main.c
	gcc -g main.c -c

adjacency_list.o: adjacency_list.c
	gcc -g adjacency_list.c -c

list.o: list.c
	gcc -g list.c -c

user.o: user.c
	gcc -g user.c -c