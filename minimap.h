#ifndef MINIMAP_H_
#define MINIMAP_H_
#include <time.h>
#include <stdio.h>  
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "score.h"
#include "fonctionperso.h"
//structure minimap
typedef struct 
{ 
  SDL_Rect posminimap;
  SDL_Surface *minimap;
  SDL_Surface *bonhomme;
  SDL_Rect posbonhomme; 
}minimap;

//minimap
void initminimap (minimap *m);
void afficherminimap (minimap m, SDL_Surface * screen);
void freeminimap(minimap *m);
void majminimap (Personne *p , minimap * m, SDL_Rect camera , int redimensionnement);
// temps
void affichertemps (int temps, SDL_Surface *screen);
SDL_Color GetPixel (SDL_Surface *BG , int x , int y);//traj3ilna couleur ta3 position ili fiha il perso hkk nfar9ou bin perso w il be9i
int collisionPPP (Personne p , SDL_Surface *masque);//mouvement
//sauvegardage 
//void afficherscore (SDL_Surface *screen,Personne p,int *score);
void sauvegarder (int score , char nomjoueur[] , char nomfichier[]);
//option
int entrernom (SDL_Surface * screen, char nom[30], int *x);
void cherchermeuilleurscore (int *score , char nomjoueur[10] , FILE* f) ;
void affichermeilleurscore (SDL_Surface *screen);

#endif 

