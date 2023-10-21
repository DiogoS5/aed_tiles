#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "reading.h"
#include "stack.h"
#include "list.h"
#include "gravity.h"
int main(int argc, char *argv[]) {
    int lines, columns, mode;
    int reset, plays, score = 0, counter = 0, value = 0;
    node* stack_head = NULL, *groups_head = NULL, *groups_curr = NULL;
    FILE* fp, *outfp;

    if (argc < 2) {//there must be a file name
        exit(0);
    }

    fp = fopen(argv[1], "r"); //open input file
    if (fp == (NULL)) {
        exit(0);
    }

    // Find the last occurrence of ".tilewalls1"
    const char* lastDotTilewalls1 = strrchr(argv[1], '.');
    if (lastDotTilewalls1 != NULL) {
        // Check if the substring after the last occurrence of ".tilewalls1" is ".tilewalls1"
        if (strcmp(lastDotTilewalls1, ".tilewalls") == 0) {
            // Calculate the length of the desired part
            size_t prefix_len = (lastDotTilewalls1 - argv[1]);

            char outfilename[prefix_len + 11 + 1];
            strncpy(outfilename, argv[1], prefix_len);
            outfilename[prefix_len] = '\0';

            if (outfilename != NULL) {
                strcat(outfilename, ".tyleblasts");
            }
            else{
                printf("NULL\n");
                exit(0);
            }

            outfp = (FILE*)fopen(outfilename, "w");

        } else {
            printf("No '.tilewalls' found at the end of the filename.\n");
            exit(0);
        }
    } else {
        printf("No '.' found in the filename.\n");
        exit(0);
    }


    while(fscanf(fp, "%d %d %d", &lines, &columns, &mode) == 3){ //read problem
        if (!(mode == -1 || mode == -3 || mode >= 0)) { //check if it's a valid problem
            fprintf(outfp, "%d %d %d\n", lines, columns, mode); //print invalid (output)
            skipTiles(fp, lines, columns); //read and ignore problem
            continue; //skip to next iteration
        }

        fprintf(outfp, "%d %d %d\n", lines, columns, mode); //print valid

        int** tiles = allocTiles(fp, lines, columns);

        tiles = readTiles(fp, lines, columns, tiles);
        
        reset = 1;
        plays = 0;
        score = 0;
        groups_head = NULL;
        groups_curr = NULL;

        while(reset){
            reset = 0;
            for(int line = 0; line < lines; line++){
                for(int column = 0; column < columns; column++){     
                    counter = 0; //initialize tile counter
                    value = tiles[line][column];

                    if(value > 0){ //search for group

                        stackPush(&stack_head, line, column);
                        while(stack_head != NULL){
                            int l = stack_head->l;
                            int c = stack_head->c;

                            stackPop(&stack_head);
                            if (tiles[l][c] == value){
                                tiles[l][c] = -1;
                                counter += 1;

                                if(l + 1 < lines){
                                    stackPush(&stack_head, l + 1, c);
                                }
                                if(l - 1 >= 0){
                                    stackPush(&stack_head, l - 1, c);
                                }
                                if(c + 1 < columns){
                                    stackPush(&stack_head, l, c + 1);
                                }
                                if(c - 1 >= 0){
                                    stackPush(&stack_head, l, c - 1);
                                }
                            }
                        }
                    }
                    else{ //not a colour
                        continue;
                    }

                    if(counter == 1){ //only one tile
                        tiles[line][column] = value; //return tile to original value
                        continue;
                    }
                    //there was a group
                    if(groups_head == NULL){
                        groups_head = addToList(groups_curr, line, column);
                        groups_curr = groups_head;
                    }
                    else{
                        groups_curr = addToList(groups_curr, line, column);
                    }
                    
                    tiles = verticalGravity(lines, columns, tiles);
                    tiles = horizontalGravity(lines, columns, tiles);

                    score += counter*(counter-1); //print score
                    plays += 1;

                    reset = 1;
                    break;
                }
                if(reset){
                    break;
                }
            }
        }

        fprintf(outfp, "%d %d\n", plays, score);
        printList(outfp, groups_head); 
        deleteList(groups_head); 
        //outputTiles(outfp, lines, columns, tiles);   
            
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

