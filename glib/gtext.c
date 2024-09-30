#include "gtext.h"
#include "gutil.h"
#include "gframework.h"
/*
#define CHARACTER_SIZE 8
void initFont(){
    fontSheet = initSpriteSheet("resources/font.png", CHARACTER_SIZE);
}

void disposeFont(){
    unloadSpriteSheet(fontSheet);
}



char translateCharToSpriteSheetId(char in){
    if (in >= 'a' && in <= 'z'){
        return in - 'a';
    }else if (in >= '0' && in <= '9'){
        return in - '0' + 26;
    }
    gLog(LOG_ERR, "Font error, character %d not defined", in);
    return 0;
}

void drawText(const char* text, int x, int y, float scale, Color color, int layer){
	int iterator = 0;
    while (text[iterator] != 0) {
        
		// skip drawing spaces
		if (text[iterator] != ' '){
			char character = translateCharToSpriteSheetId(text[iterator]);
        
        	insertDrawRequest(character, x + (iterator * CHARACTER_SIZE * scale), y, 0.0f, FLIP_NONE, scale, color, layer, &fontSheet);
        }
        iterator++;
    }
}

void drawTextF(const char* text, int x, int y, float scale, Color color, int layer, ...){
    va_list args;
	va_start(args, layer);
    char formatedText[500];
    
    vsprintf(formatedText, text, args);

	va_end(args);
    drawText(formatedText, x, y, scale, color, layer);

}

void drawTextVF(const char* text, int x, int y, float scale, Color color, int layer, va_list* args){
	
	char formatedText[500];
	vsprintf(formatedText, text, *args);
	drawText(formatedText, x, y, scale, color, layer);
}

void textF(const char* text, int x, int y, ...){
	va_list args;
	va_start(args, y);

	drawTextVF(text, x, y, 2.0, WHITE, LAYER_STATIC_UI, &args);

	va_end(args);
}*/