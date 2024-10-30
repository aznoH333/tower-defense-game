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
void drawPlaneS(const char* textureName, Vector3 position, Vector3 rotation, float scale, Vector4 modelScale);
void drawBillboard(const char* textureName, Vector3 position, float scale, bool flip);
void drawBoundingBox(BoundingBox box, Color color);
Camera* getCamera();
void CameraSetRotation(Camera* this, Vector3 rotation);
float CameraGet2AxisRotation(Camera* this);
float CameraGet2AxisRotationTowards(Camera* this, Vector3 other);


#endif