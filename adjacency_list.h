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
    void graph_print_details(GRAPH* graph);

    int graph_search_index(GRAPH* graph, char username[]);

    int graph_friendship_suggestion(GRAPH* graph);
    int graph_detect_low_affinity(GRAPH* graph);
    int graph_identify_user_profile(GRAPH* graph);

    int graph_is_adjacency_list_empty(GRAPH* graph, int vertex);
    int graph_first_vertex_list_adjacency(GRAPH* graph, int vertex);
    int graph_next_vertex_list_adjacency(GRAPH* graph, int vertex, int *current_vertex, int *next_vertex);
    
#endif