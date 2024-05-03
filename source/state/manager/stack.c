#include "stack.h"

// if initialMaxSize==0, then maximal initial size is set to DEFAULT_MAXSTACK
signed long initStack(Stack *stackPointer, unsigned int initialMaxSize, unsigned int elementSize)
{
    stackPointer->top = 0;
    stackPointer->stack = 0;
    stackPointer->elementSize = elementSize;

    if (initialMaxSize == 0)
    {
        stackPointer->size = DEFAULT_MAXSTACK;
    }
    else
    {
        stackPointer->size = initialMaxSize;
    }

    // allocate memory
    void *pNewStack = 0;

    pNewStack = malloc(elementSize * stackPointer->size);

    if (pNewStack == 0)
        return -1;

    memset(pNewStack, 0, elementSize * stackPointer->size);

    stackPointer->stack = pNewStack;

    return 0;
}

// void element has to be of the constant size
void pushStack(Stack *stackPointer, const void *newElement)
{

    if (stackPointer->top == stackPointer->size)
    {

        // stack underflow
        stackPointer->size = stackPointer->size + DEFAULT_MAXSTACK;

        if (realloc(stackPointer->stack, stackPointer->size * stackPointer->elementSize) == NULL)
        {
            // Houston we have a problem. nothing can be done... we are dead...
            puts("Warning: Stack overflow!\r\t");
        }
        return;
    }
    else
    {
        unsigned long dst;

        dst = ((unsigned long)stackPointer->stack) + ((++stackPointer->top) * (stackPointer->elementSize));

        memcpy((void *)dst, newElement, stackPointer->elementSize);
        return;
    }
}

void *getTopStackElement(Stack *stackPointer)
{

    // we assume stack is not empty
    unsigned long adr = ((unsigned long)stackPointer->stack) + (stackPointer->top * stackPointer->elementSize);

    // return removed element
    return (void *)adr;
}

void popStack(Stack *stackPointer)
{

    if (stackPointer->top == 0)
    {
        // stack underflow
        puts("Warning: Stack underflow!\r\t");
    }
    else
    {
        --stackPointer->top;
    }
}

short int isStackFull(Stack *stackPointer)
{
    if (stackPointer->top == (stackPointer->size - 1))
        return 1;
    else
        return 0;
}

short int isStackEmpty(Stack *stackPointer)
{

    if (stackPointer->top == 0)
        return 1;
    else
        return 0;
}

void deinitStack(Stack *stackPointer)
{

    free(stackPointer->stack);

    stackPointer->top = 0;
    stackPointer->stack = 0;
    stackPointer->elementSize = 0;
    stackPointer->size = 0;
}