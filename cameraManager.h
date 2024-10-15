#ifndef CAMERA_MANAGER
#define CAMERA_MANAGER

#include "raylib.h"

void CameraInit();
void CameraUnload();
void CameraUpdate();
Ray CameraGetMouseRay();


#endif