#include "gfiles.h"

File* FileInit(const char* filePath){
    
    File* out = malloc(sizeof(File));
    out->filePath = filePath;
    FILE* file = fopen(filePath, "rb");

    
    
    if (file == NULL){
        // create empty file
        out->contentsLength = 0;
        out->loadStatus = FILE_STATUS_NOT_FOUND;
        out->contents = NULL;
        gLog(LOG_WAR, "%s file not found. Creating new empty file", filePath);
    
    }else {
        
        // read file contents
        char temp[MAX_FILE_SIZE];
        
        int index = 0;
        for(;;){
            int c = fgetc(file);



            if (c == EOF){
                gLog(LOG_DBG, "Found feof ending read [%x] [%c] [%d]", c, c, c);
                
                break;
            }
            
            temp[index] = c;
            index++;
            
            
            if (index >= MAX_FILE_SIZE){
                gLog(LOG_ERR, "File read error. Max size exceeded %d", MAX_FILE_SIZE);
            }
        }
        gLog(LOG_DBG, "read file size [%d]", index);

        // copy file contents
        out->contents = malloc(index * sizeof(char));
        for (int i = 0; i < index; i++){
            out->contents[i] = temp[i];
        }
        out->contentsLength = index;
        out->loadStatus = FILE_STATUS_OK;

        fclose(file);
    }

    return out;
    //return 0;
}


void FileSetContents(File* this, char* newContents, int contentSize){
    free(this->contents);
    this->contents = newContents;
    this->contentsLength = contentSize;
}


void FileSave(File* this){
    FILE* f = fopen(this->filePath, "wb");
    
    if (f == NULL){
        gLog(LOG_ERR, "File write error %s", this->filePath);
    }
    
    for (int i = 0; i < this->contentsLength; i++){
        fprintf(f, "%c", this->contents[i]);
    }

    fclose(f);
}

void FileUnload(File* this){
    free(this->contents);
    free(this);
}

void FileStoreObject(File* this, const void* object, int size){
    char* contents = malloc(size);
    writeObjectToCharArray(object, size, contents, 0);
    FileSetContents(this, contents, size);
}
void* FileLoadObject(File* this, int size){
    char* output = malloc(size);
    if (this->contentsLength != size){
        gLog(LOG_ERR, "File object loading error, size missmatch [%d] [%d]", this->contentsLength, size);
    }
    for (int i = 0; i < size; i++){
        output[i] = this->contents[i];
    }

    return output;
}