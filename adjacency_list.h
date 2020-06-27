#ifndef ADJACENCY_LIST_H 
    #define ADJACENCY_LIST_H

    #include <stdlib.h>
    #include <string.h>
    #include "user.h"

    typedef struct graph_ GRAPH;

    GRAPH* graph_create();
    void graph_delete(GRAPH** graph);

    void graph_insert_vertex(GRAPH* graph, USER* user);
    int graph_insert_edge(GRAPH* graph, char username1[], char username2[]);
    
    int graph_number_of_vertices(GRAPH* graph);
    void graph_print(GRAPH* graph);
    void graph_print_users(GRAPH* graph);
    
#endif