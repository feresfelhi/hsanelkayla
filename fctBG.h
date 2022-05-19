#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>

typedef struct
{
	SDL_Surface *anim[2];
	SDL_Rect pos_img;
	SDL_Rect pos_img2;
	SDL_Surface *mask[1];
	SDL_Rect camera;
	SDL_Rect camera2;
	int nb_anim, gravity, multi_J;
}Background;


void initBack(Background * BG);
void afficherBack(Background BG, SDL_Surface * scre);
void animerBackground( Background * BG);
int collisionGND( SDL_Rect P, SDL_Surface * Mask);
int collisionPP( SDL_Rect P, SDL_Surface * Mask);
void scrolling (SDL_Rect *pos, int direct, int pasAvancement);
SDL_Color GetColPixel(SDL_Surface* Mask, int x, int y);
void free_BG(Background);
#endif
