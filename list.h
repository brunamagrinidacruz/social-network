#ifndef LIST_H
    #define LIST_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "user.h"

    typedef struct list_ LIST;
    
    LIST* list_create();
    void list_delete(LIST** list);

    int list_insert(LIST* list, USER* user, float affinity);

    int list_size(LIST* list);
    int list_print(LIST* list);

    int list_search_user(LIST* list, USER* user);

    int list_friendship_low_affinity(LIST* list, USER* user);

#endif