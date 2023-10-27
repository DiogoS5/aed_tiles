#include<stdio.h>
#include<stdlib.h>

#include "stack.h"

void stackPush(node** head, int line, int column){
    node* tile = (node*)calloc(1, sizeof(node));
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

void printStack(FILE* outfp, node* head){
    node* aux = head;
    while(aux != NULL){
        fprintf(outfp, "%d %d\n", aux->l + 1, aux->c + 1);
        aux = aux->next;
    }
    fprintf(outfp, "\n");
    free(aux);
}

int copyReversedStack(node* original, node** reversed) {
    int plays_counter = 0;
    // Iterate through the source stack and push its elements onto the reversed stack
    while (original != NULL) {
        stackPush(reversed, original->l, original->c);
        original = original->next;
        plays_counter++;
    }

    return plays_counter;
}


