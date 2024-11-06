#include "cameraManager.h"
#include "g3d.h"
#include <math.h>
#include "gframework.h"
#include "raylib.h"
#include "worldDirections.h"


//================================================
// Variables
//================================================
#define CAMERA_HEIGHT_OFFSET 8
#define CAMERA_ANGLE ROT_90 / 2.0f
#define CAMERA_MOVEMENT_SPEED 0.15f
#define MOUSE_EDGE_DETECTION_WIDTH 50
#define CAMERA_BOUNDRY_OFFSET 8
Camera* cameraPtr;
Vector2 currentCameraPosition;


//================================================
// Setup & unload
//================================================
void CameraInit(){
    cameraPtr = getCamera();
    currentCameraPosition = (Vector2){8.0f, 16.0f};
    SetMousePosition(getScreenWitdth() / 2, getScreenHeight() / 2);
}


void CameraUnload(){

}


//================================================
// Update
//================================================
bool isMouseNearEdge(char screenEdge){
    return false;
    // disabled for now
    // might return later
    
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    int startX;
    int startY;
    int width;
    int height;

    switch (screenEdge) {
        case DIRECTION_UP:
            startX = 0;
            startY = 0;
            width = getScreenWitdth();
            height = MOUSE_EDGE_DETECTION_WIDTH;
            break;
        case DIRECTION_DOWN:
            startX = 0;
            startY = getScreenHeight() - MOUSE_EDGE_DETECTION_WIDTH;
            width = getScreenWitdth();
            height = MOUSE_EDGE_DETECTION_WIDTH;
            break;
        case DIRECTION_LEFT:
            startX = 0;
            startY = 0;
            width = MOUSE_EDGE_DETECTION_WIDTH;
            height = getScreenHeight();
            break;
        case DIRECTION_RIGHT:
            startX = getScreenWitdth() - MOUSE_EDGE_DETECTION_WIDTH;
            startY = 0;
            width = MOUSE_EDGE_DETECTION_WIDTH;
            height = getScreenHeight();
            break;
        
    }

    return mouseX >= startX && mouseX <= startX + width && mouseY >= startY && mouseY <= startY + height;
}


bool canCameraMoveInDirection(char direction){
    return  (direction == DIRECTION_UP && currentCameraPosition.y > CAMERA_BOUNDRY_OFFSET) ||
            (direction == DIRECTION_DOWN && currentCameraPosition .y < 16 + CAMERA_BOUNDRY_OFFSET) ||
            (direction == DIRECTION_LEFT && currentCameraPosition.x > 0) ||
            (direction == DIRECTION_RIGHT && currentCameraPosition.x < 16); 
}


void CameraUpdate(){
    // controls
    if ((IsKeyDown(KEY_A) || isMouseNearEdge(DIRECTION_LEFT)) && canCameraMoveInDirection(DIRECTION_LEFT)){
        currentCameraPosition.x -= CAMERA_MOVEMENT_SPEED;
    }else if ((IsKeyDown(KEY_D) || isMouseNearEdge(DIRECTION_RIGHT)) && canCameraMoveInDirection(DIRECTION_RIGHT)){
        currentCameraPosition.x += CAMERA_MOVEMENT_SPEED;
    }

    if ((IsKeyDown(KEY_W) || isMouseNearEdge(DIRECTION_UP)) && canCameraMoveInDirection(DIRECTION_UP)){
        currentCameraPosition.y -= CAMERA_MOVEMENT_SPEED;
    }else if ((IsKeyDown(KEY_S) || isMouseNearEdge(DIRECTION_DOWN)) && canCameraMoveInDirection(DIRECTION_DOWN)){
        currentCameraPosition.y += CAMERA_MOVEMENT_SPEED;
    }


    // set position
    cameraPtr->position = (Vector3){currentCameraPosition.x, CAMERA_HEIGHT_OFFSET, currentCameraPosition.y};

    // set target
    cameraPtr->target = (Vector3){currentCameraPosition.x, CAMERA_HEIGHT_OFFSET - cos(CAMERA_ANGLE), currentCameraPosition.y - sin(ROT_90)};
}


//================================================
// getters
//================================================
Ray CameraGetMouseRay(){

    return GetMouseRay((Vector2){GetMouseX(), GetMouseY()}, *cameraPtr);
}


Vector3 CameraGetPosition(){
    return cameraPtr->position;
}
