#ifndef LEVEL 
#define LEVEL 

#include "path.h"

#define LEVEL_SIZE 16
#define MAX_PATHS 4
#define MAX_TOWER_SPOTS 10


#define TOWER_SPOT_EMPTY 0
#define TOWER_SPOT_FULL 1
#define TOWER_SPOT_DOESNT_EXIST 2

struct TowerSpot{
    unsigned char x;
    unsigned char y;
    unsigned char TOWER_SPOT_STATUS;
    unsigned char terrainHeightOffset;
}; typedef struct TowerSpot TowerSpot;


struct Level{
    char tileData[LEVEL_SIZE][LEVEL_SIZE];
    Path paths[MAX_PATHS];
    TowerSpot towerSpots[MAX_TOWER_SPOTS];
}; typedef struct Level Level;



// level tile flags
#define TILE_TYPE_FLAG          0b00000001
#define TILE_TYPE_TILE          0b00000001
#define TILE_TYPE_PATH          0b00000000
#define TILE_TYPE_MASK          0b11111110
// path flags
#define PATH_FLAG_TILE_UP       0b00000010
#define PATH_FLAG_TILE_DOWN     0b00000100
#define PATH_FLAG_TILE_LEFT     0b00001000
#define PATH_FLAG_TILE_RIGHT    0b00010000
#define PATH_BORDER_MASK        0b11100001
#define PATH_DIRECTION_MASK     0b01100000
#define PATH_DIRECTION_OFFSET 5
// tile flags
#define TILE_IS_BULDABLE_FLAG   0b00000010
// tile objects
#define TILE_OBJECT_MASK        0b00011100
#define TILE_OBJECT_OFFSET 2
#define TILE_HEIGHT_MASK        0b11100000
#define TILE_HEIGHT_OFFSET 5


#define PATH_OFFSET 0.3f

Level* generateLevel();
void LevelDraw(Level* this);
void LevelUnload(Level* this);
Level** getCurrentLevel();


#endif