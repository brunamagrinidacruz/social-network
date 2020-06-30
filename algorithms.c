#include "algorithms.h"

typedef enum {
    white, grey, black
} colors;

void execute_bfs(GRAPH* graph, int vertex, int distancy[], int ancestor[], colors color[]) {
    //Creating a queue that will stored the adjacents vertex in sequence of visited. 
    //The BFS will be execute to all vertex inside the queue
    QUEUE* queue;
    queue = queue_create();

    //Initializing vertex as grey (visited)
    color[vertex] = grey;
    //Because this vertex is the initial vertex, distancy = 0
    distancy[vertex] = 0;

    queue_insert(queue, vertex);

    int current_vertex = -1, next_vertex = -1;

    //While queue is not empty, there is still vertex to be visited
    while(!queue_is_empty(queue)) {
        int initial_vertex = queue_remove(queue);
        //Verify if there is vertex in adjacency list
        if(!graph_is_adjacency_list_empty(graph, initial_vertex)) {
            int first_vertex_list_adjacency = graph_first_vertex_list_adjacency(graph, initial_vertex);
            int is_end_vertex_list_adjacency = 0;
            //We also initializing the next_vertex as the first vertex of the list,
            //This because the function graph_next_vertex_list_adjacency will put the next_vertex in current_vertex
            next_vertex = first_vertex_list_adjacency;
            //While the adjacency list of the vertex doesn't end, continue to visited their adjacencys
            while(!is_end_vertex_list_adjacency) {
                //This function will put in current_vertex the id of the vertex we are analizing
                //And in next_vertex, it will put the value of the next_vertex to be executed
                is_end_vertex_list_adjacency = graph_next_vertex_list_adjacency(graph, initial_vertex, &current_vertex, &next_vertex);
                if(color[current_vertex] == white) {
                    //It's visited and now we have to put in queue to be processed
                    color[current_vertex] = grey;
                    distancy[current_vertex] = distancy[initial_vertex] + 1;
                    ancestor[current_vertex] = initial_vertex;
                    queue_insert(queue, current_vertex);
                    printf("vertex: %d | distancy: %d | ancestor: %d\n", current_vertex, distancy[current_vertex], ancestor[current_vertex]);
                }
            }
        }
        //When all vertices in adjacency list are executed (or if there is no adjacency vertext)
        color[initial_vertex] = black;
    }
    queue_delete(&queue);
}

void bfs(GRAPH* graph) {
    int i;
    int vertex;
    int number_of_vertices = graph_number_of_vertices(graph);
    int *distancy, *ancestor;
    colors *color;
    distancy = (int*) malloc (sizeof(int) * number_of_vertices);
    ancestor = (int*) malloc (sizeof(int) * number_of_vertices);
    color = (colors*) malloc (sizeof(colors) * number_of_vertices);

    //Initializing
    //color: as white because any vertex was visited
    //distancy: as -1 because any vertex had its distancy calculeted
    //ancestor: as -1 because any vertex has a ancestor yet
    for(i = 0; i < number_of_vertices; i++) {
        color[i] = white;
        distancy[i] = -1;
        ancestor[i] = -1;
    }

    //Verifing if some vertex is still white. If it's, execute bfs to it
    for(i = 0; i < number_of_vertices; i++) {
        if(color[i] == white)
            execute_bfs(graph, i, distancy, ancestor, color);
    }

    free(distancy);
    free(ancestor);
    free(color);
}