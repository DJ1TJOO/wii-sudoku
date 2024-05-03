#include "state_manager.h"

static Stack gameStateStack;
static short int running = 0;
static GameState *currentState = 0;

signed int initGameStateManager()
{
    // if (initStack(&gameStateStack, 0, sizeof(GameState)) < 0)
    //     return -1;

    running = 1;
    return 0;
}

void deinitGameStateManager()
{
    if (currentState)
    {
        currentState->deinit();
    }

    currentState = 0;

    // GameState *tempState = 0;

    // while (!isStackEmpty(&gameStateStack))
    // {
    //     // cleanup current state
    //     tempState = (GameState *)getTopStackElement(&gameStateStack);
    //     // deinit it
    //     tempState->deinit();
    //     // remove it
    //     popStack(&gameStateStack);
    // }

    // deinitStack(&gameStateStack);
}

void changeState(GameState *state)
{
    if (currentState)
    {
        currentState->deinit();
    }

    currentState = state;
    currentState->init();

    // GameState *tempState = 0;

    // if (!isStackEmpty(&gameStateStack))
    // {

    //     // cleanup current state
    //     tempState = (GameState *)getTopStackElement(&gameStateStack);
    //     // deinit it
    //     tempState->deinit();
    //     // remove it
    //     popStack(&gameStateStack);
    // }

    // // store and init new state
    // pushStack(&gameStateStack, (const void *)state);
    // tempState = (GameState *)getTopStackElement(&gameStateStack);
    // tempState->init();
}

void popState()
{
    // GameState *tempState = 0;

    // if (!isStackEmpty(&gameStateStack))
    // {

    //     // cleanup current state
    //     tempState = (GameState *)getTopStackElement(&gameStateStack);
    //     // deinit it
    //     tempState->deinit();
    //     // remove it
    //     popStack(&gameStateStack);
    // }

    // resume previous
    // if (!isStackEmpty(&gameStateStack))
    // {
    //     tempState = (GameState *)getTopStackElement(&gameStateStack);
    //     resumeGamestate(tempState);
    // }
}

void pushState(GameState *state)
{
    // GameState *tempState = 0;

    // if (!isStackEmpty(&gameStateStack))
    // {

    //     tempState = (GameState *)getTopStackElement(&gameStateStack);
    //     pauseGamestate(tempState);
    // }

    // pushStack(&gameStateStack, (const void *)state);
    // tempState = (GameState *)getTopStackElement(&gameStateStack);
    // tempState->init();
}

void process()
{
    if (currentState)
    {
        currentState->process();
    }

    // GameState *tempState = 0;
    // tempState = (GameState *)getTopStackElement(&gameStateStack);
    // tempState->process();

    // processSound();
}

short int isGameRunning()
{
    return running;
}

void quit()
{
    running = 0;
}