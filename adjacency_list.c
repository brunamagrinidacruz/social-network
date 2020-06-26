#include "adjacency_list.h"
#include "list.h"

/**
 * Vértices 
 *     (USER)    (index)
 * [0] Magrini -> 1, 2 
 * [1] Marlon  -> 0, 2
 * [2] Feliz   -> 0, 1
*/

/*!< Essa struct representa cada vértice */
typedef struct node_ NODE;
struct node_ {
    USER* user;
    LIST* adjacency_list; 
    NODE* next;
};

/**
 * A escolha de uma lista de adjacência ao invés de uma matriz de adjacência foi devido aos seguintes fatores:
 * - Não sabiamos a priori quantos usuários a rede social teria, e a matriz de adjacência ocupa O(|V|^2) de espaço,
 * enquanto a lista de adjacência ocupa apenas O(|V|+|A|);
 * - A lista de adjacência possui complexidade O(|V|+|A|) para processar todo o grafo, enquanto a matriz de adjacência
 * possui complexidade O(|V|^2).  Desta forma, a lista de adjacência é melhor para o processo 
 * "identificar as pessoas com perfil 'extrovertido, ...." pois neste caso é preciso analisar todo o grafo
 * - Para o tópico "detectar pessoas na lista de contatos..." a lista de adjacências também é uma melhor escolha,
 * pois ela apenas olha a lista de adjacência do grafo O(grau do vértice), enquanto na matriz de adjacência deveria 
 * ser olhado todo os |V| vértices na matriz relacionados com o vértice, ou seja O(|V|)
*/
struct graph_ {
    int number_of_vertices;
    NODE* head;
    NODE* foot;
};

GRAPH* graph_create() {
    int i;
    GRAPH* graph;
    graph = (GRAPH *) malloc(sizeof(GRAPH));
    if(graph != NULL) {
        graph->number_of_vertices = 0;
        graph->head = (NODE*) malloc(sizeof(NODE));
        if(graph->head != NULL) {
            /*!< Por ser o nó cabeça, não possue dados */
            graph->head->user = NULL;
            graph->head->adjacency_list = NULL;
            graph->head->next = NULL;
        }
        graph->foot = graph->head; 
    }
    return graph;
}

void graph_delete(GRAPH** graph) {
    if(graph != NULL) {
        int i;
        NODE* current = (*graph)->head;
        NODE* next;
        while(current != NULL) {
            next = current->next;
            list_delete(current->adjacency_list);
            if(current->user != NULL) 
                free(current->user);
            free(current);
            current = next;
        }
        free(*graph);
        graph = NULL;
    }
    return;
}

void graph_insert(GRAPH* graph, int convergent, int divergent) {
    if(graph != NULL) {
        list_insert(graph->adjacency_list[convergent], divergent); 
        list_insert(graph->adjacency_list[divergent], convergent); 
    }
    return;
}

void graph_remove(GRAPH* graph, int convergent, int divergent) {
    if(graph != NULL) {
        list_remove(graph->adjacency_list[convergent], divergent); 
        list_remove(graph->adjacency_list[divergent], convergent); 
    }
    return;
}

int graph_number_of_vertices(GRAPH* graph) {
    if(graph != NULL) {
        return graph->number_of_vertices;
    }
}

void graph_print_element(GRAPH* graph, int vertex, int adjacent_vertex) {
     if(graph != NULL) {
        return list_print_no(graph->adjacency_list[vertex], adjacent_vertex);
    }
}

int graph_is_adjacency_list_empty(GRAPH* graph, int vertex) {
    if(graph != NULL) {
        return list_size(graph->adjacency_list[vertex]) == 0;
    }
}

int graph_first_vertex_list_adjacency(GRAPH* graph, int vertex) {
    if(graph != NULL) {
        return list_first_element(graph->adjacency_list[vertex]);
    }
}

int graph_next_vertex_list_adjacency(GRAPH* graph, int vertex, int *current_vertex, int *next_vertex) {
    if(graph != NULL) {
        return list_next_element(graph->adjacency_list[vertex], current_vertex, next_vertex);
    }
}

void graph_print(GRAPH* graph) {
    if(graph != NULL) {
        int i;
        for(i = 0; i < graph->number_of_vertices; i++) {
            printf("%d: ", i);
            list_print(graph->adjacency_list[i]);
        }
        printf("\n");
    }
    return;
}