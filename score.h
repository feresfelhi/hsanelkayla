#ifndef UTILITAIRE_H_INCLUDED
#define UTILITAIRE_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string.h>




typedef struct {

	SDL_Surface* textSurface;
	SDL_Rect positiontext;
	char txt[20];
	SDL_Color couleurtext;
	TTF_Font* police;
    
}Text;

int initscore(Text* T);
int loadFontscore(Text* T, char* path);
void afficher_score(Text T,SDL_Surface *screen);
void freescore(Text T);
#endif
