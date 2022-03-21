#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
/*
struct minimap
{
        SDL_Rect pos_scrn;
	SDL_Surface * mini_map;
	SDL_Rect pos_minimap;
	SDL_Surface* mini_hero;
	SDL_Rect pos_minihero;
	SDL_Surface* mini_bg;
	SDL_Rect pos_minibg;
	SDL_Surface* mini_obs;
	SDL_Rect pos_minobs;
	SDL_Surface* mini_ennemi;
	SDL_Rect pos_miniennemi;
};
typedef struct minimap minimap; 

void initminimap(minimap* m);
void MAJMinimap (SDL_Rect* pos_perso,minimap *m , SDL_Rect camera,int redimensionnement);
void afficherminimap( minimap m,SDL_Surface *screen);
void sauvegarder (int score , char nomjoueur[] , char nomfichier[]);
void meilleur(char nomfichier[] , int * score , char nomjoueur[]);
void free_minimap(minimap* mp);
*/
typedef struct image
{
	SDL_Surface *img;//wyn chnachargo image
	SDL_Rect pos;// Position mta3 background
}image;

image init_image(char nameofpicture[100],int x,int y);
void affichage(SDL_Surface *ecran,image img);
void librer_image(image img);
#endif 
