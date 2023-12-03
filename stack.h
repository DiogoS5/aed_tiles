#ifndef STACK_H
#define STACK_H

typedef struct _node {
    int l;  //line
    int c;  //column
    struct _node *next;
} node;

extern node* head;

void stackPush(int line, int column);

void stackPop();

#endif    // STACK_H