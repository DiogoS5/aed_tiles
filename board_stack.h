#ifndef BOARDS_STACK_H
#define BOARDS_STACK_H

#include "list.h"

typedef struct _board {
    int** tiles;
    int score;      //current score
    node* play;        //play that led to this board been created
    node* possible_plays;       //stack of possible plays
    struct _board *next;
} board;

board* boardAlloc(int** tiles, int score, node* play, node* possible_plays);

void boardPush(board** head, board* board);

board* boardPop(board** head, int lines);

#endif