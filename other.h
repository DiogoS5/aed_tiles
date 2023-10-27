#ifndef OTHER_H
#define OTHER_H

#include "stack.h"

void mode1(FILE* outfp, int** tiles, int lines, int columns);
board* play(board* board, node* play, int lines, int columns);
node* findPlays(int** tiles, int lines, int columns);
void mode2(FILE* outfp, int** tiles, int lines, int columns, int min_score);

#endif