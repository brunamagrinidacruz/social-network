#ifndef ADJACENCY_LIST_H 
    #define ADJACENCY_LIST_H

    #include <stdlib.h>
    #include <string.h>
    #include "user.h"

    typedef struct graph_ GRAPH;

    GRAPH* graph_create();
    void graph_delete(GRAPH** graph);

    void graph_insert(GRAPH* graph, int convergent, int divergent);
    
    int graph_number_of_vertices(GRAPH* graph);
    void graph_print(GRAPH* graph);
    
#endif