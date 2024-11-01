#include "gfont.h"
#include "raylib.h"
#include "rlgl.h"
#include "gcollections.h"
#include <stdlib.h>


//================================================
// Variables
//================================================
Font font;
Vector* fontDrawingQueue;


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
    font = LoadFont("./gadata/font.png"); 
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
void FontDraw2D(float startX, float startY, float scale, const char* format, va_list args){
    FontDrawData* data = malloc(sizeof(FontDrawData));
    data->x = startX;
    data->y = startY;
    data->scale = scale;


    
    data->text = malloc(strLength(const char *str))
}


void FontDrawToTexture(RenderTexture2D* texture, float startX, float startY, float scale, const char* format, va_list args){

}


//================================================
// Font update
//================================================
void FontDrawUpdate(){

}