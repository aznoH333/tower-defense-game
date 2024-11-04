#ifndef CAMERA_MANAGER
#define CAMERA_MANAGER

#include "raylib.h"

void CameraInit();
void CameraUnload();
void CameraUpdate();
Vector3 CameraGetPosition();
Ray CameraGetMouseRay();


#endif