#ifndef __STATE_SAMEN_STATE_H_INCLUDED__
#define __STATE_SAMEN_STATE_H_INCLUDED__

#include <grrlib.h>
#include <wiiuse/wpad.h>

#include "../sound/sound_manager.h"

#include "../gui/text.h"
#include "../gui/button.h"

#include "../colors.h"

#include "manager/game_state.h"
#include "manager/state_manager.h"

#include "main_menu.h"

extern GameState samenState;
void initAndRegisterSamenState();

#endif