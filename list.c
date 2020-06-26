#include "list.h"

#define MAX_SIZE_USERNAME 20
#define MAX_SIZE_GENDER 10 /*!< 'masculino' ou 'feminino' */
#define MAX_SIZE_WORD 64

typedef struct user_ {
    char username[MAX_SIZE_USERNAME];
    char gender[MAX_SIZE_GENDER];
    int age;
    /*!< Opções favoritas */
    char movie[MAX_SIZE_WORD];
    char place[MAX_SIZE_WORD];
    char book[MAX_SIZE_WORD];
    char hobby[MAX_SIZE_WORD];
    char sport[MAX_SIZE_WORD];
} USER;

typedef struct node_ NODE;

struct node_ {
    USER* user;
    NODE* next;
};

struct list_ {
    int size;
    NODE* head;
    NODE* foot;
};

NODE* node_create(USER* user) {
    NODE* node = (NODE *) malloc (sizeof(NODE));
    if(node != NULL) {
        node->user = user;
        node->next = NULL;
    }
    return node;
}

LIST* list_create() {
    LIST* list;
    list = (LIST *) malloc(sizeof(LIST));
    if(list != NULL) {
        list->size = 0;
        list->head = node_create(NULL);
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
            if(current->user != NULL)
                free(current->user);
            free(current);
            current = next;
        }
        free(*list);
        list = NULL;
    }
    return;
}

void list_insert(LIST* list, USER* user) {
    if(list != NULL) {
        NODE* aux = list->head->next;
        while(aux != NULL) {
            if(aux->user->username == user->username) return;
            aux = aux->next;
        }
        NODE* new = no_create(user);
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
            printf("%s ", aux->user->username);
            aux = aux->next;
        }
        printf("\n");       
    }
    return;
}