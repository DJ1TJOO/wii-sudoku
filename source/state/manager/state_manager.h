#ifndef __STATE_MANAGER_H__
#define __STATE_MANAGER_H__

#include "game_state.h"
#include "stack.h"
#include "../../sound/sound_manager.h"

signed int initGameStateManager(void);
void deinitGameStateManager();

void changeState(GameState *state);
void popState();
void pushState(GameState *state);

void process();
short int isGameRunning();
void quit();

#endif