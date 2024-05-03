#include "game_state.h"

void initGamestate(GameState *state, const void *init, const void *process, const void *deinit)
{
    state->init = init;
    state->process = process;
    state->deinit = deinit;

    state->paused = 0;
};

inline void pauseGamestate(GameState *state)
{
    state->paused = 1;
}

inline void resumeGamestate(GameState *state)
{
    state->paused = 0;
}