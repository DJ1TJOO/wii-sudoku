

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
    SYS_STDIO_Report(true);
    fprintf(stdout, "[SUDOKU]: Hello world!\r");

    // Initialise the Graphics & Video subsystem
    fprintf(stdout, "[SUDOKU]: Init GRRLIB\r");
    GRRLIB_Init();
    // GRRLIB_Settings.antialias = true;

    // Initialise the audio subsystem
    fprintf(stdout, "[SUDOKU]: Init ASND\r");
    ASND_Init();
    fprintf(stdout, "[SUDOKU]: Init MP3\r");
    MP3Player_Init();

    // Initialise the Wiimotes
    fprintf(stdout, "[SUDOKU]: Init WPAD\r");
    WPAD_Init();

    // Initialize Game State Manager
    fprintf(stdout, "[SUDOKU]: Init Game States\r");
    initAndRegisterMainMenuState();
    initAndRegisterSamenState();

    fprintf(stdout, "[SUDOKU]: Init Game State Manager\r");
    if (initGameStateManager() < 0)
    {
        puts("Error: state manager error\n");
        exit(1);
    }

    // load the main menu
    fprintf(stdout, "[SUDOKU]: GameState -> MainMenu\r");
    changeState(&mainMenuState);

    // main loop
    while (isGameRunning() == TRUE)
    {
        process();
    }

    fprintf(stdout, "[SUDOKU]: Deinit Game State Manager\r");
    deinitGameStateManager();

    // Audio
    fprintf(stdout, "[SUDOKU]: Deinit MP3 and ASND\r");
    MP3Player_Stop();
    ASND_End();

    fprintf(stdout, "[SUDOKU]: Deinit GRRLIB\r");
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
    exit(0);       // Use exit() to exit a program, do not use 'return' from main()
}
