#ifndef PERSO_H_INCLUDED
#define PERSO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
typedef struct 
{
SDL_Surface *image;
SDL_Rect pos,min,max,x,y,w,h;
int direction;
}perso;
#endif // PERSO_H_INCLUDED
