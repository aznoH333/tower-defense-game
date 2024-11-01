#include "gframework.h"
#include "gdrawing.h"
#include "g3d.h"
#include "gfont.h"
#include "ggamestate.h"
//------------------------------------------------------
// Conf
//------------------------------------------------------

const char* WINDOW_NAME = "gameska";
const int DEFAULT_SPRITE_SIZE = 16;

const int SPRITE_ORIGIN_OFFSET = DEFAULT_SPRITE_SIZE >> 1;
const Color BACKGROUND_COLOR = {22, 7, 18, 255};

int currentScreenWidth = SCREEN_WIDTH;
int currentScreenHeight = SCREEN_HEIGHT;


//------------------------------------------------------
// sprites
//------------------------------------------------------
struct FrameworkSpriteSheet{
	Texture2D spriteSheetTexture;
	int width;
	int height;
	int defaultSpriteSize;
	int originOffset;
};
typedef struct FrameworkSpriteSheet FrameworkSpriteSheet;


FrameworkSpriteSheet mainSpriteSheet;
FrameworkSpriteSheet initSpriteSheet(const char* spriteSheetPath, int defaultSpriteSize){
	FrameworkSpriteSheet out;
	out.spriteSheetTexture = LoadTexture(spriteSheetPath);
	
	
	if (defaultSpriteSize != -1){
		out.width = out.spriteSheetTexture.width / defaultSpriteSize;
		out.height = out.spriteSheetTexture.height / defaultSpriteSize;
		out.defaultSpriteSize = defaultSpriteSize;
	}else {
		out.defaultSpriteSize = out.spriteSheetTexture.width;
		out.width = 1;
		out.height = 1;
	}
	
	
	
	out.originOffset = defaultSpriteSize >> 1;
	return out;
}

void unloadSpriteSheet(FrameworkSpriteSheet spriteSheet){
	UnloadTexture(spriteSheet.spriteSheetTexture);
}




//------------------------------------------------------
// Variables
//------------------------------------------------------
FrameworkSpriteSheet loadedSheet;
FrameworkSpriteSheet fontSheet;

Vector2 actualCameraPos = {0,0};
Camera2D cam;
Camera3D cam3d;
float scalingFactor;
int renderTextureOffset;
float screenShakeAmmount = 0.0f;
int fTimer = 0;
char currentFrameworkType;



//------------------------------------------------------
// misc
//------------------------------------------------------
int getGlobalTimer(){
	return fTimer;
}

//------------------------------------------------------
// camera
//------------------------------------------------------
void screenShake(float ammount){
	screenShakeAmmount += ammount;
}

void updateCamera(){
	screenShakeAmmount = fmin(screenShakeAmmount, 10);
	Vector2 vec = {actualCameraPos.x + sin(fTimer) * screenShakeAmmount, actualCameraPos.y + cos(fTimer) * screenShakeAmmount};
	cam.target = vec;

	if (screenShakeAmmount < 0.1f){
		screenShakeAmmount = 0;
	}else {
		screenShakeAmmount *= 0.2f;
	}

}

Vector2 getInWorldMousePosition(){
	Vector2 out = GetMousePosition();
	
	out.x /= cam.zoom;
	out.y /= cam.zoom;


	out.x += cam.target.x;
	out.y += cam.target.y;

	return out;
}

Vector2 getOnScreenMousePosition(){
	return GetMousePosition();
}

void setCameraPos(Vector2 pos){
	actualCameraPos = pos;
}


void addCameraZoom(float zoom){
	cam.zoom += zoom;
}

void setCameraZoom(float zoom){
	cam.zoom = zoom;
}

void resetCameraZoom(){
	cam.zoom = DEFAULT_CAMERA_ZOOM;
}


//------------------------------------------------------
// screen
//------------------------------------------------------
int getScreenWitdth(){
	return currentScreenWidth;
}


int getScreenHeight(){
	return currentScreenHeight;
}


//------------------------------------------------------
// drawing
//------------------------------------------------------
void drawRFSC(const char* spriteName, int x, int y, float rotation, int flip, float scale, Color c, int layer){
	insertDrawRequest(spriteName, x, y, rotation, flip, scale, c, layer);
}

void drawRSC(const char* spriteName, int x, int y, float rotation, float scale, Color c, int layer){
	insertDrawRequest(spriteName, x, y, rotation, FLIP_NONE, scale, c, layer);
}

void drawFSC(const char* spriteName, int x, int y, int flip, float scale, Color c, int layer){
	drawRFSC(spriteName, x, y, 0.0f, flip, scale, c, layer);
}

void drawFC(const char* spriteName, int x, int y, bool flip, Color c, int layer){
	drawRFSC(spriteName, x, y, 0.0f, flip, 1.0f, c, layer);
}

void drawFS(const char* spriteName, int x, int y, bool flip, float scale, int layer){
	drawRFSC(spriteName, x, y, 0.0f, flip, scale, WHITE, layer);
}


void drawR(const char* spriteName, int x, int y, float rotation, int layer){
	drawRSC(spriteName, x, y, rotation, 1.0f, WHITE, layer);
}

void drawC(const char* spriteName, int x, int y, Color c, int layer){
	drawRSC(spriteName, x, y, 0.0f, 1.0f, c, layer);
}

void drawS(const char* spriteName, int x, int y, float scale, int layer){
	drawRSC(spriteName, x, y, 0.0f, scale, WHITE, layer);
}

void drawF(const char* spriteName, int x, int y, int flip, int layer){
	drawRFSC(spriteName, x, y, 0.0f, flip, 1.0f, WHITE, layer);
}

void draw(const char* spriteName, int x, int y, int layer){	
	drawRSC(spriteName, x, y, 0.0f, 1.0f, WHITE, layer);
}


//---------------------------------------------------
// control
//---------------------------------------------------
void fUpdate(){
	fTimer++;
	
	updateGGamestate();
	if (currentFrameworkType == FRAMEWORK_TYPE_3D){
		updateG3D();
	}else {
		drawUpdate(&cam, &BACKGROUND_COLOR, currentScreenWidth, currentScreenHeight, renderTextureOffset, scalingFactor);
		updateCamera();
	}
}


void gfullscreen(){
	int tWidth = currentScreenWidth;
	int tHeight = currentScreenHeight;
	
	int monitor = GetCurrentMonitor();

	if (IsWindowFullscreen())
    {
        SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

		currentScreenWidth = SCREEN_WIDTH;
		currentScreenHeight = SCREEN_HEIGHT;
    }
	else
    {
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));

		currentScreenWidth = GetMonitorWidth(monitor);
		currentScreenHeight = GetMonitorHeight(monitor);
    }
	// update scaling factor
	//scalingFactor = currentScreenWidth /(float)(GetScreenWidth());
	gLog(LOG_INF, "Changing screen resolution from w[%d] h[%d] to w[%d] h[%d]", tWidth, tHeight, currentScreenWidth, currentScreenHeight);

	scalingFactor = 1.0f;// scaling factor should be 1 or the fullscreen bugs out??
	ToggleFullscreen();
}

bool shouldRun = true;
void closeGame(){
	shouldRun = false;
}
bool isGameRunning(){
	return !WindowShouldClose() && shouldRun;
}

//------------------------------------------------------
// sounds
//------------------------------------------------------
/*
Map* soundMap;
void playSound(const char* soundName){
	playSoundVolume(soundName, 0.4f);
}

void playSoundVolume(const char* soundName, float volume){
	Sound* s = mapGet(soundMap, soundName);
	SetSoundVolume(*s, volume);
	PlaySound(*s);
}

void loadSounds(){
	soundMap = initMap();
	Vector* soundFiles = getFolderContents("./resources/sounds/");

	for (int i = 0; i < soundFiles->elementCount; i++){
		// copy file name
		char* fileName = vectorGet(soundFiles, i);
		char* mapKey = malloc(sizeof(char) * (strLength(fileName) + 1));
		memcpy(mapKey, fileName, sizeof(char) * (strLength(fileName) + 1));
		// copy sound to heap
		char* soundFilePath = strConcat("./resources/sounds/", fileName);
		Sound s = LoadSound(soundFilePath);
		free(soundFilePath);
		Sound* mapValue = malloc(sizeof(Sound));
		memcpy(mapValue, &s, sizeof(s));

		// put in map
		mapPut(soundMap, mapKey, mapValue);
    }
    vectorFree(soundFiles);
}

void unloadSounds(){
	for (int i = 0; i < soundMap->elements->elementCount; i++){
		Sound* s = VectorGet(soundMap->elements, i);
		UnloadSound(*s);
	}
	
	mapFree(soundMap);
}*/



//------------------------------------------------------
// init
//------------------------------------------------------
void initFramework(char frameworkType){
	currentFrameworkType = frameworkType;
	
	// raylib stuff
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME);
	InitAudioDevice();
	SetTargetFPS(60);
	
	if (frameworkType == FRAMEWORK_TYPE_3D){
		initG3D();
	}

	// framework init
	//loadedSheet = initSpriteSheet("resources/spritesheet.png", DEFAULT_SPRITE_SIZE);
	FontInit();
	scalingFactor = currentScreenWidth /(float)(GetScreenWidth());
	renderTextureOffset = ((GetScreenWidth()) / 2) - (SCREEN_WIDTH / 2);
	cam.zoom = DEFAULT_CAMERA_ZOOM;
	initDrawing();
	initGGamestate();
	//loadSounds();
}


//------------------------------------------------------
// dispose
//------------------------------------------------------
void disposeFramework(){
	
	if (currentFrameworkType == FRAMEWORK_TYPE_3D){
		disposeG3D();
	}	
	
	//unloadSpriteSheet(loadedSheet);
	disposeDrawing();
	disposeGGamestate();
	//unloadSounds();

	// dispose raylib
	CloseAudioDevice();
	CloseWindow();
	FontDispose();
}

