#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "reading.h"
#include "stack.h"
#include "gravity.h"

node* head = NULL; //initialize head of stack

int main(int argc, char *argv[]) {
    int lines, columns, variant, line, column;
    FILE* fp;

    if (argc < 2) {//there must be a file name
        exit(0);
    }

    char* suffix = (char*)malloc(12*sizeof(char));
    strcpy(suffix, argv[1] + strlen(argv[1]) - 11);

    char* prefix = (char*)malloc((strlen(argv[1]) - strlen(suffix))*sizeof(char));
    strncpy(prefix, argv[1], strlen(argv[1]) - strlen(suffix));

    if(strcmp(suffix, ".tilewalls1") != 0){
        exit(0);
    }
    fp = fopen(argv[1], "r");
    if (fp == (NULL)) {
        exit(0);
    }

    char *outfilename = (char*) malloc(strlen(argv[1])+12);

    if (outfilename != NULL) {
        strcpy(outfilename, prefix);
        strcat(outfilename, ".singlestep");
    }
    else{
        exit(0);
    }

    FILE* outfp = fopen(outfilename, "w");


    while(fscanf(fp, "%d %d %d %d %d", &lines, &columns, &variant, &line, &column) == 5){ //read problem
        if (!(variant == 1 || variant == 2) || !(line > 0 && line <= lines) || !(column > 0 && column <= columns) ) { //check if it's a valid problem
            fprintf(outfp, "%d %d %d %d %d\n\n", lines, columns, variant, line, column); //print invalid (output)
            skipTiles(fp, lines, columns); //read and ignore problem
            continue; //skip to next iteration
        }

        fprintf(outfp, "%d %d %d %d %d\n", lines, columns, variant, line, column); //print valid

        line -= 1; //adjusting because lines and columns start in 0
        column -= 1;

        int counter = 0; //initialize tile counter

        int** tiles = allocTiles(fp, lines, columns);

        tiles = readTiles(fp, lines, columns, tiles);


        int value = tiles[line][column];

        stackPush(line, column);

        if(value > 0){
            while(head != NULL){
                int l = head->l;
                int c = head->c;
                stackPop(head);
                if (tiles[l][c] == value){
                    tiles[l][c] = -1;
                    counter += 1;

                    if(l + 1 < lines){
                        stackPush(l + 1, c);
                    }
                    if(l - 1 >= 0){
                        stackPush(l - 1, c);
                    }
                    if(c + 1 < columns){
                        stackPush(l, c + 1);
                    }
                    if(c - 1 >= 0){
                        stackPush(l, c - 1);
                    }
                }
            }
        }
        else{
            counter = 1;
        }

        if(counter == 1){ //if it was only one tile
            tiles[line][column] = value; //return tile to original value
        }

        //Variants
        if(variant == 1){
            fprintf(outfp, "%d\n\n", counter*(counter-1)); //print score
        }
        else{ //variant 2
            tiles = verticalGravity(lines, columns, tiles);
            tiles = horizontalGravity(lines, columns, tiles);

            outputTiles(outfp, lines, columns, tiles);
        }

        //Frees
        for (int l = 0; l < lines; l++) {
            if (tiles[l] != NULL) {
                free(tiles[l]);
            }
        }
        free(tiles);
    }

    //free files
    fclose(fp);
    fclose(outfp);

    return 0;
}
