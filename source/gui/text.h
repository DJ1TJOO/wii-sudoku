#ifndef __GUI_TEXT_H_INCLUDED__
#define __GUI_TEXT_H_INCLUDED__

#include <grrlib.h>

#include <stdarg.h>
#include <stdio.h>

char *textFormat(const char *s, ...);
u32 textWidth(GRRLIB_ttfFont *font, int font_size, char *text);
void textTTF(GRRLIB_ttfFont *font, int xpos, int ypos, u32 fgc, int font_size, char *text);
void textTTFWithShadow(GRRLIB_ttfFont *font, int xpos, int ypos, int shadow, u32 fgc, u32 bgc, int font_size, char *text);

#endif
