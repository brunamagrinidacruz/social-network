#include "list.h"

typedef struct node_ NODE;

struct node_ {
    USER* user;
    float weight; /*!< Representa a afinidade em porcentagem */
    NODE* next;
};

struct list_ {
    int size;
    NODE* head;
    NODE* foot;
};

NODE* list_node_create(USER* user, float weight) {
    NODE* node = (NODE *) malloc (sizeof(NODE));
    if(node != NULL) {
        node->user = user;
        node->weight = weight;
        node->next = NULL;
    }
    return node;
}

LIST* list_create() {
    LIST* list;
    list = (LIST *) malloc(sizeof(LIST));
    if(list != NULL) {
        list->size = 0;
        list->head = list_node_create(NULL, 0);
        list->foot = list->head;
    }
    return list;
}

void list_delete(LIST** list) {
    if(list != NULL) {
        NODE* current = (*list)->head;
        NODE* next;
        while(current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
        free(*list);
        list = NULL;
    }
    return;
}

int list_insert(LIST* list, USER* user, float affinity) {
    if(list != NULL) {
        NODE* new = list_node_create(user, affinity);
        list->foot->next = new;
        list->foot = new;
        list->size++;

        return 1;
    }
    return 0;
}

int list_size(LIST* list) {
    if(list != NULL) {
        return list->size;
    }
}

int list_empty(LIST* list) {
    if (list != NULL && list->size > 0)
        return 0;
    return 1;
}

int list_print(LIST* list) {
    if(!list_empty(list)) {
        int i;
        NODE* aux = list->head->next;
        while(aux != NULL) {
            printf("  Usuário: %s com afinidade de %.2f%% \n", user_username(aux->user), aux->weight);
            aux = aux->next;
        }
        return 1;    
    }
    return 0;
}

int list_search_user(LIST* list, USER* user) {
    if (!list_empty(list)) {
        NODE* node = list->head->next;

        while (node != NULL && node->user != user)
            node = node->next;

        if (node != NULL)
            return 1;
    }
    return 0;
}

int list_friendship_low_affinity(LIST* list, USER* user) {
    if (!list_empty(list)) {
        float affinity_users;
        int n_friendship_low_affinity = 0;
        NODE* node = list->head->next;

        while (node != NULL) {
            affinity_users = affinity(node->user, user);
            if (affinity_users < TRUE_FRIENDSHIP) {
                printf("  %s, afinidade: %.2f%%\n", user_username(node->user), affinity_users);
                n_friendship_low_affinity++;
            }
            node = node->next;
        }

        return n_friendship_low_affinity;
    }
}

/**
 * Função que verifica a afinidade entre todos os amigos de um usuário
 * e determina se o usuário é 'extrovertido' ou 'introvertido'.
 * Recebe como parametro a lista de amizades do usuário a ser analisado.
 * Caracteriza-se como 'extrovertido' um usuário que possua igual ou acima de 50% de amigos com afinidade >= 60%.
 * Caracteriza-se como 'introvertido' um usuário que possua abaixo de 50% de amigos com afinidade < 60%.
*/
void list_identify_user_profile(LIST* list) {
    if(!list_empty(list)) {
        NODE* node = list->head->next;
        int amount_true_friends = 0;
        float percentage = 0;
        /*!< Percorrendo a lista de adjacência de um determinado grafo */
        while(node != NULL) {
            if(node->weight >= TRUE_FRIENDSHIP) 
                amount_true_friends++;
            node = node->next;
        }

        /**
         * node->size - 100%
         * amount_true_friends - x
         * 
         * node->size*x = 100*amount_true_friends
         * x = 100*amount_true_friends/node->size
        */
        percentage = 100*amount_true_friends/list->size;

        if(percentage >= 50) 
            printf("extroverdio.\n");
        else 
            printf("introvertido.\n");

        return;
    }

    /*!< Como o usuário não possui amigos, é introvertido */
    printf("introvertido.\n");
    return;
}