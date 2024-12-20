#include "gdrawing.h"
#include "gcollections.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include "gframework.h"
#include "gutil.h"


//------------------------------------------------
// Variables
//------------------------------------------------
RenderTexture2D renderTexture;
Vector* drawingLayers[LAYER_COUNT];
Vector* loadedTextures;
Vector* spriteIndices;

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


const char* SPRITES_PATH = "./gamedata/resources/sprites";
void loadTextures(){
	loadedTextures = VectorInit();
	spriteIndices = VectorInit();

	Vector* textureFilePaths = getFolderContents(SPRITES_PATH);

	for (int i = 0; i < textureFilePaths->elementCount; i++){
		char* filePath = VectorGet(textureFilePaths, i);

		// add to texture vec
		Texture2D texture = LoadTexture(filePath);
		Texture2D* heapTexturePointer = malloc(sizeof(Texture2D));
		memcpy(heapTexturePointer, &texture, sizeof(Texture2D));
		VectorPush(loadedTextures, heapTexturePointer);
		

		// add name to dictionary
		char* fileName = getFileName(filePath);
		VectorPush(spriteIndices, fileName);
	}
}


void unloadTextures(){
	for (int i = 0; i < loadedTextures->elementCount; i++){
		UnloadTexture(*((Texture2D*)(VectorGet(loadedTextures, i))));
	}
	VectorFree(loadedTextures);
	VectorFree(spriteIndices);
}


//------------------------------------------------
// Drawing logic
//------------------------------------------------
void insertDrawRequest(const char* spriteName, int x, int y, float rotation, char flip, float scale, Color c, char layer){
	
	// get sprite index
	int index = VectorFindStr(spriteIndices, spriteName);
	
	if (index == -1){
		gLog(LOG_ERR, "Sprite not found [%s]", spriteName);
	}

	// init data
	DrawingData* data = malloc(sizeof(DrawingData));
	data->spriteIndex = index;
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
	Texture2D* targetSprite = VectorGet(loadedTextures, data->spriteIndex);

	Rectangle src = {
		0, 
		0, 
		targetSprite->width, 
		targetSprite->height};

	if (flipHorizontaly){
		src.width *= -1;
	}

	if (flipVerticaly){
		src.height *= -1;
	}
	
	
	Vector2 origin = {targetSprite->width >> 1, targetSprite->height >> 1};
	
	Rectangle dest = {data->x + origin.x, data->y + origin.y, src.width * data->scale, src.height * data->scale};
	
	
	DrawTexturePro(*targetSprite, src, dest, origin, data->rotation, data->c);
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


void drawToRenderTexture(RenderTexture2D* target, const char* spriteName, float x, float y, char flip, float scale, Color c){
	BeginTextureMode(*target);
	int spriteIndex = getTextureIndex(spriteName);
	flip %= 4;
	bool flipHorizontaly = flip == FLIP_HORIZONTAL || flip == FLIP_BOTH;
	bool flipVerticaly = flip == FLIP_VERTICAL || flip == FLIP_BOTH;
	gLog(LOG_INF, "%s %s", boolToStr(flipHorizontaly), boolToStr(flipVerticaly));
	Texture2D* targetSprite = VectorGet(loadedTextures, spriteIndex);
	Rectangle src = {
		0, 
		0, 
		targetSprite->width, 
		targetSprite->height
	};
	// scuffed behaviour to unfuck render texture 2d
	// for some reason render texture 2d is inverted by default
	// this is the cleanes way i found to unfuck the situation
	if (flipHorizontaly){
		src.width *= -1;
	}

	if (flipVerticaly){
		src.height *= -1;
	}
	
	//x = target->texture.width - x;
	//y = target->texture.height - y;
	
	Vector2 origin = {targetSprite->width >> 1, targetSprite->height >> 1};
	
	Rectangle dest = {x + origin.x, y + origin.y, src.width * scale, src.height * scale};
	
	
	DrawTexturePro(*targetSprite, src, dest, origin, 0.0f, c);

	EndTextureMode();
}


Texture2D* getTexture(int spriteIndex){
	return VectorGet(loadedTextures, spriteIndex);
}

int getTextureIndex(const char* textureName){
	int index = VectorFindStr(spriteIndices, textureName);

	if (index == -1){
		gLog(LOG_ERR, "Texture not found [%s]", textureName);
	}

	return index;
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