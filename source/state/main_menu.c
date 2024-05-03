#include "main_menu.h"

#include "button_png.h"
#include "button_active_png.h"
#include "arial_rounded_ttf.h"
#include "background_png.h"

GameState mainMenuState;

// Font
static GRRLIB_ttfFont *arial16;

// Buttons
static GRRLIB_texImg *tex_button_png;
static GRRLIB_texImg *tex_button_active_png;

static Button start_button;
static GRRLIB_texImg *tex_start_button;
static GRRLIB_texImg *tex_start_button_active;

static Button battle_button;
static GRRLIB_texImg *tex_battle_button;
static GRRLIB_texImg *tex_battle_button_active;

static Button quit_button;
static GRRLIB_texImg *tex_quit_button;
static GRRLIB_texImg *tex_quit_button_active;

static short int button_active = -1;
static int num_buttons = 3;

static void Init()
{
    // Init arial font
    arial16 = GRRLIB_LoadTTF(arial_rounded_ttf, arial_rounded_ttf_size);

    // Init buttons
    button_active = -1;

    tex_button_png = GRRLIB_LoadTexture(button_png);
    tex_button_active_png = GRRLIB_LoadTexture(button_active_png);

    start_button = createButton((rmode->fbWidth / 2) - (160 / 2), 170, 160, 40, arial16, 25, "samen");
    battle_button = createButton((rmode->fbWidth / 2) - (160 / 2), 170 + 50, 160, 40, arial16, 25, "battle");
    quit_button = createButton((rmode->fbWidth / 2) - (160 / 2), (rmode->efbHeight) - 100, 160, 40, arial16, 25, "sluiten");

    // Pre-render buttons
    tex_start_button = preRenderButton(start_button, tex_button_png, SUDOKU_WHITE);
    tex_start_button_active = preRenderButton(start_button, tex_button_active_png, SUDOKU_BLUE);

    tex_battle_button = preRenderButton(battle_button, tex_button_png, SUDOKU_WHITE);
    tex_battle_button_active = preRenderButton(battle_button, tex_button_active_png, SUDOKU_BLUE);

    tex_quit_button = preRenderButton(quit_button, tex_button_png, SUDOKU_WHITE);
    tex_quit_button_active = preRenderButton(quit_button, tex_button_active_png, SUDOKU_BLUE);

    // Play a random sound
    // setOneSound(1);
    // setLoopSound(1);
    // playSound(0);
}

static void Deinit()
{
    // Stop the sound
    stopSound();
    setLoopSound(0);
    setOneSound(0);

    // Free the arial font
    GRRLIB_FreeTTF(arial16);

    // Free the button textures
    GRRLIB_FreeTexture(tex_start_button);
    GRRLIB_FreeTexture(tex_start_button_active);
    GRRLIB_FreeTexture(tex_battle_button);
    GRRLIB_FreeTexture(tex_battle_button_active);
    GRRLIB_FreeTexture(tex_quit_button);
    GRRLIB_FreeTexture(tex_quit_button_active);

    // Free the button textures
    GRRLIB_FreeTexture(tex_button_png);
    GRRLIB_FreeTexture(tex_button_active_png);
}

static void HandleInput()
{
    WPAD_ScanPads(); // Scan the Wiimotes

    // If [HOME] was pressed on the first Wiimote, break out of the loop
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
    {
        quit();
        return;
    }

    // If [DOWN] was pressed on the first Wiimote, toggle the button state
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_DOWN)
        button_active = (button_active + 1) % num_buttons;
    // If [UP] was pressed on the first Wiimote, toggle the button state
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_UP)
        button_active = (button_active + num_buttons - 1) % num_buttons;

    // If [A] was pressed on the first Wiimote, handle the button press
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
    {
        switch (button_active)
        {
        case 0: // Samen
            changeState(&samenState);
            break;
        case 1: // Battle
            // changeState(&battleState);
            break;
        case 2: // Quit
            quit();
            break;
        }
    }
}

static void Render()
{
    GRRLIB_FillScreen(SUDOKU_BLACK);

    // Render main title
    u32 title_width = textWidth(arial16, 50, "SUDOKU");
    textTTF(arial16, (rmode->fbWidth / 2) - (title_width / 2), 60, SUDOKU_WHITE, 50, "SUDOKU");

    // Render the button
    renderButton(start_button, button_active == 0 ? tex_start_button_active : tex_start_button);

    // Render battle button
    renderButton(battle_button, button_active == 1 ? tex_battle_button_active : tex_battle_button);

    // Render quit button
    renderButton(quit_button, button_active == 2 ? tex_quit_button_active : tex_quit_button);

    // Render the frame buffer to the TV
    GRRLIB_Render();
}

static void Loop()
{
    if (mainMenuState.paused == 1)
        return;

    HandleInput();
    Render();
}

void initAndRegisterMainMenuState()
{
    initGamestate(&mainMenuState, Init, Loop, Deinit);
}