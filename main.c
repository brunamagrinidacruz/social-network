#include <stdio.h>
#include <stdlib.h>
#include "adjacency_list.h"

int main(void) {

    GRAPH* graph = graph_create();

    USER* magrini = user_create("Bruna\0", "feminino\0", 19, "barbie\0", "bar do zé\0", "1984\0", "cinema\0", "corrida\0");
    USER* marlon = user_create("Marlon\0", "masculino\0", 19, "vingadores\0", "praça xv\0", "feliz ano velho\0", "leitura\0", "ping pong\0");
    USER* feliz = user_create("Feliz\0", "masculino\0", 21, "barbie\0", "usp\0", "design is my passion\0", "lol\0", "lol\0");

    graph_insert_vertex(graph, magrini);
    graph_insert_vertex(graph, marlon);
    graph_insert_vertex(graph, feliz);

    graph_insert_edge(graph, "Bruna\0", "Marlon\0");
    graph_insert_edge(graph, "Bruna\0", "Feliz\0");

    graph_print(graph);

    graph_delete(&graph);
    
    return 0;
}