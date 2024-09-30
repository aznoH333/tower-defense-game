#ifndef G_TEXT
#define G_TEXT 

#include "raylib.h"

void drawText(const char* text, int x, int y, float scale, Color color, int layer);
void drawTextF(const char* text, int x, int y, float scale, Color color, int layer, ...);
void textF(const char* text, int x, int y, ...);

#endif