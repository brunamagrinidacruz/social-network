#include "user.h"

struct user_ {
    char username[MAX_SIZE_USERNAME];
    char gender[MAX_SIZE_GENDER];
    int age;
    /*!< Opções favoritas */
    char movie[MAX_SIZE_WORD];
    char place[MAX_SIZE_WORD];
    char book[MAX_SIZE_WORD];
    char hobby[MAX_SIZE_WORD];
    char sport[MAX_SIZE_WORD];
};

USER* user_create(char username[MAX_SIZE_USERNAME], char gender[MAX_SIZE_GENDER], int age, char movie[MAX_SIZE_WORD], char place[MAX_SIZE_WORD], char book[MAX_SIZE_WORD], char hobby[MAX_SIZE_WORD], char sport[MAX_SIZE_WORD]) {
    USER* user = (USER*) malloc(sizeof(USER));
    if (user != NULL) {
        user->age = age;
        strcpy(user->username, username);
        strcpy(user->gender, gender);
        strcpy(user->movie, movie);
        strcpy(user->place, book);
        strcpy(user->book, book);
        strcpy(user->hobby, hobby);
        strcpy(user->sport, sport);
    }
    return user;
}

/**
 * Calcula a porcentagem de afinidade.
*/
float affinity(USER* user1, USER* user2) {
    int similar_preferences = 0;
    
    if(strcmp(user1->movie, user2->movie) == 0)
        similar_preferences++;

    if(strcmp(user1->place, user2->place) == 0)
        similar_preferences++;

    if(strcmp(user1->book, user2->book) == 0)
        similar_preferences++;

    if(strcmp(user1->hobby, user2->hobby) == 0)
        similar_preferences++;

    if(strcmp(user1->sport, user2->sport) == 0)
        similar_preferences++;

    return (similar_preferences*100)/AMOUNT_USER_PARAMETERS;
}

int user_age(USER* user) {
    if (user != NULL) 
        return user->age;
    return -1;
}

char* user_username(USER* user) {
    if (user != NULL) 
        return user->username;
    return NULL;
}

char* user_gender(USER* user) {
    if (user != NULL) 
        return user->gender;
    return NULL;
}

char* user_movie(USER* user) {
    if (user != NULL) 
        return user->movie;
    return NULL;
}

char* user_place(USER* user) {
    if (user != NULL) 
        return user->place;
    return NULL;
}

char* user_book(USER* user) {
    if (user != NULL) 
        return user->book;
    return NULL;
}

char* user_hobby(USER* user) {
    if (user != NULL) 
        return user->hobby;
    return NULL;
}

char* user_sport(USER* user) {
    if (user != NULL) 
        return user->sport;
    return NULL;
}

void user_print(USER* user) {
    if (user != NULL) 
        printf("username: %s,\ngender: %s,\nage: %d,\nmovie: %s,\nplace: %s,\nbook: %s,\nhobby: %s,\nsport: %s.\n", user->username, user->gender, user->age, user->movie, user->place, user->book, user->hobby, user->sport);
    return;
}

void user_delete(USER** user) {
    if (user != NULL) {
        free(user);
        user = NULL;
    }
    return;
}