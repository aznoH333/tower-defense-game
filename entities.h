#ifndef GAME_ENTITIES
#define GAME_ENTITIES

#include <raylib.h>


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


void addEntity(Entity* entity);
void updateEntities();
void disposeEntities();
void initEntities();
Entity* EntityInit(Vector3 position, void (*EntityUpdate)(struct Entity* this), void (*EntityCollide)(struct Entity* this, struct Entity* other), void (*EntityDestroy)(struct Entity* this), void (*EntityRemove)(struct Entity* this));


int allocateExtraData(void* data);
void* getExtraData(int index);
void removeExtraData(int index);


#endif