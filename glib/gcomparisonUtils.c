#include "gcomparisonUtils.h"
#include "raylib.h"
#include "gutil.h"


bool Vec3Equals(void* element1, void* element2){
    Vector3* a = element1;
    Vector3* b = element2;

    return a->x == b->x && a->y == b->y && a->z == b->z;
}


bool Vec2Equals(void* element1, void* element2){
    Vector2* a = element1;
    Vector2* b = element2;

    return a->x == b->x && a->y == b->y;
}


bool Vec4Equals(void* element1, void* element2){
    Vector4* a = element1;
    Vector4* b = element2;
    return a->x == b->x && a->y == b->y && a->z == b->z && a->w == b->w;
}
