#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>

typedef struct
{
	SDL_Surface *anim[1];
	//SDL_Rect pos_scrn;
	//SDL_Rect pos_img;
	SDL_Surface *mask[1];
	SDL_Rect camera;
	int nb_anim, gravity;
}Background;


void initBack(Background * BG);
void afficherBack(Background BG, SDL_Surface * scre);
void animerBackground( Background * BG);
int collisionPP( SDL_Rect P, SDL_Surface * Mask);
void scrolling (Background * BG, int direct, int pasAvancement);
void free_BG(Background);
#endif
