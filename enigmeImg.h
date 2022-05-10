#ifndef ENIGMEIMG_H_INCLUDED
#define ENIGMEIMG_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/**
* @struct enigme
* @brief structure enigme
*/

typedef struct
{	
	SDL_Surface *image_enigme; /*!< Surface*/ 
	SDL_Rect position_enigme; /*!< Rectangle*/ 
	SDL_Surface *anim[6]; /*!< Surface*/
	SDL_Rect position_anim; /*!< Rectangle*/
	int resultat;
	int alea;
	
}enigme;

/**
* @struct picture
* @brief structure picture
*/

typedef struct
{	
	SDL_Rect pos_scrn; /*!< Rectangle*/
	SDL_Rect pos_img; /*!< Rectangle*/
	SDL_Surface *img; /*!< Surface*/ 
}Pic;

void init_Img(Pic *, char *, int, int);
void afficher_Img(Pic, SDL_Surface *);
int init_Enigme(enigme* en ,char *nomfichier);
void affiche_Enigme(enigme en, SDL_Surface *screen);
void resoudre_Enigme(enigme *en);
void Enigme_animer(enigme *en);
#endif
