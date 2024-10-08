#include "g3d.h"
#include "gframework.h"
#include "gutil.h"
#include "raylib.h"
#include "gdrawing.h"
#include <math.h>

//======================================================
// Variables
//======================================================
Mesh plane;
Model planeModel;
Camera3D camera = { 0 };
    

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

}


void disposeG3D(){
    // unload polygons
    //UnloadMesh(plane);
    UnloadModel(planeModel);
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
void updateG3D(){
    // update camera (temporary)
    UpdateCamera(&camera, CAMERA_FREE);

    BeginDrawing();
    
    ClearBackground(BLACK);
    BeginMode3D(camera);

    drawPlane("debug_textures_0001", (Vector3){1.0f,0,0}, (Vector3){0.0f,0.0f, 0.0f}, 1.0f);
    drawPlane("debug_textures_0001", (Vector3){0,0,0}, (Vector3){(float)getGlobalTimer() * 0.1f,(float)getGlobalTimer() * 0.01f, (float)getGlobalTimer() * 0.05f}, 1.0f);
    //DrawCube((Vector3){0, 0, 0}, 2.0f, 2.0f, 2.0f, RED);
    //DrawPlane((Vector3){0, 0, 0}, (Vector2){1.0f, 1.0f}, RED);

    EndMode3D();
    EndDrawing();
}


//======================================================
// Model drawing
//======================================================
void drawPlane(const char* textureName, Vector3 position, Vector3 rotation, float scale){
    // set texture
    planeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *getTexture(textureName);

	planeModel.transform = vec3ToRotations(&rotation);
	DrawModel(planeModel, position, scale, WHITE);
}
