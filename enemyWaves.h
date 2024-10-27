#ifndef ENEMY_WAVES
#define ENEMY_WAVES

#include "gcollections.h"
#include "path.h"

#define ENEMY_GROUP_ACTIVE 0
#define ENEMY_GROUP_PASSIVE 1

// groups
struct EnemySpawnGroup{
    unsigned char enemyId;
    unsigned char enemiesInGroup;
    unsigned char groupSpawnDelay;
    unsigned char enemySpawnDelay;
    unsigned char status;
    unsigned short internalTimer;
};
typedef struct EnemySpawnGroup EnemySpawnGroup;


EnemySpawnGroup* EnemySpawnGroupInit(unsigned char enemyId, unsigned char enemiesInGroup, unsigned char groupSpawnDelay, unsigned char enemySpawnDelay);
void EnemySpawnGroupUpdate(EnemySpawnGroup* this, int spawnPath);
void EnemySpawnGroupDispose(EnemySpawnGroup* this);

#define WAVE_STATUS_PREPERATION 0
#define WAVE_STATUS_ACTIVE 1
#define WAVE_STATUS_BREAK 2
#define WAVE_STATUS_FINISHED 3

// waves
struct EnemyWaves{
    // wave info
    unsigned char currentWave;
    unsigned char maxWaves;
    unsigned short currentWaveTimer;
    unsigned short nextWaveTimer;
    unsigned char currentStatus;
    Vector* enemyGroups;
    // difficulity info
    unsigned char startingDifficulity;
    unsigned char finalDifficulity;
};
typedef struct EnemyWaves EnemyWaves;

EnemyWaves* EnemyWavesInit();
void EnemyWavesUpdate(EnemyWaves* this);
void EnemyWavesStartNextWave(EnemyWaves* this);
void EnemyWavesDispose(EnemyWaves* this);

#endif