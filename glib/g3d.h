#ifndef GAME_3D
#define GAME_3D

#include <raylib.h>

void initG3D();
void disposeG3D();
void updateG3D();
void drawPlane(const char* textureName, Vector3 position, Vector3 rotation, float scale);

#endif