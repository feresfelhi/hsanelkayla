#ifndef ENEMI_H
#define ENEMI_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "perso.h"

typedef struct
{

    SDL_Surface* sprite;

    SDL_Rect pos ,max, min;
     SDL_Rect possprite;
  

    int direction; //0 if left and 1 if right

    
}enemie;
void initenemie (enemie *e);
void afficher_enemie (enemie e,SDL_Surface *screen);
void animate_Enemy(enemie * e);
void move_enemy( enemie * e);
int collision (enemie e,perso p);//int collisionBB( SDL_Rect posSDL_Rect pos);
//void moveIA( Enemy * e, SDL_Rect posPlayer);
#endif
