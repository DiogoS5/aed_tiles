#ifndef TILES_H
#define TILES_H

int** allocTiles(FILE* fp, int lines, int columns);

int** readTiles(FILE* fp, int lines, int columns, int** tiles);

void outputTiles(FILE* outfp, int lines, int columns, int** tiles);

void skipTiles(FILE* fp, int lines, int columns);

#endif    // TILES_H