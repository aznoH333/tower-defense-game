#include "path.h"
#include "g3d.h"
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


//================================================
// Update enemy
//================================================
Vector3 PathResolveEnemyLocation(Path* this, float pathProgress, float* rotation){
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
        
        float currentSegmentProgress = pathProgress - combinedLength;
        switch (currentPoint->direction) {
            case DIRECTION_UP:
                y -= currentSegmentProgress;
                *rotation = ROT_270;
                break;
            case DIRECTION_DOWN:
                y += currentSegmentProgress;
                *rotation = ROT_90;
                break;
            case DIRECTION_RIGHT:
                x += currentSegmentProgress;
                *rotation = 0.0f;
                break;
            case DIRECTION_LEFT:
                x -= currentSegmentProgress;
                *rotation = ROT_180;
                break;
        }

        return (Vector3){x, 0.25f, y};
    }

    return (Vector3){0,0,0};
}


bool PathHasReachedEnd(Path* this, float pathProgress){
    return pathProgress > this->pathLength;
}