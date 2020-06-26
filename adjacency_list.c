#include "adjacency_list.h"
#include "list.h"

/**
 * A ideia do grafo será essa:
 *     (USER)     (index do usuário)
 * [0] Magrini -> 1, 2 //Magrini está conectada com Marlon e Feliz
 * [1] Marlon  -> 0, 2 //Marlon está conectado com Magrini e Feliz
 * [2] Feliz   -> 0, 1 //Feliz está conectado com Magrini e Marlon
 * [3] Breno   -> 2    //Breno está conectado com o Feliz
 * [4] Matheus -> NULL //Matheus não está conectado com ninguém
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

NODE* node_create(USER* user) {
    NODE* node;
    node = (NODE *) malloc (sizeof(NODE));
    if(node != NULL) {
        node->user = user;
        node->adjacency_list = list_create();
        node->next = NULL;
    }
}

GRAPH* graph_create() {
    int i;
    GRAPH* graph;
    graph = (GRAPH *) malloc(sizeof(GRAPH));
    if(graph != NULL) {
        graph->number_of_vertices = 0;
        graph->head = node_create(NULL); /*!< Por ser o nó cabeça, não possue dados */
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
            list_delete(&current->adjacency_list);
            if(current->user != NULL) 
                user_delete(&current->user);
            free(current);
            current = next;
        }
        free(*graph);
        graph = NULL;
    }
    return;
}

void graph_insert_vertex(GRAPH* graph, USER* user) {
    if(graph != NULL) {
        NODE* node = node_create(user);
        graph->foot->next = node;
        graph->foot = node;
        graph->number_of_vertices++;
    }
}

 
void graph_insert_edge(GRAPH* graph, char username1[], char username2[]) {
    if(graph != NULL) {
        /*!< Procurando nó e o indice do primeiro usuário */
        NODE* node1 = graph->head->next;
        int index1 = 0;
        while(node1 != NULL) {
            if(strcmp(user_username(node1->user), username1) == 0)
                break;
            index1++;
            node1 = node1->next;
        }

        /*!< Procurando nó e o indice do segundo usuário */
        NODE* node2 = graph->head->next;
        int index2 = 0;
        while(node2 != NULL) {
            if(strcmp(user_username(node2->user), username2) == 0)
                break;
            index2++;
            node2 = node2->next;
        }

        /*!< Algum dos usuários não existe */
        if(node1 == NULL || node2 == NULL) 
            return;

        float affinity_users = affinity(node1->user, node2->user);
        list_insert(node1->adjacency_list, index2, affinity_users); 
        list_insert(node2->adjacency_list, index1, affinity_users); 
    }
    return;
}

int graph_number_of_vertices(GRAPH* graph) {
    if(graph != NULL) {
        return graph->number_of_vertices;
    }
}

void graph_print(GRAPH* graph) {
    if(graph != NULL) {
        int i;
        NODE* aux = graph->head->next;
        while(aux != NULL) {
            printf("%s: ", user_username(aux->user));
            list_print(aux->adjacency_list);
        }
        printf("\n");
    }
    return;
}