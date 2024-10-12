#include "path.h"
#include "gutil.h"
#include "worldDirections.h"
#include <raylib.h>


//================================================
// Path point
//================================================
PathPoint PathPointInit(unsigned char x, unsigned char y, char direction){
    return (PathPoint){x, y, direction};
}


//================================================
// Init
//================================================
Path PathInit(){
    return (Path){{}, 0, 0.0f};
}


//================================================
// Update
//================================================
Vector3 PathResolveEnemyLocation(Path* this, float pathProgress){
    if (this->pointCount < 2){
        gLog(LOG_ERR, "Path doesnt have enough points to calculat position");
    }


    int pointIndex = -1;
    unsigned char combinedLength = 0;
    for (int i = 0; i < this->pointCount - 1; i++){
        combinedLength += this->pointLengths[i];
        
        if (pathProgress < combinedLength){
            pointIndex = i;
            combinedLength -= this->pointLengths[i];
            break;
        }
    }

    if (pointIndex == -1){
        // idk
    }else {
        PathPoint* currentPoint = &this->points[pointIndex];
        
        float x = currentPoint->x;
        float y = currentPoint->y;
        
        if (currentPoint->direction <= DIRECTION_DOWN){
            y += pathProgress - combinedLength;
        }else {
            x += pathProgress - combinedLength;
        }

        return (Vector3){x, 0.25f, y};
    }

    return (Vector3){0,0,0};
}


void PathAddPoint(Path* this, unsigned char x, unsigned char y, char direction){
    if (this->pointCount >= MAX_PATH_POINTS){
        gLog(LOG_ERR, "Max path points exceeded");
    }

    this->points[this->pointCount] = PathPointInit(x, y, direction);
    this->pointCount++;

    //recalculate point lengths
    if (this->pointCount < 2){
        return;
    }

    unsigned char totalLength = 0;
    for (int i = 0; i < this->pointCount - 1; i++){
        PathPoint* currentPoint = &this->points[i];
        PathPoint* nextPoint = &this->points[i + 1];

        char distance;
        
        if (currentPoint->direction == DIRECTION_UP || currentPoint->direction == DIRECTION_DOWN){
            distance = chabs(currentPoint->y - nextPoint->y);
        }else {
            distance = chabs(currentPoint->x - nextPoint->x);
        }

        this->pointLengths[i] = distance;
        totalLength += distance;
    }

    this->pathLength = totalLength;

}


bool PathHasReachedEnd(Path* this, float pathProgress){
    return pathProgress > this->pathLength;
}
