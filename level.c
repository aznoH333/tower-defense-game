#include "level.h"
#include <stdlib.h>
#include "g3d.h"
#include "gutil.h"

//================================================
// Tile manipulation
//================================================
void setTileTypeFlag(char* tile, char tileType){
    *tile = *tile & TILE_TYPE_MASK;
    *tile += tileType;
}


char getTileTypeFlag(char* tile){
    return *tile & TILE_TYPE_FLAG;
}


char getTileSafe(char tileData[LEVEL_SIZE][LEVEL_SIZE], int x, int y){
    if (x >= 0 && x < LEVEL_SIZE && y >= 0 && y <= LEVEL_SIZE){
        return tileData[x][y];
    }
    return 0;
}


bool isTileAPathTile(char tileData[LEVEL_SIZE][LEVEL_SIZE], int x, int y){
    char tile = getTileSafe(tileData, x, y);
    return getTileTypeFlag(&tile) == TILE_TYPE_PATH;
}


void setPathBorders(char* tile, bool up, bool down, bool left, bool right){
    *tile = *tile | (up * PATH_FLAG_TILE_UP) | (down * PATH_FLAG_TILE_DOWN) | (left * PATH_FLAG_TILE_LEFT) | (right * PATH_FLAG_TILE_RIGHT);
}


bool pathHasBorder(char* tile, char direction){
    return (*tile & direction) > 0;
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

    // set path borders
    for (int x = 0; x < LEVEL_SIZE; x++){
        for (int y = 0; y < LEVEL_SIZE; y++){
            setPathBorders(&this->tileData[x][y], 
                isTileAPathTile(this->tileData, x, y - 1), 
                isTileAPathTile(this->tileData, x, y + 1), 
                isTileAPathTile(this->tileData, x - 1, y), 
                isTileAPathTile(this->tileData, x + 1, y));
        }
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
    
    drawPlane(tileName, (Vector3){x, 0 - (PATH_OFFSET * !isTile), y}, (Vector3){0,0,0}, 1.0f);

    if (isTile){
        return;
    }
    // render path borders
    // up
    if (pathHasBorder(tile, PATH_FLAG_TILE_UP)){
        drawPlane("debug_textures_0004", (Vector3){x - 0.5f, -0.5f, y}, (Vector3){ROT_90,ROT_90,0}, 1.0f);
    }

    // down
    if (pathHasBorder(tile, PATH_FLAG_TILE_DOWN)){
        drawPlane("debug_textures_0004", (Vector3){x + 0.5f, -0.5f, y}, (Vector3){-ROT_90,ROT_270,ROT_180}, 1.0f);
    }
    
    // left
    if (pathHasBorder(tile, PATH_FLAG_TILE_LEFT)){
        drawPlane("debug_textures_0004", (Vector3){x, 0.0f, y - 0.5f}, (Vector3){0,0,ROT_90}, 1.0f);
    }

    // right
    if (pathHasBorder(tile, PATH_FLAG_TILE_RIGHT)){
        drawPlane("debug_textures_0004", (Vector3){x, 0.0f, y}, (Vector3){ROT_90,ROT_270,-ROT_90}, 1.0f);
    }

}

void LevelDraw(Level* this){
    for (int x = 0; x < LEVEL_SIZE; x++){
        for (int y = 0; y < LEVEL_SIZE; y++){
            renderTile(&this->tileData[x][y], x, y);
        }
    }
}