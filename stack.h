#ifndef STACK_H
#define STACK_H

typedef struct _node {
    int l;  //line
    int c;  //column
    struct _node *next;
} node;

typedef struct _occurrences {
    int number;  // numero lido
    int counter; // ocurrencias de cada número diferent
    struct _occurrences *next;
} occurrences;

void stackPush(node** head, int line, int column);

void stackPop(node** head);

void printStack(FILE* outfp, node* head);

int copyReversedStack(node* original, node** reversed);

void stackPushOccurrences(occurrences **head, int counter, int value);

int score(occurrences* head );

void deleteStackOccurrences(occurrences** head);

void deleteStack(node** head);

#endif