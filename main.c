#include <stdio.h>
#include <stdlib.h>
#include "adjacency_list.h"

#define END 0
#define SEND_INVITE 1
#define FRIENDSHIP_SUGGESTION 2
#define DETECT_LOW_AFFINITY 3
#define IDENTIFY_USER_PROFILE 4
#define PRINT_SOCIAL_NETWORK 5

#define SIZE_TEXT 64

void print_menu() {
    printf("------------------------------------\n");
    printf("%d - Enviar convite\n", SEND_INVITE);
    printf("%d - Sugestão de 'amigos de verdade'\n", FRIENDSHIP_SUGGESTION);
    printf("%d - Detectar baixa afinidade\n", DETECT_LOW_AFFINITY);
    printf("%d - Identificar perfil dos usuários\n", IDENTIFY_USER_PROFILE);
    printf("%d - Imprimir rede social\n", PRINT_SOCIAL_NETWORK);
    printf("%d - Sair\n", END);
    printf("------------------------------------\n");
}

/**
 * Função responsável por ler uma linha.
 * Recebe o arquivo que será lido 
 * e o parâmetro value que é prenchido na função com o conteúdo da linha a partir dos dois pontos (:).
 * Exemplo: caso a linha seja 'nome do usuário: beltrano', value será 'beltrano'.
*/
void read_line(FILE* file, char value[]) {
    char byte;
    int index = 0;
    int findInitValue = 0;
    while(1) {
        fread(&byte, 1, sizeof(char), file);

        if(byte == '\n') {  /*!< Encontrou o fim da linha */
            value[index] = '\0';
            break;
        }

        /**
         *  Enquanto não encontrou os dois pontos, é só o nome do campo.
         *  Quanto encontrou os dois pontos e não foi achado antes, então irá começar o valor.
         * */
        if(!findInitValue && byte == ':') {
            findInitValue = 1;
            fread(&byte, 1, sizeof(char), file); /*!< Lendo o espaço entre os dois pontos e o valor do campo */
            /*!< Se o espaço existir, ler o primeiro caractere do valor. Se não, o byte lido é o primeiro caractere do valor */
            if(byte == ' ') fread(&byte, 1, sizeof(char), file);
        }

        if(findInitValue) {
            value[index] = byte;
            index++;
        }
    }

}

/**
 * Função responsável por pular uma linha.
 * Retorna o arquivo que vai pular a linha e um inteiro que informa se o arquivo acabou ou não.
*/
int jump_line(FILE* file){
    char byte;
    return fread(&byte, 1, sizeof(char), file);
}

/**
 * Função responsável por ler o arquivo e inserir os valores iniciais no grafo.
 * Recebe como parametro o grafo onde serão inseridos os usuários.
 * O arquivo deve conter os 7 itens para cada usuário: nome, gênero, idade, filme, local, livro, hobby e esporte em ordem
 * e deve ter um espaço entre cada usuário. No usuário final, deve ter um espaço também.
 * O arquivo não pode estar vazio.
*/
void initialize_profiles(GRAPH* graph) {
    if(graph != NULL) {
        FILE* file;
        char file_name[SIZE_TEXT];
        
        USER* user;
        char username[MAX_SIZE_USERNAME];
        char gender[MAX_SIZE_GENDER];
        char age[4]; /*!< O tamanho máximo de uma idade seria 3 digitos (até 150) e mais um para o \0 */
        char movie[MAX_SIZE_WORD];
        char place[MAX_SIZE_WORD];
        char book[MAX_SIZE_WORD];
        char hobby[MAX_SIZE_WORD];
        char sport[MAX_SIZE_WORD];

        printf("Digite o nome do arquivo que contém os perfis dos usuários: ");
        scanf("%s", file_name);

        file = fopen(file_name, "r");
        
        if(file != NULL) {
            int hasRows = 1;
            while(hasRows) {
                /*!< Lendo o nome de usuário */
                read_line(file, username);
                /*!< Lendo o gênero */
                read_line(file, gender);
                /*!< Lendo a idade */
                read_line(file, age);
                /*!< Lendo o filme favorito */
                read_line(file, movie);
                /*!< Lendo o place favorito */
                read_line(file, place);
                /*!< Lendo o book favorito */
                read_line(file, book);
                /*!< Lendo o hobby favorito */
                read_line(file, hobby);
                /*!< Lendo o sport favorito */
                read_line(file, sport);
                user = user_create(username, gender, atoi(age), movie, place, book, hobby, sport);
                graph_insert_vertex(graph, user);
                hasRows = jump_line(file);
            }
        }

      fclose(file);
    }
}

int main(void) {

    GRAPH* graph = graph_create();
    char username1[MAX_SIZE_USERNAME], username2[MAX_SIZE_USERNAME];

    /*!< Ler arquivo de dados que contem os perfis */
    initialize_profiles(graph);

    int operation;
    print_menu();
    scanf("%d", &operation);

    while(operation != END) {
        switch(operation) {
            case SEND_INVITE:
                graph_print_users(graph);
                printf("Amizade entre os usuários: ");
                scanf("%s %s", username1, username2);
                if (!graph_insert_edge(graph, username1, username2))
                    printf("Falha ao fazer a amizade.\n");
                break;
            case FRIENDSHIP_SUGGESTION:
                if(!graph_friendship_suggestion(graph))
                    printf("Falha ao sugerir amidades verdadeiras.\n");
                break;
            case DETECT_LOW_AFFINITY:
                if(!graph_detect_low_affinity(graph))
                    printf("Falha ao detectar amizades de baixa afinidade.\n");
                break;
            case IDENTIFY_USER_PROFILE:
                if(!graph_identify_user_profile(graph))
                    printf("Falha ao identificar os perfils dos usuários");
                break;
            case PRINT_SOCIAL_NETWORK:
                graph_print(graph);
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