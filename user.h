#ifndef USER_H
    #define USER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define AMOUNT_USER_PARAMETERS 5
    #define MAX_SIZE_USERNAME 20
    #define MAX_SIZE_GENDER 10 /*!< 'masculino' ou 'feminino' */
    #define MAX_SIZE_WORD 64

    typedef struct user_ USER;

    USER* user_create(char username[MAX_SIZE_USERNAME], char gender[MAX_SIZE_GENDER], int age, char movie[MAX_SIZE_WORD], char place[MAX_SIZE_WORD], char book[MAX_SIZE_WORD], char hobby[MAX_SIZE_WORD], char sport[MAX_SIZE_WORD]);
    
    float affinity(USER* user1, USER* user2);
    
    char* user_username(USER* user);
    int user_age(USER* user);
    char* user_gender(USER* user);
    char* user_movie(USER* user);
    char* user_place(USER* user);
    char* user_book(USER* user);
    char* user_hobby(USER* user);
    char* user_sport(USER* user);

    void user_print(USER* user);
    void user_delete(USER** user);

#endif