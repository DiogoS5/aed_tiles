#include<stdio.h>
#include<stdlib.h>

#include "reading.h"

int** allocTiles(int lines, int columns){
    int** tiles = (int**)calloc(lines, sizeof(int*)); //alloc lines

    for (int l = 0; l < lines; l++){
        tiles[l] = (int*)calloc(columns, sizeof(int)); //alloc columns
    }

    if (tiles == NULL) { //validate allocation
        exit(EXIT_FAILURE);
    }

    return tiles;
}

int** readTiles(FILE* fp, int lines, int columns, int** tiles){
    for(int l = lines - 1; l >= 0; l--){
        for(int c = 0; c < columns; c++){
            if(fscanf(fp, "%d", &tiles[l][c]) != 1){
                exit(EXIT_FAILURE);
            }
        }
    }
    return tiles;
}

int** copyTiles(int lines, int columns, int** tiles){
    int** new_tiles = allocTiles(lines, columns);
    for(int l = lines - 1; l >= 0; l--){
        for(int c = 0; c < columns; c++){
            new_tiles[l][c] = tiles[l][c];
        }
    }
    return new_tiles;
}

void skipTiles(FILE* fp, int lines, int columns){
    int discard;
    for(int l=0; l < lines; l++){
        for(int c=0; c < columns; c++){
            if(fscanf(fp, "%d", &discard) != 1){
                exit(EXIT_FAILURE);
            }
        }
    }
}