#ifndef salma_H_
#define salma_H_
#include <time.h>

//structure pour le personnage principale
typedef struct 
{
  SDL_Rect posperso;
  SDL_Surface *perso;
  int direction ; // ken 1 perso yimchi imin sinon yimchi isar
}personne;

//structure minimap
typedef struct 
{ 
  SDL_Rect posminimap;
  SDL_Surface *minimap;
}minimap;

//minimap
void initminimap (minimap *m);
void afficherminimap (minimap m, SDL_Surface * screen);
void freeminimap(minimap *m);
void majminimap (personne *p , minimap * m, SDL_Rect camera , int redimensionnement);
// temps
void affichertemps (int temps, SDL_Surface *screen);
SDL_Color GetPixel (SDL_Surface *BG , int x , int y);//traj3ilna couleur ta3 position ili fiha il perso hkk nfar9ou bin perso w il be9i
int collisionPP (personne p , SDL_Surface *masque);//mouvement
//sauvegardage du scors
void sauvegarder (int score , char nomjoueur[] , char nomfichier[]);

#endif 

