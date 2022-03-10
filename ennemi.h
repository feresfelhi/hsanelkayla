#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


typedef struct
{

SDL_Surface* sprite;

SDL_Rect pos;

int run_speed;

int direction; //-1 if left and 1 if right

int state; // chasing / idle / fighting

int hp;

int damage;

}enemy;
void init_enemy(enemy * e, char filename[], int x, int y, int direction,int run_speed);
void disp_enemy(enemy e, SDL_Surface * window);
void animate_Enemy(enemy * e);
void move_enemy( enemy * e, int max, int min);
//int collisionBB( Player p, Enemy e);//int collisionBB( SDL_Rect posSDL_Rect pos);
//void moveIA( Enemy * e, SDL_Rect posPlayer);
#endif
