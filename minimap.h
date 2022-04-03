#ifndef salma_H_
#define salma_H_
#include <time.h>

typedef struct
{
	SDL_Rect position_perso;  //lel perso l kbir
	SDL_Surface *sprite;
} Personne;

typedef struct
{
	SDL_Rect position_mini; //lel point rouge
	SDL_Surface *sprite;     
} minimap;

typedef struct temps
{
	SDL_Surface *texte;  
	SDL_Rect position;  //limin lfouk

	TTF_Font *police;

	char entree[100];
	int secondesEcoulees;     
	SDL_Color couleurBlanche;   
	time_t t1, t2;
	int min, sec;
} temps;


//minimap
void initmap(minimap *m);   
void afficherminimap(minimap m, SDL_Surface *screen);
void free_minimap(minimap *m);
void majminimap (Personne *p, minimap *m ,SDL_Rect camera ,int redimensionnement);
//temps
void initialiser_temps(temps *t);
void afficher_temps(temps *t, SDL_Surface *ecran);
void free_temps(temps *t, SDL_Surface *ecran);
//map
SDL_Color GetPixel(SDL_Surface *Background, int x, int y);
int collisionPP(Personne p, SDL_Surface *Masque);

#endif







/*#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>

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

//found on github
typedef struct image
{
	SDL_Surface *img;//wyn chnachargo image
	SDL_Rect pos;// Position mta3 background
}image;

image init_image(char nameofpicture[100],int x,int y);
void affichage(SDL_Surface *ecran,image img);
void librer_image(image img);
#endif */
/*
#ifndef HEADER_H_
#define HEADER_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>

typedef struct
 {
  SDL_Surface *perso;//image perso
  SDL_Rect posperso;//position perso
  int direction;//direction perso 1 imin 2 essar
 }Personne;

typedef struct
 {
   SDL_Surface *minimap;//image minimap
   SDL_Surface *point;//image point minimap
   SDL_Surface *cadreminimap;//image cadreminimap
   SDL_Rect posminimap;//position minimap
   SDL_Rect pospoint;//position point minimap
   SDL_Rect poscadreminimap;//position cadre minimap
 }minimap;
 
void initminimap( minimap * m); 
//MAJMinimap (perso p , minimap * m, SDL_Rect camera , int redimensionnement);
void afficherminimap (minimap m, SDL_Surface * screen);
void affichertemps (int temps, SDL_Surface * screen);
int collisionPP( Personne p, SDL_Surface * Masque);
void sauvegarder (int score , char nomjoueur[] , char nomfichier[]);
void meilleur (char nomfichier[] , int *score , char nomjoueur[]);*/

//#endif
