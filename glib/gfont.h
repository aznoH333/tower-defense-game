#ifndef G_FONT
#define G_FONT

#include "raylib.h"

void FontInit();
void FontDispose();
void FontDraw2D(float startX, float startY, float scale, const char* format, ...);
void FontDrawToTexture(RenderTexture2D* texture, float startX, float startY, float scale, const char* format, ...);
void FontDrawUpdate();


#endif