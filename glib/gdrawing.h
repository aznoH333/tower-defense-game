#ifndef G_DRAWING
#define G_DRAWING

#include "raylib.h"





#define FLIP_NONE 0
#define FLIP_HORIZONTAL 1
#define FLIP_VERTICAL 2
#define FLIP_BOTH 4



// drawing
void insertDrawRequest(const char* spriteName, int x, int y, float rotation, char flip, float scale, Color c, char layer);
void drawUpdate(Camera2D* cam, const Color* backgroundColor, unsigned short currentScreenWidth, unsigned short currentScreenHeight, unsigned short currentRenderTextureOffset, float currentScalingFactor);
Texture2D* getTexture(int spriteIndex);
int getTextureIndex(const char* textureName);

void initDrawing();
void disposeDrawing();




#endif