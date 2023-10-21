#include<stdio.h>
#include<stdlib.h>

#include "list.h"

node* addToList(node* curr, int line, int column){
    node* block = (node*)calloc(sizeof(node), 1);
    //validate
    if(block == NULL){
        exit(EXIT_FAILURE);
    }

    block->l = line;
    block->c = column;
    if(curr == NULL){
        curr = block;
    }
    else{
        curr->next = block;
        curr = block;
    }

    return curr;
}

void printList(FILE* outfp, node* head){
    node* aux = (node*)calloc(sizeof(node), 1);
    aux = head;
    while(aux != NULL){
        fprintf(outfp, "%d %d\n", aux->l + 1, aux->c + 1);
        aux = aux->next;
    }
    fprintf(outfp, "\n");
    free(aux);
}

void deleteList(node* head){
    while(head != NULL){
        node* aux = head;
        head = head->next;
        free(aux);
    }
}