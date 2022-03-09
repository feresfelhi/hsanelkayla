#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>

typedef struct
{
	SDL_Rect pos;
	SDL_Surface *anim1[], *anime2[], anime3[];
	SDL_Surface *mask;
	int stage, nb_anim;
	
}Background;


void initBack(Background * BG);
void afficherBack(Background BG, SDL_Surface * scre);
void animerBackground( Background * BG);
int collisionPP( Personne P, SDL_Surface * Mask);
void scrolling (background * BG, int direct, int pasAvancement);
void free_BG(Background);
#endif
