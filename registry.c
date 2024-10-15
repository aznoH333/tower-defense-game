#include "registry.h"
#include "enemy.h"
#include "entities.h"
#include "ggamestate.h"
#include <raylib.h>
#include "level.h"
#include "towerManager.h"
#include "cameraManager.h"


//================================================
// Game states
//================================================
void gameLoad(){
    *getCurrentLevel() = generateLevel();
    EntitiesInit();
    CameraInit();
}


void gameUnload(){
    EntitiesDispose();
    LevelUnload(*getCurrentLevel());
    CameraUnload();
}


void gameUpdate(){
    // temporary controls
    if (IsKeyPressed(KEY_M)){
        EntitiesAddEntity(EnemyInit(0.0f, 0, 100, 0.025f));
    }

    if (IsKeyPressed(KEY_L)){
        (*getCurrentLevel())++;
    }

    if (IsKeyPressed(KEY_N)){
        TowerManagerBuildTower(0, &(*getCurrentLevel())->towerSpots[0]);
    }

    // temporary building
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        for (int i = 0; i < MAX_TOWER_SPOTS; i++){
            TowerSpot* t = &(*getCurrentLevel())->towerSpots[i];

            if (t->TOWER_SPOT_STATUS != TOWER_SPOT_EMPTY){
                continue;
            }


            RayCollision result = GetRayCollisionBox(CameraGetMouseRay(), (BoundingBox){(Vector3){t->x, -1.0f, t->y}, (Vector3){1, 2, 1}}); 
            if (result.hit){
                TowerManagerBuildTower(0, t);
                
                break;
            }
        }
    }
    

    // update
    EntitiesUpdate();
    LevelDraw(*getCurrentLevel());
    CameraUpdate();
}


void registerGamestates(){
    registerGamestate(GamestateInit(&gameLoad, &gameUnload, &gameUpdate));
}


//================================================
// Public function
//================================================
void registerContet(){
    registerGamestates();
}
