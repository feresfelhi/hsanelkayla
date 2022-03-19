#ifndef TEXT_H_
#define TEXT_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
	SDL_Rect pos;
	SDL_Color color;
	SDL_Surface *surftxt;
	TTF_Font *font;
	char* txt;
}text;
void initText(text *T, int x, int y, int s, char* font);
void initTitle(text *T, int x, int y, int size, char* font);
void freetext(text T);
void affichertxt(text T, SDL_Surface * screen, char *ch);
#endif
