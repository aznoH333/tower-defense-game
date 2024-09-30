#ifndef G_DRAWING
#define G_DRAWING

#include "raylib.h"



#define LAYER_BACKGROUND 0
#define LAYER_WORLD 1
#define LAYER_OBJECTS 2
#define LAYER_EFFECTS 3
#define LAYER_UI 4
#define LAYER_STATIC_UI 5
#define LAYER_COUNT LAYER_STATIC_UI + 1

#define FLIP_NONE 0
#define FLIP_HORIZONTAL 1
#define FLIP_VERTICAL 2
#define FLIP_BOTH 4

// drawing
void insertDrawRequest(const char* spriteName, int x, int y, float rotation, char flip, float scale, Color c, char layer);
void drawUpdate(Camera2D* cam, const Color* backgroundColor, unsigned short currentScreenWidth, unsigned short currentScreenHeight, unsigned short currentRenderTextureOffset, float currentScalingFactor);

void initDrawing();
void disposeDrawing();




#endif