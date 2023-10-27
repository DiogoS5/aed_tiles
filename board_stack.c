#include<stdio.h>
#include<stdlib.h>

#include "board_stack.h"

board* boardAlloc(int** tiles, int score, node* possible_plays){
    board* new_board = (board*)malloc(sizeof(board));
    //validate
    if(new_board == NULL){
        printf("allocation error push");
        exit(EXIT_FAILURE);
    }

    new_board->tiles = tiles;
    new_board->score = score;
    new_board->possible_plays = possible_plays;
    new_board->next = NULL;
    return new_board;
}

void boardPush(board** head, board* board){
    if(*head == NULL){   
        *head = board; //new head
    }
    else{
        board->next = *head;
        *head = board; //replaces head
    }
}

void boardPop(board** head, int lines){
    if (head == NULL){
        printf("no head stack");
        exit(EXIT_FAILURE);
    }
    else{
        board* discard = *head;
        *head = (*head)->next;
        free(discard);
    }
}
