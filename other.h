#ifndef OTHER_H
#define OTHER_H

#include "stack.h"

void mode1(FILE* outfp, int** tiles, int lines, int columns);
board* play(board* board, int play_l, int play_c, int lines, int columns);
node* findPlays(int** tiles, int lines, int columns);

#endif