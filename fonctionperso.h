#ifndef PERSO_H_
#define PERSO_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
int vie;
SDL_Surface *imagevie;
SDL_Rect Position_vie;
}Vie
typedef struct
{
SDL_Surface *text_score;
SDL_Rect positionscore;
TTF_Font *police;
int score
}Score;

typedef struct
{
SDL_Surface *sprite_sheet;
SDL_Rect positionperso,position_spriteshite;
Vie vie_perso;
Score score_perso;
int mouvement;//sourie ou clavier
int jump;
int attack;
int direction ;//droite ou gauche
int max_frame;
int frame;//le framme actuelle de perso
int vitesse;
}perso;

void init_perso(perso* p);
afficher_perso(perso* p; SDL_Surface *screen);
deplacer_perso(perso* p);
saut_perso(perso* p);
void animation(perso* p);
#endif



