#include "enemyWaves.h" 
#include "gcollections.h"
#include <stdlib.h>
#include "entities.h"
#include "enemy.h"
#include "gutil.h"


//================================================
// Enemy spawn groups
//================================================
EnemySpawnGroup* EnemySpawnGroupInit(unsigned char enemyId, unsigned char enemiesInGroup, unsigned char groupSpawnDelay, unsigned char enemySpawnDelay){
    EnemySpawnGroup* this = malloc(sizeof(EnemySpawnGroup));
    
    this->enemyId = enemyId;
    this->groupSpawnDelay = groupSpawnDelay;
    this->enemiesInGroup = enemiesInGroup;
    this->internalTimer = groupSpawnDelay;
    this->enemySpawnDelay = enemySpawnDelay;
    this->status = ENEMY_GROUP_PASSIVE;
    return this;
}


void EnemySpawnGroupUpdate(EnemySpawnGroup* this, int spawnPath){
    this->internalTimer -= this->internalTimer > 0;

    if (this->internalTimer == 0){
        if (this->status == ENEMY_GROUP_PASSIVE){
            // PASSIVE status
            // switch to active state
            this->internalTimer = this->enemiesInGroup * this->enemySpawnDelay;
            this->status = ENEMY_GROUP_ACTIVE;
        }else{
            // ACTIVE status
            // switch to passive
            this->internalTimer = this->groupSpawnDelay;
            this->status = ENEMY_GROUP_PASSIVE;
        }
    }

    if (this->status == ENEMY_GROUP_ACTIVE && this->internalTimer % this->enemySpawnDelay == 0){
        // temporary
        EntitiesAddEntity(EnemyInit(0.0f, 0, 100, 0.025f));
    }
}


void EnemySpawnGroupDispose(EnemySpawnGroup* this){
    free(this);
}


//================================================
// Enemy spawn groups
//================================================
EnemyWaves* EnemyWavesInit(){
    EnemyWaves* waves = malloc(sizeof(EnemyWaves*));

    // temp
    waves->startingDifficulity = 1;
    waves->finalDifficulity = 6;
    waves->maxWaves = 5;
    waves->currentWave = 0;
    waves->currentStatus = WAVE_STATUS_PREPERATION;
    waves->enemyGroups = VectorInit();

    return waves;
}


void EnemyWavesWaveUpdate(EnemyWaves* this){
    for (int i = 0; i < this->enemyGroups->elementCount; i++){
        EnemySpawnGroup* group = VectorGet(this->enemyGroups, i);
        EnemySpawnGroupUpdate(group, 0); // TODO support multiple paths
    }

    if (this->currentWaveTimer-- == 0){

        if (this->currentWave == this->maxWaves){
            this->currentStatus = WAVE_STATUS_FINISHED;
        }else {
            this->currentStatus = WAVE_STATUS_BREAK;
            this->nextWaveTimer = 600;// TODO make this not a constant??
        }
    }
}


void EnemyWavesClearEnemyGroups(EnemyWaves* this){
    for(int i = 0; i < this->enemyGroups->elementCount; i++){
        EnemySpawnGroup* group = VectorGet(this->enemyGroups, i);

        EnemySpawnGroupDispose(group);
    
    }

    VectorClearM(this->enemyGroups, true);
}


void EnemyWavesBreakUpdate(EnemyWaves* this){
    this->nextWaveTimer -= this->nextWaveTimer > 0;
    if (this->nextWaveTimer == 0){
        // set status
        EnemyWavesStartNextWave(this);
    }
}


void EnemyWavesUpdate(EnemyWaves* this){
    switch (this->currentStatus) {
        case WAVE_STATUS_BREAK:
            EnemyWavesBreakUpdate(this);
            break;
        case WAVE_STATUS_FINISHED:
        case WAVE_STATUS_PREPERATION:
            break;
        case WAVE_STATUS_ACTIVE:
            EnemyWavesWaveUpdate(this);
            break;
    }
}


void EnemyWavesDispose(EnemyWaves* this){
    EnemyWavesClearEnemyGroups(this);
    VectorFreeM(this->enemyGroups, true);
    free(this);
}


void EnemyWavesStartNextWave(EnemyWaves* this){
    if (this->currentStatus != WAVE_STATUS_PREPERATION && this->currentStatus != WAVE_STATUS_BREAK){
        return;
    }
    this->currentStatus = WAVE_STATUS_ACTIVE;

    // generate enemy groups
    // todo
    EnemyWavesClearEnemyGroups(this);
    VectorPush(this->enemyGroups, EnemySpawnGroupInit(0, 2, 120, 60));
   
    this->currentWave++;
    this->currentWaveTimer = 500;
}
