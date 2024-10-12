#ifndef ENEMY 
#define ENEMY 

#include "raylib.h"
#include "entities.h"

struct Enemy{
    unsigned char pathIndex;
    unsigned short health;
    float movementSpeed;
    float pathProgress;
}; typedef struct Enemy Enemy;


void EnemyUpdate(Entity* this);
void EnemyCollide(Entity* this, Entity* other);
void EnemyDestroy(Entity* this);
void EnemyClean(Entity* this);
Entity* EnemyInit(Vector3 position, unsigned char pathIndex, unsigned short health, float movementSpeed);


#endif