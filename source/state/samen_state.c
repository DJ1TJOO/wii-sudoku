#include "samen_state.h"

#include "button_png.h"
#include "button_active_png.h"
#include "arial_rounded_ttf.h"
#include "background_png.h"
#include "p1_cursor_png.h"

GameState samenState;

// Font
static GRRLIB_ttfFont *arial16;

// Buttons
static GRRLIB_texImg *tex_button_png;
static GRRLIB_texImg *tex_button_active_png;

static Button quit_button;
static GRRLIB_texImg *tex_quit_button;
static GRRLIB_texImg *tex_quit_button_active;

static Button new_game_button;
static GRRLIB_texImg *tex_new_game_button;
static GRRLIB_texImg *tex_new_game_button_active;

// Sudoku
static GRRLIB_texImg *tex_background_png;
static GRRLIB_texImg *tex_cursor_png;

static u32 title_width;

static short int button_active = -1;
static int num_buttons = 3;

static int sudoku[81];
static int sudoku_state[81];
static int sudoku_active = 0;

static int active_cell = 0;
static int active_number = 1;

static void Init()
{
    // Init arial font
    arial16 = GRRLIB_LoadTTF(arial_rounded_ttf, arial_rounded_ttf_size);

    // Init sudoku
    tex_background_png = GRRLIB_LoadTexture(background_png);
    tex_cursor_png = GRRLIB_LoadTexture(p1_cursor_png);

    // Init buttons
    button_active = -1;

    tex_button_png = GRRLIB_LoadTexture(button_png);
    tex_button_active_png = GRRLIB_LoadTexture(button_active_png);

    quit_button = createButton((rmode->fbWidth / 2) - (160 / 2), (rmode->efbHeight) - 60, 160, 40, arial16, 25, "menu");
    new_game_button = createButton((rmode->fbWidth / 2) - (160 / 2), (rmode->efbHeight) - 110, 160, 40, arial16, 25, "nieuw spel");

    // Pre-render buttons
    tex_quit_button = preRenderButton(quit_button, tex_button_png, SUDOKU_WHITE);
    tex_quit_button_active = preRenderButton(quit_button, tex_button_active_png, SUDOKU_BLUE);

    tex_new_game_button = preRenderButton(new_game_button, tex_button_png, SUDOKU_WHITE);
    tex_new_game_button_active = preRenderButton(new_game_button, tex_button_active_png, SUDOKU_BLUE);

    // title width
    title_width = textWidth(arial16, 30, "SUDOKU");

    // Generate sudoku
    int *generated_sudoku = generateSudoku();
    for (int i = 0; i < 81; i++)
    {
        sudoku[i] = generated_sudoku[i];
        sudoku_state[i] = 0;
    }

    // Play a random sound
    // setOneSound(1);
    // setLoopSound(1);
    // playSound(0);
}

static void Deinit()
{
    // Stop the sound
    // stopSound();
    // setLoopSound(0);
    // setOneSound(0);

    // Free the arial font
    GRRLIB_FreeTTF(arial16);

    // Free the button textures
    GRRLIB_FreeTexture(tex_quit_button);
    GRRLIB_FreeTexture(tex_quit_button_active);

    GRRLIB_FreeTexture(tex_button_png);
    GRRLIB_FreeTexture(tex_button_active_png);

    // Free the sudoku texture
    GRRLIB_FreeTexture(tex_background_png);
    GRRLIB_FreeTexture(tex_cursor_png);
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

    if (button_active != 0)
    {
        // If [DOWN] was pressed on the first Wiimote, toggle the button state
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_DOWN)
            button_active = (button_active + 1) % num_buttons;
        // If [UP] was pressed on the first Wiimote, toggle the button state
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_UP)
            button_active = (button_active + num_buttons - 1) % num_buttons;
    }
    else if (button_active == 0)
    {
        // If [DOWN] was pressed on the first Wiimote, toggle the button state
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_DOWN)
            active_cell = (active_cell + 9) % 81;
        // If [UP] was pressed on the first Wiimote, toggle the button state
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_UP)
            active_cell = (active_cell + 81 - 9) % 81;

        // If [LEFT] was pressed on the first Wiimote, toggle the button state
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_LEFT)
            active_cell = (active_cell + 81 - 1) % 81;
        // If [RIGHT] was pressed on the first Wiimote, toggle the button state
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_RIGHT)
            active_cell = (active_cell + 1) % 81;

        sudoku_active = sudoku[active_cell];
    }

    // If [-] was pressed on the first Wiimote, handle the button press
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_MINUS)
    {
        active_number = (active_number + 9 - 2) % 9 + 1;
    }

    // If [+] was pressed on the first Wiimote, handle the button press
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_PLUS)
    {
        active_number = (active_number) % 9 + 1;
    }

    // If [B] was pressed on the first Wiimote, handle the button press
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_B)
    {
        if (button_active == 0)
            button_active = 1;
    }

    // If [A] was pressed on the first Wiimote, handle the button press
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
    {
        switch (button_active)
        {
        case 0: // Inside sudoku
            sudoku[active_cell] = active_number;
            sudoku_state[active_cell] = 1;
            break;
        case 1: // New game
            break;
        case 2: // To Main menu
            changeState(&mainMenuState);
            break;
        }
    }
}

static void Render()
{
    GRRLIB_FillScreen(SUDOKU_BLACK);

    // Render main title
    textTTF(arial16, (rmode->fbWidth / 2) - (title_width / 2), 20, SUDOKU_WHITE, 30, "SUDOKU");

    // Render new game button
    renderButton(new_game_button, button_active == 1 ? tex_new_game_button_active : tex_new_game_button);

    // Render quit button
    renderButton(quit_button, button_active == 2 ? tex_quit_button_active : tex_quit_button);

    // Render sudoku
    GRRLIB_DrawImg((rmode->fbWidth / 2) - (tex_background_png->w / 2), 70, tex_background_png, 0, 1, 1, GRRLIB_WHITE);

    // Render sudoku numbers
    for (int i = 0; i < 81; i++)
    {
        if (sudoku[i] != 0)
        {
            int x = (rmode->fbWidth / 2) - (tex_background_png->w / 2) + (i % 9) * 30;
            int y = 70 + (i / 9) * 30;

            u32 color = sudoku_state[i] == 0 ? SUDOKU_GREY : SUDOKU_WHITE;
            if (sudoku[i] == sudoku_active)
                color = SUDOKU_BLUE;

            textTTF(arial16, x + 12, y + 5, color, 20, textFormat("%d", sudoku[i]));
        }
    }

    // Render cursor
    if (button_active == 0)
    {
        int x = (rmode->fbWidth / 2) - (tex_background_png->w / 2) + (active_cell % 9) * 30;
        int y = 70 + (active_cell / 9) * 30;
        GRRLIB_DrawImg(x, y, tex_cursor_png, 0, 1, 1, GRRLIB_WHITE);
    }

    // Render active number
    textTTF(arial16, (rmode->fbWidth / 2) + (tex_background_png->w / 2) + 40, 70 + (tex_background_png->h / 2) - 30, SUDOKU_WHITE, 16, "Geselecteerd:");

    GRRLIB_DrawImg((rmode->fbWidth / 2) + (tex_background_png->w / 2) + 40, 70 + (tex_background_png->h / 2) - 7, tex_cursor_png, 0, 0.5, 0.5, GRRLIB_WHITE);
    textTTF(arial16, (rmode->fbWidth / 2) + (tex_background_png->w / 2) + 60, 70 + (tex_background_png->h / 2) - 8, SUDOKU_WHITE, 16, textFormat("%d", active_number));

    // Render the frame buffer to the TV
    GRRLIB_Render();
}

static void Loop()
{
    if (samenState.paused == 1)
        return;

    HandleInput();
    Render();
}

void initAndRegisterSamenState()
{
    initGamestate(&samenState, Init, Loop, Deinit);
}