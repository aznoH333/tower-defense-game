#ifndef PATH
#define PATH

#include <raylib.h>
#include "worldDirections.h"


#define MAX_PATH_POINTS 8



struct PathPoint{
    char x;
    char y;
    char direction;
}; typedef struct PathPoint PathPoint;


struct Path {
    PathPoint points[MAX_PATH_POINTS];
    char pointLengths[MAX_PATH_POINTS - 1];
    unsigned char pointCount;
    float pathLength;
}; typedef struct Path Path;


// point functions
PathPoint PathPointInit(unsigned char x, unsigned char y, char direction);

// path functions
Path PathInit();
void PathAddPoint(Path* this, unsigned char x, unsigned char y, char direction);
bool PathHasReachedEnd(Path* this, float pathProgress);
Vector3 PathResolveEnemyLocation(Path* this, float pathProgress, float* rotation);

#endif