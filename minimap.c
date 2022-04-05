#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"

void initminimap (minimap *m)
{
  m->minimap = IMG_Load("niveau1.png");
  m->posminimap.x=100;
  m->posminimap.y=40;
  m->point = IMG_Load("perso.png");
  m->pospoint.x = 100;
  m->pospoint.y = 80;
}
void afficherminimap (minimap m, SDL_Surface *screen)
{
  SDL_BlitSurface(m.minimap , NULL , screen , &m.posminimap);
  SDL_BlitSurface(m.point, NULL, screen,&m.pospoint);
}
void affichertemps (int temps , SDL_Surface *screen)
{
  TTF_Font *police = NULL;
  police = TTF_OpenFont("Urusans.TTF",40);
  SDL_Color couleur = {0,0,0};
  SDL_Rect post;
  post.x=0;
  post.y=0;
  char s[19];
  sprintf (s,"Temps : %d" , temps );
  SDL_Surface *txt;
  txt = TTF_RenderText_Blended (police, s , couleur);
  SDL_BlitSurface(txt,NULL,screen,&post);
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
  if (camera.x==0)
    p->posperso.x += redimensionnement;
  if (camera.x ==1)
    p->posperso.x -= redimensionnement;
  if (camera.x == 2)
    p->posperso.y += redimensionnement;
  if (camera.x==3)
    p->posperso.y -= redimensionnement;
}
