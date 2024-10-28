#include "registry.h"
#include "cards.h"
#include "entities.h"
#include "ggamestate.h"
#include <raylib.h>
#include "level.h"
#include "towerManager.h"
#include "cameraManager.h"
#include "enemyWaves.h"
#include "gutil.h"
#include "deck.h"
#include "deckIteration.h"


//================================================
// Game states
//================================================
EnemyWaves* w;
Deck* deck;
DeckIteration* deckIteration;
int selectedCardInHand = -1;

void gameLoad(){
    *getCurrentLevel() = generateLevel();
    EntitiesInit();
    CameraInit();
    w = EnemyWavesInit();
    deck = DeckInit();
    DeckAddCard(deck, 0); // Temporary add test card
    DeckAddCard(deck, 0);
    DeckAddCard(deck, 0);
    DeckAddCard(deck, 0);

    deckIteration = DeckIterationInit(deck);

    DeckIterationDrawCard(deckIteration); // temporary card draw
    DeckIterationDrawCard(deckIteration);

}


void gameUnload(){
    EntitiesDispose();
    LevelUnload(*getCurrentLevel());
    CameraUnload();
    EnemyWavesDispose(w);
    DeckIterationDispose(deckIteration);
    DeckDispose(deck);
}


void gameUpdate(){

    EnemyWavesUpdate(w);
    // temporary controls
    if (IsKeyPressed(KEY_M)){
        EnemyWavesStartNextWave(w);
    }

    if (IsKeyPressed(KEY_L)){
        (*getCurrentLevel())++;
    }

    if (IsKeyPressed(KEY_N)){
        TowerManagerBuildTower(0, &(*getCurrentLevel())->towerSpots[0]);
    }
    
    // temporary card select
    for (int i = KEY_ONE; i < KEY_ONE + deckIteration->hand->elementCount; i++){
        if (IsKeyPressed(i)){
            selectedCardInHand = i - KEY_ONE;
            gLog(LOG_DBG, "[hand] - Selected card [%d]", selectedCardInHand);
        }
    }

    
    // temporary building
    if (selectedCardInHand >= 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        for (int i = 0; i < MAX_TOWER_SPOTS; i++){
            TowerSpot* t = &(*getCurrentLevel())->towerSpots[i];

            if (t->TOWER_SPOT_STATUS != TOWER_SPOT_EMPTY){
                continue;
            }


            RayCollision result = GetRayCollisionBox(CameraGetMouseRay(), (BoundingBox){(Vector3){t->x, -1.0f + t->terrainHeightOffset, t->y}, (Vector3){1, 2, 1}}); 
            if (result.hit){
                gLog(LOG_DBG, "card hit");
                Card* temporaryCard = DeckIterationGetCardInHand(deckIteration, selectedCardInHand);
                gLog(LOG_DBG, "placing tower [%s]", temporaryCard->name);

                temporaryCard->cardFunction(temporaryCard, (CardTarget){t});
                DeckIterationDiscardCard(deckIteration, selectedCardInHand);
                DeckIterationDrawCard(deckIteration);
                selectedCardInHand = - 1;
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
    gLog(LOG_DBG, "Test card effect active");
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
