#ifndef BOARDS_STACK_H
#define BOARDS_STACK_H

#include "list.h"

typedef struct _board {
    int** tiles;
    int score;      //current score
    node* plays;        //stack of plays that led to this board been created
    node* possible_plays;       //stack of possible plays
    struct _board *next;
} board;

board* boardAlloc(int** tiles, int score, node* plays, node* possible_plays);

void boardPush(board** head, board* board);

void boardPop(board** head, int lines);

#endif