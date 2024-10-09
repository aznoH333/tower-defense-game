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
    if (x >= 0 && x < LEVEL_SIZE && y >= 0 && y < LEVEL_SIZE){
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


void setTileData(char* tile, bool buildable, char height){
    // set build flag
    *tile = *tile & ~TILE_IS_BULDABLE_FLAG | (buildable * TILE_IS_BULDABLE_FLAG);
    gLog(LOG_INF, "step 1 %b", *tile);

    // set height
    char validHeight = (height & (TILE_HEIGHT_MASK >> TILE_HEIGHT_OFFSET)) << TILE_HEIGHT_OFFSET;
    *tile = *tile & ~TILE_HEIGHT_MASK | validHeight;

    gLog(LOG_INF, "step 2 %b", *tile);
}


bool isTileBuildable(char* tile){
    return (*tile & TILE_IS_BULDABLE_FLAG) > 0;
}

char getTileHeight(char* tile){
    return (*tile & TILE_HEIGHT_MASK) >> TILE_HEIGHT_OFFSET;
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

    // hardcoded tiles
    setTileData(&this->tileData[6][6], true, 0);
    setTileData(&this->tileData[8][8], true, 0);
    setTileData(&this->tileData[4][2], false, 1);
    setTileData(&this->tileData[4][3], false, 2);
    setTileData(&this->tileData[4][4], false, 1);







    // set path borders
    for (int x = 0; x < LEVEL_SIZE; x++){
        for (int y = 0; y < LEVEL_SIZE; y++){
            if (isTileAPathTile(this->tileData, x, y)){
                setPathBorders(&this->tileData[x][y], 
                isTileAPathTile(this->tileData, x, y - 1), 
                isTileAPathTile(this->tileData, x, y + 1), 
                isTileAPathTile(this->tileData, x - 1, y), 
                isTileAPathTile(this->tileData, x + 1, y));
            }
        }
    }


    return this;
}


void LevelUnload(Level* this){

}


//================================================
// Update
//================================================
void renderPath(char* tile, int x, int y){
    // render main path
    drawPlane("debug_textures_0002", (Vector3){x, -PATH_OFFSET, y}, (Vector3){0,0,0}, 1.0f);
    
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
        drawPlane("debug_textures_0004", (Vector3){x, -0.5f, y - 0.5f}, (Vector3){ROT_90,0.0f,0.0f}, 1.0f);
    }
    
    // right
    if (pathHasBorder(tile, PATH_FLAG_TILE_RIGHT)){
        drawPlane("debug_textures_0004", (Vector3){x, -0.5f, y + 0.5f}, (Vector3){ROT_270,0.0f,ROT_180}, 1.0f);
    }
}


void renderRegularTile(char* tile, int x, int y){
    char height = getTileHeight(tile);
    bool buildable = isTileBuildable(tile);

    const char* textureName;

    // decide texture
    if (buildable){
        textureName = "debug_textures_0003";
    }else if (height > 0){
        textureName = "debug_textures_0005";
    }else {
        textureName = "debug_textures_0001";
    }

    // draw main tile
    drawPlane(textureName, (Vector3){x, height, y}, (Vector3){0,0,0}, 1.0f);

    // draw sides for high tiles
    for (int i = height; i > 0; i--){
        drawPlane("debug_textures_0005", (Vector3){x + 0.5f, i - 0.5f, y}, (Vector3){ROT_90,ROT_90,0}, 1.0f);
        drawPlane("debug_textures_0005", (Vector3){x - 0.5f, i - 0.5f, y}, (Vector3){-ROT_90,ROT_270,ROT_180}, 1.0f);
        drawPlane("debug_textures_0005", (Vector3){x, i - 0.5f, y + 0.5f}, (Vector3){ROT_90,0.0f,0.0f}, 1.0f);
        drawPlane("debug_textures_0005", (Vector3){x, i - 0.5f, y - 0.5f}, (Vector3){ROT_270,0.0f,ROT_180}, 1.0f);
    }

}


void renderTile(char* tile, int x, int y){
    bool isTile = getTileTypeFlag(tile) == TILE_TYPE_TILE;

    const char* tileName = (isTile ? "debug_textures_0001" : "debug_textures_0002");
    

    if (!isTile){
        renderPath(tile, x, y);
    }else {
        renderRegularTile(tile, x, y);
    }
}


void LevelDraw(Level* this){
    for (int x = 0; x < LEVEL_SIZE; x++){
        for (int y = 0; y < LEVEL_SIZE; y++){
            renderTile(&this->tileData[x][y], x, y);
        }
    }
}