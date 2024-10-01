#include "gdrawing.h"
#include "gcollections.h"
#include <stdlib.h>
#include "gframework.h"


//------------------------------------------------
// Variables
//------------------------------------------------

RenderTexture2D renderTexture;
Vector* drawingLayers[LAYER_COUNT];
Vector* loadedTextures;


//------------------------------------------------
// Structs
//------------------------------------------------

struct DrawingData{
	int spriteIndex;
	int x;
	int y;
	float rotation;
	float scale;
	Color c;
	int flip;
};
typedef struct DrawingData DrawingData;


//------------------------------------------------
// Setup & teardown
//------------------------------------------------

void initDrawingLayers(){
	for (int i = 0; i < LAYER_COUNT; i++){
		drawingLayers[i] = VectorInit();
	}
}

void cleanDrawingLayers(){
	for (int i = 0; i < LAYER_COUNT; i++){
		VectorFree(drawingLayers[i]);
	}
}

void loadTextures(){
    loadedTextures = VectorInit();
}

void unloadTextures(){
	for (int i = 0; i < loadedTextures->elementCount; i++){
		UnloadTexture(*((Texture2D*)(VectorGet(loadedTextures, i))));
	}
	VectorFree(loadedTextures);
}


//------------------------------------------------
// Drawing logic
//------------------------------------------------

void insertDrawRequest(const char* spriteName, int x, int y, float rotation, char flip, float scale, Color c, char layer){
	// init data
	DrawingData* data = malloc(sizeof(DrawingData));
	//data->spriteIndex = spriteIndex;
	data->x = x;
	data->y = y;
	data->scale = scale;
	data->rotation = rotation;
	data->c = c;
	data->flip = flip;


	// push to vector
	VectorPush(drawingLayers[layer], data);
}

void drawSpriteData(DrawingData* data){
	int flip = data->flip % 4;
	bool flipHorizontaly = flip == FLIP_HORIZONTAL || flip == FLIP_BOTH;
	bool flipVerticaly = flip == FLIP_VERTICAL || flip == FLIP_BOTH;
	/*
	Rectangle src = {
		(data->spriteIndex % data->targetSheet->width) * data->targetSheet->defaultSpriteSize, 
		floor((float)data->spriteIndex / data->targetSheet->width) * data->targetSheet->defaultSpriteSize, 
		data->targetSheet->defaultSpriteSize, 
		data->targetSheet->defaultSpriteSize};*/

	if (flipHorizontaly){
		//src.width *= -1;
	}

	if (flipVerticaly){
		//src.height *= -1;
	}
	
	
	/*
	Rectangle dest = {data->x + data->targetSheet->originOffset, data->y + data->targetSheet->originOffset, data->targetSheet->defaultSpriteSize * data->scale, data->targetSheet->defaultSpriteSize * data->scale};
	
	
	Vector2 origin = {data->targetSheet->originOffset, data->targetSheet->originOffset};
	DrawTexturePro(data->targetSheet->spriteSheetTexture, src, dest, origin, data->rotation, data->c);*/
}

void drawLayer(int layer){
	for (int i = 0; i < drawingLayers[layer]->elementCount;i++){
		drawSpriteData((DrawingData*)VectorGet(drawingLayers[layer], i));
	}
	VectorClear(drawingLayers[layer]);
}


//------------------------------------------------
// Public functions
//------------------------------------------------

void drawUpdate(Camera2D* cam, const Color* backgroundColor, unsigned short currentScreenWidth, unsigned short currentScreenHeight, unsigned short currentRenderTextureOffset, float currentScalingFactor){
    BeginTextureMode(renderTexture);
    BeginMode2D(*cam);
    ClearBackground(*backgroundColor);
	
	for (int i = 0; i < LAYER_STATIC_UI; i++){
		drawLayer(i);
	}

	EndMode2D();


	drawLayer(LAYER_STATIC_UI);


    EndTextureMode();
    
    BeginDrawing();
    ClearBackground(BLACK);
    Rectangle r = { 0, 0, (float)(renderTexture.texture.width), (float)(-renderTexture.texture.height) };
    Rectangle r2 = { currentRenderTextureOffset, 0, (float)(currentScreenWidth) * currentScalingFactor, (float)(currentScreenHeight) };
    Vector2 v = {0, 0};
    DrawTexturePro(renderTexture.texture,r,r2,v,0,WHITE);

    EndDrawing();
}


void initDrawing(){
    initDrawingLayers();

	renderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    loadTextures();
}
void disposeDrawing(){
    cleanDrawingLayers();

    unloadTextures();

	UnloadRenderTexture(renderTexture);
}