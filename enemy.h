#ifndef ENEMY 
#define ENEMY 

#include "entities.h"

struct Enemy{
    unsigned char pathIndex;
    unsigned short health;
    float movementSpeed;
    float pathProgress;
    unsigned char animationTimer;
}; typedef struct Enemy Enemy;


void EnemyUpdate(Entity* this);
void EnemyCollide(Entity* this, Entity* other);
void EnemyDestroy(Entity* this);
void EnemyClean(Entity* this);
Entity* EnemyInit(float pathProgress, unsigned char pathIndex, unsigned short health, float movementSpeed);


#endif