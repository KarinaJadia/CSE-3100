#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int match(char *exp)
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = NULL;
    int result = 0;
    int counter = 0;

    // this is what i was gonna do but it didn't work

    // for(int i = 0; i < strlen(exp); i++) // going through string
    // {
    //     if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{') // if opening bracket then add to stack
    //     {
    //         // TODO
    //         push(s, create_node(exp[i]));
    //     }
    //     else if(exp[i] == ')' || exp[i] == ']' || exp[i] == '}') // if closing bracket
    //     {
    //         // TODO
    //         push(s, create_node(exp[i]));
    //     }
    // }
    // int counter = 0;

    // if (!empty(s)) {
    //     // TODO

    //     while (!empty) {
    //         node* x = pop(s)
    //         if(x->v == '(') counter += 1;
    //         if(x->v == ')') counter -= 1;
    //         if(x->v == '[') counter += 2;
    //         if(x->v == ']') counter -= 2;
    //         if(x->v == '{') counter += 3;
    //         if(x->v == '}') counter -= 3;
    //     }

    for(int i = 0; i < strlen(exp); i++) // going through string
    {
        // i completely butchered it im sorry
        if(exp[i] == '(') counter += 1;
        if(exp[i] == ')') counter -= 1;
        if(exp[i] == '[') counter += 2;
        if(exp[i] == ']') counter -= 2;
        if(exp[i] == '{') counter += 3;
        if(exp[i] == '}') counter -= 3;
    }
    if (counter == 0) result = 1;

    free(s);
    return result;


}

int main(int argc, char *argv[])
{   
    if(argc != 2) 
    {
        printf("Usage: %s expression\n", argv[0]);
        return -1;
    }
    char * exp = argv[1];

    printf("%s\n", exp);
    if(match(exp))
    {
        printf("match test passed.\n");
    }
    else
    {
        printf("match test failed.\n");
    }
	return 0;
}