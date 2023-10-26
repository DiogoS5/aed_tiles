#ifndef TILES_H
#define TILES_H

int** allocTiles(int lines, int columns);

int** readTiles(FILE* fp, int lines, int columns, int** tiles);

int** copyTiles(int lines, int columns, int** tiles);

void skipTiles(FILE* fp, int lines, int columns);

#endif