#ifndef ADJACENCY_LIST_H 
    #define ADJACENCY_LIST_H

    #include <stdlib.h>

    typedef struct graph_ GRAPH;

    #define MAX_SIZE_USERNAME 20
    #define MAX_SIZE_GENDER 10 /*!< 'masculino' ou 'feminino' */
    #define MAX_SIZE_WORD 64

    typedef struct user_ {
        char username[MAX_SIZE_USERNAME];
        char gender[MAX_SIZE_GENDER];
        int age;
        /*!< Opções favoritas */
        char movie[MAX_SIZE_WORD];
        char place[MAX_SIZE_WORD];
        char book[MAX_SIZE_WORD];
        char hobby[MAX_SIZE_WORD];
        char sport[MAX_SIZE_WORD];
    } USER;

    GRAPH* graph_create();
    void graph_delete(GRAPH** graph);

    void graph_insert(GRAPH* graph, int convergent, int divergent);
    void graph_remove(GRAPH* graph, int convergent, int divergent);

    void graph_print_element(GRAPH* graph, int vertex, int adjacent_vertex);
    
    int graph_number_of_vertices(GRAPH* graph);
    int graph_is_adjacency_list_empty(GRAPH* graph, int vertex);
    int graph_first_vertex_list_adjacency(GRAPH* graph, int vertex);
    int graph_next_vertex_list_adjacency(GRAPH* graph, int vertex, int *current_vertex, int *next_vertex);

    void graph_print(GRAPH* graph);
    
#endif