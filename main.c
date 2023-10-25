#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "reading.h"
#include "stack.h"
#include "board_stack.h"
#include "list.h"
#include "gravity.h"
#include "other.h"


int main(int argc, char *argv[]) {
    int lines, columns, mode;
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

        int** tiles = allocTiles(lines, columns);

        tiles = readTiles(fp, lines, columns, tiles);
        
        if(mode == -1){
            //node* possible_plays_head = findPlays(tiles, lines, columns);
            //printf(outfp, "possible plays:\n");
            //printList(outfp, possible_plays_head);
            //deleteList(possible_plays_head);
            mode1(outfp, tiles, lines, columns);
        }
        else if(mode == 2){
            printf("ye");
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

