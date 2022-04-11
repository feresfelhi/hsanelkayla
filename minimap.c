#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"

void initminimap (minimap *m)
{
  m->posminimap.x=0;
  m->posminimap.y=0;
  m->minimap = IMG_Load("niveau1.png");
}

void afficherminimap (minimap m, SDL_Surface *screen)
{
  SDL_BlitSurface(m.minimap , NULL , screen , &m.posminimap);
}
void freeminimap(minimap *m)
{
    SDL_FreeSurface(m->minimap);
}

void affichertemps (int temps , SDL_Surface *screen)
{
  char s[19];
  SDL_Surface *txt;
  TTF_Font *police = NULL;
  police = TTF_OpenFont("Urusans.TTF",40);
  SDL_Color couleur = {0,0,0}; //couleur noir
  SDL_Rect post;// fou9 3al isar 
  post.x=0; 
  post.y=0;
  sprintf (s,"Temps : %d" , temps );
  txt = TTF_RenderText_Blended (police, s , couleur);
  SDL_BlitSurface(txt,NULL,screen,&post);
}

void afficherscore (SDL_Surface *screen,personne pM,int *score)
{
  char s[19];
  SDL_Surface *sc;
  TTF_Font *police = NULL;
  police = TTF_OpenFont ("Urusans.TTF",40);
  SDL_Color couleur = {0,0,0}; //couleur noir
  SDL_Rect possc;// fil wosit 
  possc.x=0; 
  possc.y=50;
  SDL_Flip(screen);//permute les tompons d'ecran
  if (pM.posperso.x == 400 && pM.posperso.y == 450) 
   {
     (*score)++; 
     sprintf (s,"Score : %d" , *score );
     sc = TTF_RenderText_Blended (police, s , couleur);
     SDL_BlitSurface(sc,NULL,screen,&possc);
   }
   else
    {
      printf ("si\n");
      sprintf (s,"Score : %d",*score);
      sc = TTF_RenderText_Blended(police , s, couleur);
      SDL_BlitSurface(sc,NULL,screen,&possc);
    }
  TTF_CloseFont(police);
}

SDL_Color GetPixel(SDL_Surface *BG, int x, int y)
{
  SDL_Color color;
  Uint32 col = 0;
  char *pixelposition = (char *)BG->pixels;
  pixelposition += (BG->pitch * y);
  pixelposition += (BG->format->BytesPerPixel * x);
  memcpy(&col, pixelposition, BG->format->BytesPerPixel);
  SDL_GetRGB(col, BG->format, &color.r, &color.g, &color.b);
  return (color);
}

int collisionPP (personne p , SDL_Surface *masque)
{
  int collision =0;
  int x,y,i;
  SDL_Color test , couleurnoir = {0,0,0};
  SDL_Rect pos[8];
  //w:3ardh
  pos[0].x = p.posperso.x;
  pos[0].y = p.posperso.y;
  pos[1].x = p.posperso.x + p.posperso.w / 2;
  pos[1].y = p.posperso.y;
  pos[2].x = p.posperso.x + p.posperso.w;
  pos[2].y = p.posperso.y;
  pos[3].x = p.posperso.x;
  pos[3].y = p.posperso.y + p.posperso.h / 2;
  pos[4].x = p.posperso.x;
  pos[4].y = p.posperso.y + p.posperso.h;
  pos[5].x = p.posperso.x + p.posperso.w / 2;
  pos[5].y = p.posperso.y + p.posperso.h;
  pos[6].x = p.posperso.x + p.posperso.w;
  pos[6].y = p.posperso.y + p.posperso.h;
  pos[7].x = p.posperso.x + p.posperso.w;
  pos[7].y = p.posperso.y + p.posperso.h / 2;
  for (i=0;i<8 && collision==0;i++)
  {
    x = pos[i].x;
    y = pos[i].y;
    test = GetPixel(masque,x,y);
    if (test.r ==0 && test.g == 0 && test.b == 0)
       collision = 1;
  }
  return collision;
}

void majminimap (personne *p, minimap *m ,SDL_Rect camera , int redimensionnement)
{
  if (camera.x==0) //ymin
    p->posperso.x += redimensionnement;
  if (camera.x ==1) //ysar
    p->posperso.x -= redimensionnement;
  if (camera.x == 2) //fou9
    p->posperso.y += redimensionnement;
  if (camera.x==3) //louta
    p->posperso.y -= redimensionnement;
}

/*void entrernom (SDL_Surface * screen)
{
  int j;
  FILE * nom = NULL;
  nom = fopen ("joueurs.txt","r+");//ouverture du fichier nom
  //tester si l'ouverture a reussi
  //l'ouverture a reussi
  if (nom != NULL)
  {
    fseek(nom,0,SEEK_END);
    fprintf(nom,"%s \n",joueur);
  }
  //echec de l'ouverture 
  else
  {
    printf ("ERREUR!! \n IMPOSSIBKE D'OUVRIR LE FICHIER\n");
  }
  fclose (nom);
  TTF_Font * sans = TTF_OpenFont("Urusans.TTF",40);
  SDL_Color black = {0,0,0};
  SDL_Surface * message = TTF_RenderText_Solid(sans,"put your text here",black);
  SDL_Texture * Message = SDL_CreateTextureFromSurface(renderer,message);
  SDL_Rect message_rect;
  message_rect.x = 0;
  message_rect.y = 100;
  message_rect.w = 100;
  message_rect.h = 100;
  SDL_RenderCopy(renderer, Message, NULL, &message_rect);
  SDL_FreeSurface(message);
  SDL_DestroyTexture(Message);
}*/

void sauvegarder (int score , char nomjoueur[] , char nomfichier[])
{
    int i;
    FILE * sauvegarde = NULL;
    sauvegarde = fopen ("score.txt","r"); //ouverture du fichier sauvegarde 
    //tester si l'ouverture du fichier a reussi
    //succes de l'ouverture
    if (sauvegarde != NULL) 
    {
        fseek(sauvegarde , 0 , SEEK_END);
        fprintf(sauvegarde,"SCORE %d : %d \n",i,score);
    }
    //echec de l'ouverture 
    else
    {
        printf ("ERREUR!! \n IMPOSSIBKE D'OUVRIR LE FICHIER\n");
    }
    fclose (sauvegarde);
}

