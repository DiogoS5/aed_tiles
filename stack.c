#include<stdio.h>
#include<stdlib.h>

#include "stack.h"

void stackPush(node** head, int line, int column){
    node* tile = (node*)calloc(sizeof(node), 1);
    //validate
    if(tile == NULL){
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
        exit(EXIT_FAILURE);
    }
    else{
        discard = *head;
        *head = (*head)->next;
        free(discard);
    }
}

void deleteStack(node** head){
    if(*head == NULL){
        printf("no stack to delete\n");
        exit(0);
    }
}