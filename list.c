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

void list_insert(LIST* list, USER* user, float weight) {
    if(list != NULL) {
        NODE* aux = list->head->next;
        while(aux != NULL) {
            if(strcmp(user_username(aux->user), user_username(user)) == 0) return;
            aux = aux->next;
        }
        NODE* new = list_node_create(user, weight);
        list->foot->next = new;
        list->foot = new;
        list->size++;
    }
    return;
}

int list_size(LIST* list) {
    if(list != NULL) {
        return list->size;
    }
}

void list_print(LIST* list) {
    if(list != NULL) {
        int i;
        NODE* aux = list->head->next;
        while(aux != NULL) {
            printf("Usuário: %s Weight: %.2f | ", user_username(aux->user), aux->weight);
            aux = aux->next;
        }      
    }
    return;
}