#ifndef LIST_H
    #define LIST_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "user.h"

    typedef struct list_ LIST;
    
    LIST* list_create();
    void list_delete(LIST** list);

    void list_insert(LIST* list, USER* user, float weight);

    int list_size(LIST* list);
    void list_print(LIST* list);

#endif