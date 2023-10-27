#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(stack *s, node *new_node)
{
    if (s == NULL || new_node == NULL) {
        fprintf(stderr, "cannot push\n");
        return;
    }
    new_node->next = s->top;
    s->top = new_node;
}

node* pop(stack *s)
{
    if (s == NULL || s->top == NULL) {
        fprintf(stderr, "stack is empty, cannot pop\n");
        return NULL;
    }
    node* temp = s->top;
    s->top = temp->next;
    temp->next = NULL;
    return temp;
}

int empty(stack *s)
{
    return s == NULL || s->top == NULL;
}

void clear_stack(stack *s)
{
    while (!empty(s)) {
        node* temp = pop(s);
        free(temp);
    }
}
