#include "adjacency_list.h"
#include "list.h"

/**
 * A primeira ideia do grafo foi armazenar na aresta o indice de quem a pessoa estava relacionada.
 * Entretanto, ao fazer uma análise em uma pessoa em especifico (um vértice da lista),
 * se quisessemos obter informações sobre a pessoa com quem está conectado, seria necessário
 * percorrer a lista de usuários novamente (tendo em vista que é uma lista dinâmica)
 * para encontrar as informações da pessoa associada. Por isso, decidimos optar por em cada aresta,
 * armazenar o endereço da pessoa com quem está se relacionando.
 *     (USER)     (index do usuário)
 * [0] Magrini -> 1, 2 //Magrini está conectada com Marlon e Feliz
 * [1] Marlon  -> 0, 2 //Marlon está conectado com Magrini e Feliz
 * [2] Feliz   -> 0, 1, 3 //Feliz está conectado com Magrini e Marlon
 * [3] Breno   -> 2    //Breno está conectado com o Feliz
 * [4] Matheus -> NULL //Matheus não está conectado com ninguém
*/

/**
 * A ideia do grafo será essa:
 *     (USER)  (Endereço do usuáro)
 * Magrini -> &Marlon, &Feliz, &Matheus 
 * Marlon  -> &Magrini, &Feliz
 * Feliz   -> &Marlon, &Magrini, &Breno
 * Breno   -> &Feliz   
 * Matheus -> &Magrini
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
            if(current->adjacency_list != NULL)
                list_delete(&(current->adjacency_list));
            if(current->user != NULL) 
                user_delete(&(current->user));
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

int graph_empty(GRAPH* graph) {
    if (graph != NULL && graph->number_of_vertices > 0)
        return 0;
    return 1;
}
 
NODE* graph_search_node(GRAPH* graph, char username[]) {
    if (!graph_empty(graph)) {
        NODE* node = graph->head->next;

        while (node != NULL && strcmp(user_username(node->user), username) != 0)
            node = node->next;

        if (node != NULL)
            return node;
    }
    return NULL;
}

int graph_insert_edge(GRAPH* graph, char username1[], char username2[]) {
    if(!graph_empty(graph)) {
        /*!< Procurando nó do primeiro usuário */
        NODE* node1 = graph_search_node(graph, username1);

        /*!< Procurando nó do segundo usuário */
        NODE* node2 = graph_search_node(graph, username2);

        /*!< Algum dos usuários não existe */
        if(node1 == NULL || node2 == NULL) 
            return 0;

        if (list_search_user(node1->adjacency_list, node2->user)) {
            printf("Os usuários já são amigos.\n");
            return 1;
        }

        float affinity_users = affinity(node1->user, node2->user);
        int request;

        printf("A chance dessa amizade ser verdadeira é de %.2f%% e ", affinity_users);
        if(affinity_users >= TRUE_FRIENDSHIP) 
            printf("por isso recomendamos vocês se tornarem amigos e se conheçam melhor!\n");
        else
            printf("por isso não recomendamos vocês se tornarem amigos. Você pode verificar as sugestões de possíveis novos 'amigos de verdade'.\n");
        printf("O usuário %s deseja aceitar a solicitação? (1 - Sim, 0 - Não): ", username2);
        scanf("%d", &request);

        if (!request) {
            printf("Amizade recusada.\n");
        } else {
            /*!< Verificando se a nova amizade foi realizada com sucesso */
            if (!list_insert(node1->adjacency_list, node2->user, affinity_users) || !list_insert(node2->adjacency_list, node1->user, affinity_users)) 
                return 0;
            printf("Amizade feita com sucesso.\n");
        }
        return 1;
    }
    return 0;
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
            printf("Lista de amizade do usuário %s:\n", user_username(aux->user));
            if(!list_print(aux->adjacency_list))
                printf("  Nenhuma amizade.\n");
            aux = aux->next;
            printf("\n");
        }
    }
    return;
}

void graph_print_users(GRAPH* graph) {
    if (!graph_empty(graph)) {
        NODE* node = graph->head->next;

        while (node != NULL) {
            printf("Nome do usuário: %s\n", user_username(node->user));
            node = node->next;
        }
    }
    return;
}

int graph_friendship_suggestion(GRAPH* graph) {
    if (!graph_empty(graph)) {
        int n_friendship;
        float affinity_users;
        NODE* node = graph->head->next;
        NODE* node_possible_friend;

        while (node != NULL) {
            printf("Sugestão de amizadade verdadeira para o usuário %s:\n", user_username(node->user));
            n_friendship = 0;
            node_possible_friend = graph->head->next;
            while (node_possible_friend != NULL) {
                if (!list_search_user(node->adjacency_list, node_possible_friend->user) && node_possible_friend != node) {
                    affinity_users = affinity(node->user, node_possible_friend->user);
                    if (affinity_users >= TRUE_FRIENDSHIP) {
                        printf("  %s, afinidade = %.2f%%\n\n", user_username(node_possible_friend->user), affinity_users);
                        n_friendship++;
                    }
                }
                node_possible_friend = node_possible_friend->next;
            }

            if (n_friendship == 0)
                printf("  Nenhuma sugestão de amizade verdadeira.\n\n");

            node = node->next;
        }

        return 1;
    }
    return 0;
}

int graph_detect_low_affinity(GRAPH* graph) {
    if (!graph_empty(graph)) {
        NODE* node = graph->head->next;

        while (node != NULL) {
            printf("Amizades de baixa afinidade do usuário %s:\n", user_username(node->user));
            if(!list_friendship_low_affinity(node->adjacency_list, node->user))
                printf("  Nenhuma amizade de baixa afinidade.\n");
            printf("\n");
            node = node->next;
        }

        return 1;
    }
    return 0;
}

/**
 * Função que analisa o perfil dos usuários que estão no grafo.
 * Recebe como parametro o grafo a ser analisado.
*/
int graph_identify_user_profile(GRAPH* graph) {
    if(!graph_empty(graph)) {
        NODE* node = graph->head->next;
        /*!< Percorrendo entre todos os vértices do grafo */
        while(node != NULL) {
            printf("O usuário %s é ", user_username(node->user));
            /*!< Analisando se o usuário é 'extrovertido' ou 'introverdo'*/
            list_identify_user_profile(node->adjacency_list);
            node = node->next;
        }

        return 1;
    }
    return 0;
}