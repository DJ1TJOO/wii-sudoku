#ifndef __STATE_MAIN_MENU_H_INCLUDED__
#define __STATE_MAIN_MENU_H_INCLUDED__

#include <grrlib.h>
#include <wiiuse/wpad.h>

#include "../sound/sound_manager.h"

#include "../gui/text.h"
#include "../gui/button.h"

#include "../colors.h"

#include "manager/game_state.h"
#include "manager/state_manager.h"

#include "samen_state.h"

extern GameState mainMenuState;
void initAndRegisterMainMenuState();

#endif