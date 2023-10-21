#include<stdio.h>
#include<stdlib.h>

#include "stack.h"

void stackPush(int line, int column){
    node* tile = (node*)calloc(sizeof(node), 1);
    //validate
    if(tile == NULL){
        fprintf(stderr, "Memory allocation error");
        exit(EXIT_FAILURE);
    }
    tile->l = line;
    tile->c = column;

    if(head == NULL){   
        head = tile; //new head
    }
    else{
        tile->next = head;
        head = tile; //replaces head
    }
}

void stackPop(){
    node *discard;
    if (head == NULL){
        fprintf(stderr, "Coudn't pop, no head");
        exit(EXIT_FAILURE);
    }
    else{
        discard = head;
        head = head->next;
        free(discard);
    }
}