#ifndef GAME_ENTITIES
#define GAME_ENTITIES

#include <raylib.h>
#include "gcollections.h"


#define ENTITY_TYPE_ENEMY               0
#define ENTITY_TYPE_TOWER               1
#define ENTITY_TYPE_TOWER_PROJECTILE    2

#define ENTITY_STATE_ALIVE              0
#define ENTITY_STATE_DEATH              1
#define ENTITY_STATE_CLEAN              2


struct Entity{
    Vector3 position;
    float rotation;
    Vector3 boundingBox;
    // functions
    void (*EntityUpdate)(struct Entity* this);
    void (*EntityCollide)(struct Entity* this, struct Entity* other);
    void (*EntityDestroy)(struct Entity* this);                         // should do actions when entity is destroyed by combat/ ect (play animation, award money whatever)
    void (*EntityRemove)(struct Entity* this);                          // should only clean assigned data (dont play animations)
    // extra data
    unsigned int extraDataIndex;
    unsigned char entityType;
    unsigned char existanceState;
};
typedef struct Entity Entity;


// entity management
void EntitiesAddEntity(Entity* entity);
void EntitiesUpdate();
void EntitiesDispose();
void EntitiesInit();
Vector* EntitiesFindEntities(Entity* caller, bool (*validityFunction)(Entity* caller, Entity* candidate), float range);


// entity
Entity* EntityInit(Vector3 position, void (*EntityUpdate)(struct Entity* this), void (*EntityCollide)(struct Entity* this, struct Entity* other), void (*EntityDestroy)(struct Entity* this), void (*EntityRemove)(struct Entity* this), char entityType);


// extra data
int EntitiesAllocateExtraData(void* data);
void* EntitiesGetExtraData(int index);
void EntitiesRemoveExtraData(int index);


#endif