#ifndef LIST_H
#define LIST_H

#include "stack.h"

node* addToList(node* head, int line, int column);

void printList(FILE* outfp, node* head);

void deleteList(node* head);

#endif