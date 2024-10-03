/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include "gframework.h"
#include "gfiles.h"




struct Debug{
    int x;
    int y;
}; typedef struct Debug Debug;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    
    initFramework();

    //gfullscreen();
    File* file = FileInit("./beans.test");
    Debug* dbg;
    
    if (file->loadStatus == FILE_STATUS_NOT_FOUND){
        dbg = malloc(sizeof(Debug));
        dbg->x = 10;
        dbg->y = 10;
    }else {
        dbg = FileLoadObject(file, sizeof(Debug));
    }

    // Main game loop
    while (isGameRunning())
    {
  		fUpdate();

        draw("spritesheet_0162", dbg->x, dbg->y, LAYER_OBJECTS);
        if (IsKeyDown(KEY_LEFT)) dbg->x--;
        if (IsKeyDown(KEY_RIGHT)) dbg->x++;
        if (IsKeyDown(KEY_UP)) dbg->y--;
        if (IsKeyDown(KEY_DOWN)) dbg->y++;



	}

    FileStoreObject(file, dbg, sizeof(Debug));
    FileSave(file);
    free(dbg);

    
    disposeFramework();

    return 0;
}
