#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "reading.h"
#include "stack.h"
#include "gravity.h"

node* head = NULL; //initialize head of stack

int main(int argc, char *argv[]) {
    int lines, columns, variant, line, column;
    FILE* fp, *outfp;

    if (argc < 2) {
        fprintf(stderr, "not enough arguments\n"); //there must be a file name
        exit(EXIT_FAILURE);
    }

    if(strstr(argv[1], ".tilewalls1") == NULL){
        fprintf(stderr, "'.tilewalls1' not found in file name.\n");
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if (fp == (NULL)) {
        fprintf(stderr, "File %s cannot be read. \n", argv[1]);
        exit(EXIT_FAILURE);
    }


    // Find the last occurrence of ".tilewalls1"
    const char* lastDotTilewalls1 = strrchr(argv[1], '.');
    if (lastDotTilewalls1 != NULL) {
        // Check if the substring after the last occurrence of ".tilewalls1" is ".tilewalls1"
        if (strcmp(lastDotTilewalls1, ".tilewalls1") == 0) {
            // Calculate the length of the desired part
            size_t prefix_len = (lastDotTilewalls1 - argv[1]);

            char outfilename[prefix_len + 11 + 1];
            strncpy(outfilename, argv[1], prefix_len);
            outfilename[prefix_len] = '\0';

            if (outfilename != NULL) {
                strcat(outfilename, ".singlestep");
            }
            else{
                printf("NULL\n");
                exit(0);
            }

            // Print the result
            printf("outfilename: %s\n", outfilename);

            outfp = (FILE*)fopen(outfilename, "w");

        } else {
            printf("No '.tilewalls1' found at the end of the filename.\n");
            exit(0);
        }
    } else {
        printf("No '.' found in the filename.\n");
        exit(0);
    }

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

        if(value > 0){
            stackPush(line, column);
            while(head != NULL){
                int l = head->l;
                int c = head->c;
                stackPop(head);
                //printf("(%d,%d) ", l+1, c+1);
                if (tiles[l][c] == value){
                    //printf("ye\n");
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
