#ifndef STACK_H
#define STACK_H

typedef struct _node {
    int l;  //line
    int c;  //column
    struct _node *next;
} node;

void stackPush(node** head, int line, int column);

void stackPop(node** head);

#endif