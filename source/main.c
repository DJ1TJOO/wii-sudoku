

#include <grrlib.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <wiiuse/wpad.h>

#include <asndlib.h>
#include <mp3player.h>

#include "state/states.h"
#include "state/samen_state.h"
#include "state/main_menu.h"
#include "state/manager/state_manager.h"

int main(int argc, char **argv)
{
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();
    // GRRLIB_Settings.antialias = true;

    // Initialise the audio subsystem
    ASND_Init();
    MP3Player_Init();

    // Initialise the Wiimotes
    WPAD_Init();

    // Initialize Game State Manager
    initAndRegisterMainMenuState();
    initAndRegisterSamenState();

    if (initGameStateManager() < 0)
    {
        puts("Error: state manager error\n");
        exit(1);
    }

    // load the main menu
    changeState(&mainMenuState);

    // main loop
    while (isGameRunning() == TRUE)
    {
        process();
    }

    deinitGameStateManager();
    MP3Player_Stop();
    ASND_End();

    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
    exit(0);       // Use exit() to exit a program, do not use 'return' from main()
}
