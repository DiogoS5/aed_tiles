#include<stdio.h>
#include<stdlib.h>

#include "stack.h"

void stackPush(node** head, int line, int column){
    node* tile = (node*)calloc(1, sizeof(node));
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


/*********************************
 * Argumentos: head, counter, value.
 * head é a cabeça da lista, counter dá o número de ocorrências e value é o número lido 
 * 
 * DESCRIÇÃO: Esta função recebe o value e o counter e procura na stack se o value já exista,
 * incrementa o número de ocorrências com o valor do counter, caso não exista adiciona à stack
 * o novo value e dá-lhe o número de ocorrência igual ao counter
 * *********************************/
void stackPushOccurrences(occurrences **head, int counter, int value){
    int valueFound = 0;
    /*Procura se o número já existe na stack*/
    occurrences* current = *head;
    while (current != NULL) {
        if (current->number == value) {
            current->counter += counter;
            valueFound = 1;
            break; // Valor encontrado e atualizado, sai da função
        }
        current = current->next;
    }

    if (!valueFound){
        /*Se não existir o número adiciona à stack*/
        occurrences* num_occcurr = (occurrences*)calloc(1, sizeof(occurrences));
        if(num_occcurr == NULL){
            exit(EXIT_FAILURE);
        }

        num_occcurr->counter = counter;
        num_occcurr->number = value;

        if(*head == NULL){   
            *head = num_occcurr; //new head
        }
        else{
            num_occcurr->next = *head;
            *head = num_occcurr; //replaces head
        }
    }
}

int score(occurrences* head) {
    int score = 0;
    occurrences* current = head;
    while (current != NULL) {
        score += current->counter * (current->counter - 1);
        current = current->next;
        
    }
    return score;
}

void deleteStackOccurrences(occurrences** head) {
    while (*head != NULL) {
        occurrences* aux = *head;
        *head = (*head)->next;
        free(aux);
    }
}

void deleteStack(node** head) {
    while (*head != NULL) {
        node* aux = *head;
        *head = (*head)->next;
        free(aux);
    }
}