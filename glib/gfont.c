#include "gfont.h"
#include "raylib.h"
#include "rlgl.h"
#include "gcollections.h"
#include <stdio.h>
#include <stdlib.h>
#include "gutil.h"


//================================================
// Variables
//================================================
Font font;
Vector* fontDrawingQueue;
#define MAX_TEXT_LENGTH 255


//================================================
// Structs
//================================================
struct FontDrawData{
    char* text;
    float x;
    float y;
    float scale;
};
typedef struct FontDrawData FontDrawData ;

//================================================
// Init & dispose
//================================================
void FontInit(){
    font = GetFontDefault();//LoadFont("./gadata/font.png"); 
    fontDrawingQueue = VectorInit();
}


void drawQueueClear(){
    for (int i = 0; i < fontDrawingQueue->elementCount; i++){
        FontDrawData* data = VectorGet(fontDrawingQueue, i);
        free(data->text);
        free(data);
    }
    VectorClearM(fontDrawingQueue, true);
};


void FontDispose(){
    UnloadFont(font);
    drawQueueClear();
    VectorFreeM(fontDrawingQueue, true);
}


//================================================
// Font draw
//================================================
void FontDraw2D(float startX, float startY, float scale, const char* format, ...){
    va_list args;

    va_start(args, format);
    FontDrawData* data = malloc(sizeof(FontDrawData));
    data->x = startX;
    data->y = startY;
    data->scale = scale;
    
    data->text = malloc(MAX_TEXT_LENGTH);
    vsprintf(data->text, format, args);

    VectorPush(fontDrawingQueue, data);
    va_end(args);
}


void FontDrawToTexture(RenderTexture2D* texture, float startX, float startY, float scale, const char* format, ...){
    va_list args;
    va_start(args, format);

    BeginTextureMode(*texture);
    char* text = malloc(MAX_TEXT_LENGTH);
    vsprintf(text, format, args);
    DrawTextEx(font, text, (Vector2){startX, startY}, scale, 1.0f, WHITE);
    free(text);
    EndTextureMode();

    va_end(args);
}


//================================================
// Font update
//================================================
void FontDrawUpdate(){
    
    
    foreach(FontDrawData*, data, fontDrawingQueue){
        DrawTextEx(font, data->text, (Vector2){data->x, data->y}, data->scale, 1.0f, WHITE);

    }
    drawQueueClear();
}