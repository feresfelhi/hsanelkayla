#ifndef enigme_H_INCLUDED
#define enigme_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
//#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
typedef struct
{
 SDL_Surface * srf,*texte , *fond , *rp ;
 SDL_Rect pos;
}enigme;

void init_enigme(enigme * e);
int enigmee(enigme *screen,int* e1,int* e2,int* e3,int* e4,int* e5,int *close,int rep);

  #endif // DS_H_INCLUDEDw
