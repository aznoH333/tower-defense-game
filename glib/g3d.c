#include "g3d.h"
#include "gframework.h"
#include "gutil.h"
#include "raylib.h"
#include "gdrawing.h"
#include <math.h>


//======================================================
// Structs
//======================================================
struct Draw3DData{
    int spriteIndex;
    Vector3 position;
    Vector3 rotation;
    float scale;
    //char type;
}; typedef struct Draw3DData Draw3DData ;


//======================================================
// Variables
//======================================================
Mesh plane;
Model planeModel;
Camera3D camera = { 0 };
Vector* drawQueue;
    

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

    // draw queue
    drawQueue = VectorInit();
}


void disposeG3D(){
    // unload polygons
    //UnloadMesh(plane);
    UnloadModel(planeModel);
    VectorFree(drawQueue);
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


void updateG3D(){
    // update camera (temporary)
    UpdateCamera(&camera, CAMERA_FREE);

    BeginDrawing();
    
    ClearBackground(BLACK);
    BeginMode3D(camera);


    for (int i = 0; i < drawQueue->elementCount; i++){
        drawPlaneData(VectorGet(drawQueue, i));
    }

    VectorClear(drawQueue);

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
    VectorPush(drawQueue, drawData);
}
