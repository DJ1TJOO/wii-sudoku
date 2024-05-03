#ifndef __GAMESTATE_H_INCLUDED__
#define __GAMESTATE_H_INCLUDED__

typedef void (*voidFunction)();

typedef struct
{
  voidFunction init;
  voidFunction process;
  voidFunction deinit;
  short int paused;
} GameState;

void initGamestate(GameState *state, const void *init, const void *process, const void *deinit);
void pauseGamestate(GameState *state);
void resumeGamestate(GameState *state);

#endif