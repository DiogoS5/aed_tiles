#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#include "reading.h"
#include "stack.h"
#include "board_stack.h"
#include "list.h"
#include "gravity.h"
#include "other.h"

void mode1(FILE* outfp, int** tiles, int lines, int columns){
    int reset = 1, plays = 0, score = 0, counter = 0, value = 0;
    node* stack_head = NULL, *groups_head = NULL, *groups_curr = NULL;

    while(reset){
        reset = 0;
        for(int line = 0; line < lines; line++){
            for(int column = 0; column < columns; column++){     
                counter = 0; //initialize tile counter
                value = tiles[line][column];

                if(value > 0){ //search for group

                    stackPush(&stack_head, line, column); //push first tile to stack
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

                score += counter*(counter-1); //update score
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

}

board* play(board* board, int play_l, int play_c, int lines, int columns){
    node* stack_head = NULL;
    int counter = 0; //initialize tile counter

    int** new_tiles = copyTiles(lines, columns, board->tiles);

    int value = new_tiles[play_l][play_c];

    stackPush(&stack_head, play_l, play_l);
    while(stack_head != NULL){
        int l = stack_head->l;
        int c = stack_head->c;
        stackPop(&stack_head);

        if (new_tiles[l][c] == value){

            new_tiles[l][c] = -1;
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

    int new_score = board->score + counter*(counter-1); //print score
    
    new_tiles = verticalGravity(lines, columns, new_tiles);
    new_tiles = horizontalGravity(lines, columns, new_tiles);

    node* possible_plays = findPlays(new_tiles, lines, columns);

    return boardAlloc(new_tiles, new_score, play_l, play_c, possible_plays);
}

//IDEIA: implement there is hope
//finds possible plays for given tiles
node* findPlays(int** tiles, int lines, int columns){
    int counter = 0, value = 0;
    node* stack_head = NULL, *possible_plays_head = NULL, *possible_plays_curr = NULL;

    //alloc matrix for visited flags
    _Bool** visited = (_Bool**)calloc(lines, sizeof(_Bool*));

    for (int l = 0; l < lines; l++) {
        visited[l] = (_Bool*)calloc(columns, sizeof(_Bool));

        if (visited[l] == NULL) {
            printf("failed allocation");
            exit(0);
        }
    }

    for(int line = 0; line < lines; line++){
        for(int column = 0; column < columns; column++){     
            counter = 0; //initialize tile counter
            value = tiles[line][column];

            if(value > 0 && !visited[line][column]){ //search for group
                stackPush(&stack_head, line, column); //push first tile to stack

                while(stack_head != NULL){
                    int l = stack_head->l; //just for better readability
                    int c = stack_head->c;

                    stackPop(&stack_head);
                    if (tiles[l][c] == value && !visited[l][c]){
                        visited[l][c] = 1;   //marks as visited
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

            /*there was only one tile*/

            if(counter == 1){
                tiles[line][column] = value; //return tile to original value
                continue;
            }

            /*there was a group*/

            //add play to possible plays list
            if(possible_plays_head == NULL){
                possible_plays_head = addToList(possible_plays_curr, line, column);
                possible_plays_curr = possible_plays_head;
            }
            else{
                possible_plays_curr = addToList(possible_plays_curr, line, column);
            }
        }
    }

    for (int l = 0; l < lines; l++) {
        if (visited[l] != NULL) {
            free(visited[l]);
        }
    }
    free(visited);
    
    return possible_plays_head;
}

void mode2(FILE* outfp, int** tiles, int lines, int columns){
    node* possible_plays = findPlays(tiles, lines, columns);
    board* board_head = NULL;
    board* new_board = boardAlloc(tiles, 0, 0, 0, possible_plays);
    boardPush(&board_head, new_board);

    while(board_head != NULL){
        boardPop(&board_head, lines);
        while(possible_plays != NULL){
            board* new_board = play(board_head, possible_plays->l, possible_plays->c, lines, columns);
            boardPush(&board_head, new_board);
            
            //delete play and move to next
            node* discard = possible_plays;
            possible_plays = possible_plays->next;
            free(discard);
        }
    }
}