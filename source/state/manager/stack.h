#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stack for storing game states
#define DEFAULT_MAXSTACK 20

typedef struct
{
    size_t top;  // top of stack
    size_t size; // current max size of a stack, if we try to go past this threshold, then
                 // it's size will be increased by DEFAULT_MAXSTACK elements
    unsigned long elementSize;
    void *stack;
} Stack;

// if initialMaxSize==0, then maximal initial size is set to DEFAULT_MAXSTACK
signed long initStack(Stack *stackPointer, unsigned int initialMaxSize, unsigned int elementSize);

// void element has to be of the constant size
void pushStack(Stack *stackPointer, const void *newElement);
void popStack(Stack *stackPointer);
void *getTopStackElement();
short int isStackFull(Stack *stackPointer);
short int isStackEmpty(Stack *stackPointer);
void deinitStack(Stack *stackPointer);

#endif