#include "./button.h"

#ifndef GRRLIB_WHITE
#define GRRLIB_WHITE 0xFFFFFFFF
#endif

Button createButton(int x, int y, int width, int height, GRRLIB_ttfFont *font, int font_size, char *text)
{
    u32 computed_text_width = GRRLIB_WidthTTF(font, text, font_size);
    int text_x_offset = (width / 2) - (computed_text_width / 2);
    int text_y_offset = height / 2 - font_size / 1.6;

    Button button = {x, y, width, height, font, font_size, text_x_offset, text_y_offset, text};
    return button;
}

GRRLIB_texImg *preRenderButton(Button button, GRRLIB_texImg *tex_button, u32 text_color)
{
    GRRLIB_texImg *composed_tex_button = GRRLIB_CreateEmptyTexture(button.width, button.height);

    GRRLIB_CompoStart();

    GRRLIB_DrawPart(0, 0, 0, 0, 9, 9, tex_button, 0, 1, 1, GRRLIB_WHITE);
    GRRLIB_DrawPart(button.width - 9, 0, 11, 0, 9, 9, tex_button, 0, 1, 1, GRRLIB_WHITE);
    GRRLIB_DrawPart(button.width - 9, button.height - 9, 11, 11, 9, 9, tex_button, 0, 1, 1, GRRLIB_WHITE);
    GRRLIB_DrawPart(0, button.height - 9, 0, 11, 9, 9, tex_button, 0, 1, 1, GRRLIB_WHITE);

    if (button.width > 18)
    {
        GRRLIB_DrawPart(9 - (9 * ((button.width - 18) / 2 - 1)), 0, 9, 0, 2, 9, tex_button, 0, (button.width - 18) / 2, 1, GRRLIB_WHITE);
        GRRLIB_DrawPart(9 - (9 * ((button.width - 18) / 2 - 1)), button.height - 9, 9, 11, 2, 9, tex_button, 0, (button.width - 18) / 2, 1, GRRLIB_WHITE);
    }

    if (button.height > 18)
    {
        GRRLIB_DrawPart(0, 9 - (9 * ((button.height - 18) / 2 - 1)), 0, 9, 9, 2, tex_button, 0, 1, (button.height - 18) / 2, GRRLIB_WHITE);
        GRRLIB_DrawPart(button.width - 9, 9 - (9 * ((button.height - 18) / 2 - 1)), 11, 9, 9, 2, tex_button, 0, 1, (button.height - 18) / 2, GRRLIB_WHITE);
    }

    if (button.width > 18 && button.height > 18)
    {
        GRRLIB_DrawPart(9 - (9 * ((button.width - 18) / 2 - 1)), 9 - (9 * ((button.height - 18) / 2 - 1)), 9, 9, 2, 2, tex_button, 0, (button.width - 18) / 2, (button.height - 18) / 2, GRRLIB_WHITE);
    }

    textTTF(button.font, button.text_x_offset, button.text_y_offset, text_color, button.font_size, button.text);

    GRRLIB_CompoEnd(0, 0, composed_tex_button);
    return composed_tex_button;
}

void renderButton(Button button, GRRLIB_texImg *tex_button)
{
    GRRLIB_DrawImg(button.x, button.y, tex_button, 0, 1, 1, GRRLIB_WHITE);
}