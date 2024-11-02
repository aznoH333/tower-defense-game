#ifndef G_FRAMEWORK
#define G_FRAMEWORK


#include "raylib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define DEFAULT_CAMERA_ZOOM 3.6f
#define DEFAULT_GAME_WIDTH (int)(SCREEN_WIDTH / DEFAULT_CAMERA_ZOOM)
#define DEFAULT_GAME_HEIGHT (int)(SCREEN_HEIGHT / DEFAULT_CAMERA_ZOOM)// misc


#define LAYER_BACKGROUND 0
#define LAYER_WORLD 1
#define LAYER_OBJECTS 2
#define LAYER_EFFECTS 3
#define LAYER_UI 4
#define LAYER_STATIC_UI 5
#define LAYER_COUNT LAYER_STATIC_UI + 1


#define FRAMEWORK_TYPE_2D 0
#define FRAMEWORK_TYPE_3D 1


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

// screen
int getScreenWitdth();
int getScreenHeight();


//public draw functions
void drawRFSC(const char* spriteName, int x, int y, float rotation, int flip, float scale, Color c, int layer);
void drawRSC(const char* spriteName, int x, int y, float rotation, float scale, Color c, int layer);
void drawFSC(const char* spriteName, int x, int y, int flip, float scale, Color c, int layer);
void drawFC(const char* spriteName, int x, int y, bool flip, Color c, int layer);
void drawFS(const char* spriteName, int x, int y, bool flip, float scale, int layer);

void drawR(const char* spriteName, int x, int y, float rotation, int layer);
void drawC(const char* spriteName, int x, int y, Color c, int layer);
void drawS(const char* spriteName, int x, int y, float scale, int layer);
void drawF(const char* spriteName, int x, int y, int flip, int layer);
void draw(const char* spriteName, int x, int y, int layer);


// sounds
void playSound(const char* soundName);
void playSoundVolume(const char* soundName, float value);

// controll functions
void fUpdate();
void initFramework(char frameworkType);
void disposeFramework();
void gfullscreen();
void closeGame();
bool isGameRunning();





#endif
