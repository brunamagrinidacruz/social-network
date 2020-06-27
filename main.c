#include <stdio.h>
#include <stdlib.h>
#include "adjacency_list.h"

#define END 0
#define SEND_INVITE 1
#define FRIENDSHIP_SUGGESTION 2
#define DETECT_LOW_AFFINITY 3
#define IDENTIFY_USER_PROFILE 4

void print_menu() {
    printf("------------------------------------\n");
    printf("%d - Enviar convite\n", SEND_INVITE);
    printf("%d - Sugestão de 'amigos de verdade'\n", FRIENDSHIP_SUGGESTION);
    printf("%d - Detectar baixa afinidade\n", DETECT_LOW_AFFINITY);
    printf("%d - Identificar perfil dos usuários\n", IDENTIFY_USER_PROFILE);
    printf("%d - Sair\n", END);
    printf("------------------------------------\n");
}

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

    int operation;
    print_menu();
    scanf("%d", &operation);

    while(operation != END) {
        switch(operation) {
            case SEND_INVITE:
                printf("1\n");
                break;
            case FRIENDSHIP_SUGGESTION:
                printf("2\n");
                break;
            case DETECT_LOW_AFFINITY:
                printf("3\n");
                break;
            case IDENTIFY_USER_PROFILE:
                printf("4\n");
                break;
            case END:
                printf("Até a próxima!\n");
                break;
            default:
                printf("Operação inválida!\n");
        }
        print_menu();
        scanf("%d", &operation);
    }

    graph_delete(&graph);
    
    return 0;
}