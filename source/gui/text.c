#include "./text.h"

char *textFormat(const char *s, ...)
{
    va_list ap;
    char line[200];

    va_start(ap, s);
    vsnprintf(line, 200, s, ap);
    va_end(ap);

    return strdup(line);
}

u32 textWidth(GRRLIB_ttfFont *font, int font_size, char *text)
{
    return GRRLIB_WidthTTF(font, text, font_size);
}

void textTTF(GRRLIB_ttfFont *font, int xpos, int ypos, u32 fgc, int font_size, char *text)
{
    GRRLIB_PrintfTTF(xpos, ypos, font, text, font_size, fgc);
}

void textTTFWithShadow(GRRLIB_ttfFont *font, int xpos, int ypos, int shadow, u32 fgc, u32 bgc, int font_size, char *text)
{
    GRRLIB_PrintfTTF(xpos + shadow, ypos + shadow, font, text, font_size, bgc);
    GRRLIB_PrintfTTF(xpos, ypos, font, text, font_size, fgc);
}