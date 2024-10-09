#ifndef GAME_3D
#define GAME_3D

#include <raylib.h>

// usefull constants
#define ROT_90 PI/2
#define ROT_180 PI
#define ROT_270 ROT_180 + ROT_90


void initG3D();
void disposeG3D();
void updateG3D();
void drawPlane(const char* textureName, Vector3 position, Vector3 rotation, float scale);
void drawBillboard(const char* textureName, Vector3 position, float scale);

#endif