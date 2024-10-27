#include "registry.h"
#include "cards.h"
#include "enemy.h"
#include "entities.h"
#include "ggamestate.h"
#include <raylib.h>
#include "level.h"
#include "towerManager.h"
#include "cameraManager.h"
#include "gutil.h"


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
    Card* temporaryCard = CardsGetCardById(0);
    // temporary building
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        for (int i = 0; i < MAX_TOWER_SPOTS; i++){
            TowerSpot* t = &(*getCurrentLevel())->towerSpots[i];

            if (t->TOWER_SPOT_STATUS != TOWER_SPOT_EMPTY){
                continue;
            }


            RayCollision result = GetRayCollisionBox(CameraGetMouseRay(), (BoundingBox){(Vector3){t->x, -1.0f, t->y}, (Vector3){1, 2, 1}}); 
            if (result.hit){
                //TowerManagerBuildTower(0, t);

                temporaryCard->cardFunction(temporaryCard, (CardTarget){t});
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
// Cards
//================================================
void testCardFunction(Card* this, CardTarget target){
    TowerManagerBuildTower(0, target.towerSpot);
}


void registerCards(){
    CardsRegisterCard("Testovaci karticka", 100, CARD_RARITY_COMMON, CARD_TARGET_BUILDSPOT, "Udelej se", &testCardFunction);   
}


//================================================
// Public function
//================================================
void registerContet(){
    registerGamestates();
    registerCards();
}
