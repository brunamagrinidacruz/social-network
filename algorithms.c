#include "algorithms.h"

typedef enum {
    white, grey, black
} colors;

void execute_bfs(GRAPH* graph, int vertex, int distancy[], int ancestor[], colors color[]) {
    /*!< Fila que irá armazenar os vértices na sequência que foram visitados */
    QUEUE* queue;
    queue = queue_create();

    /*!< Inicializando vértice como "grey" (visitado) */
    color[vertex] = grey;
    /*!< Por ser o vértice inicial, a distância é 0 */
    distancy[vertex] = 0;

    queue_insert(queue, vertex);
    
    int current_vertex = -1, next_vertex = -1;

    while(!queue_is_empty(queue)) {
        int initial_vertex = queue_remove(queue);
        /*!< Verificando se há vértices na lista de adjacência */
        if(!graph_is_adjacency_list_empty(graph, initial_vertex)) {
            int first_vertex_list_adjacency = graph_first_vertex_list_adjacency(graph, initial_vertex);
            int is_end_vertex_list_adjacency = 0;
            /*!< Inicializando o next_vertex como o primeiro vértice pois a graph_next_vertex_list_adjacency irá colocar ele no current_vertex */
            next_vertex = first_vertex_list_adjacency;
            /*!< Enquanto a lista de adjacência do vértice não termina, continua visitando seus vértices adjacentes */
            while(!is_end_vertex_list_adjacency) {
                /*!< Colocando o próximo vértice da lista de adjacência em next_vertex e o vértice a ser executado em current_vertex */
                is_end_vertex_list_adjacency = graph_next_vertex_list_adjacency(graph, initial_vertex, &current_vertex, &next_vertex);
                if(color[current_vertex] == white) {
                    /*!< Como foi visitado, armazena na lista para ser processado */
                    color[current_vertex] = grey;
                    distancy[current_vertex] = distancy[initial_vertex] + 1;
                    ancestor[current_vertex] = initial_vertex;
                    queue_insert(queue, current_vertex);
                }
            }
        }

        /*!< Quando todos os vértices adjacentes foram executados (ou se não há vértices adjacentes), o vértice foi processado */
        color[initial_vertex] = black;
    }
    queue_delete(&queue);
}

/**
 * Recebe como parametro um grafo e dois nomes de usuários.
 * Calcula a distância entre os dois usuários.
*/
int bfs(GRAPH* graph, char username1[], char username2[]) {

    if(strcmp(username1, username2) == 0) {
        printf("O usuário está conectado com si mesmo!\n");
        return 1;
    }

    /*!< Posição do usuário1 na lista de adjacência */
    int index_source = graph_search_index(graph, username1);
    /*!< Posição do usuário2 na lista de adjacência */
    int index_target = graph_search_index(graph, username2);

    if(index_source == -1 || index_target == -1)
        return 0;

    int i;
    int vertex;
    int number_of_vertices = graph_number_of_vertices(graph);
    int *distancy, *ancestor;
    colors *color;
    distancy = (int*) malloc (sizeof(int) * number_of_vertices);
    ancestor = (int*) malloc (sizeof(int) * number_of_vertices);
    color = (colors*) malloc (sizeof(colors) * number_of_vertices);

    /**
     * Inicializando
     * color: como "white" porque nenhum vértice foi visitado
     * distancy: como -1 porque nenhum vértice teve a distância calculada
     * ancestor: como -1 porque nenhum vértice tem um ancestral ainda
    */
    for(i = 0; i < number_of_vertices; i++) {
        color[i] = white;
        distancy[i] = -1;
        ancestor[i] = -1;
    }

    execute_bfs(graph, index_source, distancy, ancestor, color);

    if(distancy[index_target] == -1)
        printf("O usuário %s não possui um laço com o usuário %s.\n", username1, username2);
    else if(distancy[index_target] == 1)
        printf("Os usuários são amigos!\n");
    else
        printf("A distância entre o usuário %s e o usuário %s é de %d.\n", username1, username2, distancy[index_target]);
    
    free(distancy);
    free(ancestor);
    free(color);
    return 1;
}