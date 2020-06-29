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

/*
 * Função que imprime os usuários de baixa afinidade dado uma lista e um usuário para ter como comparação.
 */
int list_friendship_low_affinity(LIST* list, USER* user) {
    if (!list_empty(list)) {
        float affinity_users;
        int n_friendship_low_affinity = 0; /*!< número de amizade de baixa afinidade */
        NODE* node = list->head->next;

        while (node != NULL) {
            affinity_users = affinity(node->user, user);
            /*!< se afinididade < amizade verdadeira (60.00%) */
            if (affinity_users < TRUE_FRIENDSHIP) {
                printf("  %s, afinidade: %.2f%%\n", user_username(node->user), affinity_users);
                n_friendship_low_affinity++;
            }
            node = node->next;
        }

        return n_friendship_low_affinity;
    }
    return 0;
}