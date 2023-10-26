#include<stdio.h>
#include<stdlib.h>

#include "stack.h"

void stackPush(node** head, int line, int column){
    node* tile = (node*)calloc(sizeof(node), 1);
    //validate
    if(tile == NULL){
        printf("allocation error push");
        exit(EXIT_FAILURE);
    }

    tile->l = line;
    tile->c = column;

    if(*head == NULL){   
        *head = tile; //new head
    }
    else{
        tile->next = *head;
        *head = tile; //replaces head
    }
}

void stackPop(node** head){
    node *discard;
    if (head == NULL){
        printf("no head stack");
        exit(EXIT_FAILURE);
    }
    else{
        discard = *head;
        *head = (*head)->next;
        free(discard);
    }
}
