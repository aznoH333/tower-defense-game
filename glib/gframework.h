#ifndef G_FRAMEWORK
#define G_FRAMEWORK


#include "raylib.h"
#include "gutil.h"
#include <math.h>
#include <string.h>
#include "gcollections.h"
#include <stdlib.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define DEFAULT_CAMERA_ZOOM 3.6f
#define DEFAULT_GAME_WIDTH (int)(SCREEN_WIDTH / DEFAULT_CAMERA_ZOOM)
#define DEFAULT_GAME_HEIGHT (int)(SCREEN_HEIGHT / DEFAULT_CAMERA_ZOOM)// misc


int getGlobalTimer();

// camera
void screenShake(float ammount);
void updateCamera();
Vector2 getInWorldMousePosition();
Vector2 getOnScreenMousePosition();
void setCameraPos(Vector2 pos);
void addCameraZoom(float zoom);
void setCameraZoom(float zoom);
void resetCameraZoom();


//public draw functions
void drawRFSC(int spriteIndex, int x, int y, float rotation, int flip, float scale, Color c, int layer);
void drawRSC(int spriteIndex, int x, int y, float rotation, float scale, Color c, int layer);
void drawFSC(int spriteIndex, int x, int y, int flip, float scale, Color c, int layer);
void drawFC(int spriteIndex, int x, int y, bool flip, Color c, int layer);
void drawFS(int spriteIndex, int x, int y, bool flip, float scale, int layer);

void drawR(int spriteIndex, int x, int y, float rotation, int layer);
void drawC(int spriteIndex, int x, int y, Color c, int layer);
void drawS(int spriteIndex, int x, int y, float scale, int layer);
void drawF(int spriteIndex, int x, int y, int flip, int layer);
void draw(int spriteIndex, int x, int y, int layer);


// sounds
void playSound(const char* soundName);
void playSoundVolume(const char* soundName, float value);

// controll functions
void fUpdate();
void initFramework();
void disposeFramework();
void gfullscreen();
void closeGame();
bool isGameRunning();





#endif
