#ifndef G_FILES
#define G_FILES 

#include <stdio.h>
#include <stdlib.h>
#include "gutil.h"
#include <limits.h>


#define MAX_FILE_SIZE 1000000


#define FILE_STATUS_OK 0
#define FILE_STATUS_NOT_FOUND 1

struct File{
    char* contents;
    int contentsLength;
    const char* filePath;
    char loadStatus;
};
typedef struct File File;

File* FileInit(const char* filePath);
void FileSetContents(File* file, char* newContents, int contentSize);
void FileSave(File* file);
void FileUnload(File* file);
void FileStoreObject(File* file, const void* object, int size);
void* FileLoadObject(File* file, int size);



#endif