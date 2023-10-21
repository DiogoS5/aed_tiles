#include<stdlib.h>

#include "gravity.h"

int** verticalGravity(int lines, int columns, int** tiles){
    int counter;
    for(int c = 0; c < columns; c++){
        counter = 0;
        for(int l = 0; l < lines; l++){
            if(tiles[l][c] != -1){
                if(counter != l){
                    tiles[counter][c] = tiles[l][c];
                    tiles[l][c] = -1;
                }
                counter++;
            }
        }
    }
    return tiles;
}

int** horizontalGravity(int lines, int columns, int** tiles){
    int counter = columns - 1;
    for(int c = columns - 1; c >= 0; c--){
        if(tiles[0][c] != -1){
            if(counter != c){
                for(int l = 0; l < lines; l++){
                    tiles[l][counter] = tiles[l][c];
                    tiles[l][c] = -1;
                }
            }  
            counter--;                     
        }
    }
    return tiles;
}