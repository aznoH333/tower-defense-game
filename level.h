#ifndef LEVEL 
#define LEVEL 

#define LEVEL_SIZE 16

struct Level{
    char tileData[LEVEL_SIZE][LEVEL_SIZE];
}; typedef struct Level Level;


#define DIRECTION_UP 0
#define DIRECTION_DOWN 1
#define DIRECTION_LEFT 2
#define DIRECTION_RIGHT 3

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
#define PATH_DIRECTION_MASK     0b01100000
#define PATH_DIRECTION_OFFSET 5


Level* generateLevel();
void LevelDraw(Level* this);
void LevelUnload(Level* this);

#endif