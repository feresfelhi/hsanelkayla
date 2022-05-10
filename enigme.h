#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED
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
}pic;

void initImg(pic *, char *, int, int);
void afficher_img(pic, SDL_Surface *);
int initEnigme(enigme* e ,char *nomfichier);
void afficheEnigme(enigme e, SDL_Surface *screen);
void resoudreEnigme(enigme *e);
void animerEnigme(enigme *e);
#endif
