#include<stdio.h>
#include<stdlib.h>

#include "board_stack.h"

void boardPush(board** head, int** tiles, int score, int play[], node* possible_plays){
    board* new_board = (board*)calloc(sizeof(board), 1);
    //validate
    if(new_board == NULL){
        printf("allocation error push");
        exit(EXIT_FAILURE);
    }

    new_board->tiles = tiles;
    new_board->score = score;
    new_board->play[0] = play[0];
    new_board->play[1] = play[1];
    new_board->possible_plays = possible_plays;

    if(*head == NULL){   
        *head = new_board; //new head
    }
    else{
        new_board->next = *head;
        *head = new_board; //replaces head
    }
}

void boardPop(board** head){
    board *discard;
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

void deleteBoardStack(board** head){
    if(*head == NULL){
        printf("no stack to delete\n");
        exit(0);
    }
}