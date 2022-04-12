#ifndef perso_H_INCLUDED  
#define perso_H_INCLUDED
#include <stdio.h>  
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "vieetscore.h"


typedef struct { 

	SDL_Surface *image;
	SDL_Rect position;
	SDL_Rect frame;
	SDL_Surface *vie;
        SDL_Rect posvie;

	
	int nbframe; 
	//Text vie;
	int direction; 
	Text score; 
        int test;	 
        int courant;    
	double acceleration;  
	double decelere;	 
	double vitesse;   
	double vx;
	double vgrav ;
	double vsaut ;
	double vy ; 
	
}Personne;


void initPerso(Personne *p);  
void initPerso2(Personne *p);
void afficherPerso (Personne p,SDL_Surface *screen);
void deplacerPerso(Personne *p ,SDL_Surface *screen,int dt);
void animerPerso(Personne *p);
void saut(Personne *p);
void vitesseUP(Personne *p);
void vitesseDOWN(Personne *p);
#endif

