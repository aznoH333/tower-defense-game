#include "level.h"
#include <stdlib.h>
#include "g3d.h"

//================================================
// Tile manipulation
//================================================
void setTileTypeFlag(char* tile, char tileType){
    *tile = *tile & TILE_TYPE_MASK;
    *tile += tileType;
}

bool getTileTypeFlag(char* tile){
    return *tile & TILE_TYPE_FLAG;
}

//================================================
// Init and unload
//================================================
Level* generateLevel(){
    Level* this = malloc(sizeof(Level));

    // init empty map
    for (int x = 0; x < LEVEL_SIZE; x++){
        for (int y = 0; y < LEVEL_SIZE; y++){
            this->tileData[x][y] = 0;
        }
    }

    // generate path (temporary)
    for (int x = 0; x < LEVEL_SIZE; x++){
        for (int y = 0; y < LEVEL_SIZE; y++){
            setTileTypeFlag(&this->tileData[x][y], TILE_TYPE_TILE);
        }
    }


    // hardcoded path
    for (int i = 0; i < 5; i++){
        setTileTypeFlag(&this->tileData[5][i], TILE_TYPE_PATH);
    }
    for (int i = 0; i < 4; i++){
        setTileTypeFlag(&this->tileData[5 + i][5], TILE_TYPE_PATH);
    }
    for (int i = 0; i < 11; i++){
        setTileTypeFlag(&this->tileData[9][5+i], TILE_TYPE_PATH);
    }


    return this;
}


void LevelUnload(Level* this){

}


//================================================
// Update
//================================================
void renderTile(char* tile, int x, int y){
    bool isTile = getTileTypeFlag(tile) == TILE_TYPE_TILE;
    
    const char* tileName = (isTile ? "debug_textures_0001" : "debug_textures_0002");
    
    drawPlane(tileName, (Vector3){x, 0 + (0.3f * isTile), y}, (Vector3){0,0,0}, 1.0f);
}

void LevelDraw(Level* this){
    for (int x = 0; x < LEVEL_SIZE; x++){
        for (int y = 0; y < LEVEL_SIZE; y++){
            renderTile(&this->tileData[x][y], x, y);
        }
    }
}