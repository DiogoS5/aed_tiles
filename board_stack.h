#ifndef BOARDS_STACK_H
#define BOARDS_STACK_H

#include "list.h"

typedef struct _board {
    int** tiles;
    int score;      //current score
    int play[2];        //play that led to this board been created
    node* possible_plays;        //list of possible plays
    struct _board *next;
} board;

void boardsPush(board** head, int** tiles, int score, int play);

void boardsPop(board** head);

void boardsStack(board** head);

#endif