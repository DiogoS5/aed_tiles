#include<stdio.h>
#include<stdlib.h>

#include "reading.h"

int** allocTiles(FILE* fp, int lines, int columns){
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

void outputTiles(FILE* outfp, int lines, int columns, int** tiles){
    for(int l = lines - 1; l >= 0; l--){
        for(int c = 0; c < columns; c++){
            fprintf(outfp, "%d ", tiles[l][c]);
        }
        fprintf(outfp, "\n");
    }
    fprintf(outfp, "\n");
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