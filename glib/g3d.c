#include "g3d.h"
#include "gcollections.h"
#include "gframework.h"
#include "gutil.h"
#include "raylib.h"
#include "gdrawing.h"
#include <math.h>
#include "raymath.h"

//======================================================
// Structs
//======================================================
struct Draw3DData{
    int spriteIndex;
    Vector3 position;
    Vector3 rotation;
    float scale;
    bool flip;
}; typedef struct Draw3DData Draw3DData ;


//======================================================
// Variables
//======================================================
Mesh plane;
Model planeModel;
Camera3D camera = { 0 };
Vector* drawQueue;
Vector* billboardQueue;
Shader alphaDiscard;
    

//======================================================
// Comparison functions
//======================================================
char billboardDistanceCompare(void* billboard1, void* billboard2){
    //float distance1 = distanceBetweenPoints(camera.position, ((Draw3DData*)billboard1)->position);
    //float distance2 = distanceBetweenPoints(camera.position, ((Draw3DData*)billboard2)->position);
    float distance1 = Vector3Distance(camera.position, ((Draw3DData*)billboard1)->position);
    float distance2 = Vector3Distance(camera.position, ((Draw3DData*)billboard2)->position);


    if (distance2 < distance1){
        return -1;
    }
    return distance2 > distance1;
}


//======================================================
// Setup and dispose
//======================================================
void initG3D(){
    // temporary camera setup
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // prep polygons
    plane = GenMeshPlane(1, 1, 1, 1);
    planeModel = LoadModelFromMesh(plane);

    //raylib util functions
    gfullscreen();
    DisableCursor();

    // queue init
    drawQueue = VectorInit();
    billboardQueue = VectorInit();

    alphaDiscard = LoadShader(NULL, "gamedata/resources/shaders/discard.fs");
}


void disposeG3D(){
    // unload polygons
    //UnloadMesh(plane);
    UnloadModel(planeModel);
    VectorFree(drawQueue);
    VectorFree(billboardQueue);
    UnloadShader(alphaDiscard);
}


//======================================================
// Translation functions
//======================================================
Matrix vec3ToRotations(Vector3* rotation){
    float z = rotation->z;
    float y = rotation->y;
    float x = rotation->x;
    
    Matrix out =    {
                        1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f,
                    };
    
    // rotation along x axis
    out = matrixMultiplication(out, (Matrix) {   1.0f, 0.0f, 0.0f, 0.0f,
                                                        0.0f, cosf(x), -sinf(x), 0.0f,
                                                        0.0f, sinf(x), cosf(x), 0.0f,
                                                        0.0f, 0.0f, 0.0f, 1.0f});

    // rotation along y axis
    out = matrixMultiplication(out, (Matrix) {   cosf(y), 0.0f, sinf(y), 0.0f,
                                                        0, 1.0f, 0.0f, 0.0f,
                                                        -sinf(y), 0.0f, cosf(y), 0.0f,
                                                        0.0f, 0.0f, 0.0f, 1.0f});

    // rotation along z axis
    out = matrixMultiplication(out, (Matrix) {   cosf(z), -sinf(z), 0.0f, 0.0f,
                                                        sinf(z), cosf(z), 0.0f, 0.0f,
                                                        0.0f, 0.0f, 1.0f, 0.0f,
                                                        0.0f, 0.0f, 0.0f, 1.0f});


    return out;
}


//======================================================
// Update
//======================================================
void drawPlaneData(Draw3DData* data){
    // set texture
    planeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *getTexture(data->spriteIndex);

	planeModel.transform = vec3ToRotations(&data->rotation);
	DrawModel(planeModel, data->position, data->scale, WHITE);
}


void drawBillboardData(Draw3DData* data){
    
    Texture2D texture = *getTexture(data->spriteIndex);
    Rectangle source = (Rectangle){0.0f, 0.0f, texture.width * (boolToSign(data->flip)), texture.height};
    
    

    //DrawBillboard(camera, *getTexture(data->spriteIndex), data->position, data->scale, WHITE);
    DrawBillboardRec(camera, texture, source, data->position, (Vector2){data->scale, data->scale}, WHITE);
}


void updateG3D(){
    // update camera (temporary)
    UpdateCamera(&camera, CAMERA_FREE);

    BeginDrawing();
    
    ClearBackground(BLACK);
    BeginMode3D(camera);
    BeginShaderMode(alphaDiscard);

    // draw planes
    for (int i = 0; i < drawQueue->elementCount; i++){
        drawPlaneData(VectorGet(drawQueue, i));
    }
    VectorClear(drawQueue);

    // draw billboards
    for (int i = 0; i < billboardQueue->elementCount; i++){
        drawBillboardData(VectorGet(billboardQueue, i));
    }
    VectorClear(billboardQueue);

    EndShaderMode();
    EndMode3D();
    EndDrawing();
}


//======================================================
// Model drawing
//======================================================
void drawPlane(const char* textureName, Vector3 position, Vector3 rotation, float scale){
    Draw3DData* drawData = malloc(sizeof(Draw3DData));
    drawData->spriteIndex = getTextureIndex(textureName);
    drawData->position = position;
    drawData->rotation = rotation;
    drawData->scale = scale;
    drawData->flip = false;
    VectorPush(drawQueue, drawData);
}


void drawBillboard(const char* textureName, Vector3 position, float scale, bool flip){
    Draw3DData* drawData = malloc(sizeof(Draw3DData));
    drawData->spriteIndex = getTextureIndex(textureName);
    drawData->position = position;
    drawData->rotation = (Vector3){};
    drawData->scale = scale;
    drawData->flip = flip;
    VectorPush(billboardQueue, drawData);
}


//======================================================
// Camera
//======================================================
Camera* getCamera(){
    return &camera;
}


void CameraSetRotation(Camera* this, Vector3 rotation){
    gLog(LOG_ERR, "Not implemented yet");
}


float CameraGet2AxisRotation(Camera* this){
    Vector3 normalizedCameraTarget = normalizeVector((Vector3){-this->position.x + this->target.x, -this->position.y + this->target.y, -this->position.z + this->target.z});

    return -dirTowards(0, 0, normalizedCameraTarget.x, normalizedCameraTarget.z) + ROT_270;
}


float CameraGet2AxisRotationTowards(Camera* this, Vector3 other){
    return -dirTowards(this->position.x, this->position.z, other.x, other.z) + ROT_270;
}