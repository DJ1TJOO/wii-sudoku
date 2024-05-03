#ifndef __GUI_BUTTON_H_INCLUDED__
#define __GUI_BUTTON_H_INCLUDED__

#include <grrlib.h>
#include "text.h"

typedef struct
{
    int x;
    int y;
    int width;
    int height;
    GRRLIB_ttfFont *font;
    int font_size;
    int text_x_offset;
    int text_y_offset;
    char *text;
} Button;

Button createButton(int x, int y, int width, int height, GRRLIB_ttfFont *font, int font_size, char *text);
GRRLIB_texImg *preRenderButton(Button button, GRRLIB_texImg *tex_button, u32 text_color);
void renderButton(Button button, GRRLIB_texImg *tex_button);

#endif
