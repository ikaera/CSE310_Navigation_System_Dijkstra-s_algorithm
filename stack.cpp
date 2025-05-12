// Irakli Eradze  ASU ID (emplid): 1222868231

#include "stack.h"
#include <stdlib.h>

void Push(pSTACK stack, int item) {
    if (stack->top == stack->capacity - 1) return;
    stack->array[++stack->top] = item;
}

int Pop(pSTACK stack) {
    if (stack->top == -1) return -1;
    return stack->array[stack->top--];
}

int IsEmpty(pSTACK stack) {
    return stack->top == -1;
}