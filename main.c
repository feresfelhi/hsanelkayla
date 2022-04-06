#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"

int main()
{
  int collision , distance=100 , exit=1; //exit variable de la boucle du jeux
  int temps;
  int frame=0;//pour savoir fps
  Uint32 start,end;//pour fps
  const int FPS=20;//fixation fps en 20
  SDL_Event event;
  minimap m;
  personne p , pM , pMprochaine ;
  SDL_Surface *screen = NULL , *imageFond = NULL , *masked = NULL , *chiffres[30];
  SDL_Rect posBG , poschiffres , poscamera;
  int longeurM=8000 , largeurM = 800, longeur = 800 , largeur = 80, i=0;
  int redimonsionnement = distance * longeur /longeurM;
  screen = SDL_SetVideoMode(1600, 800,32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
  TTF_Init();
  if (screen == NULL)
   {
     printf("ERREUR: %s\n", SDL_GetError());
     return 1;
   }
  posBG.x=0;
  posBG.y=0;
  imageFond = IMG_Load("lvl1.png");//image kbira il principal
  //initialisation du minimap
  initminimap(&m); 
  masked = IMG_Load("map1_masked.png");
  //mini personnage
  p.perso = IMG_Load("miniperso.png");
  p.posperso.x = 0;
  p.posperso.y = 150;
  //personnage principale
  pM.perso = IMG_Load("perso.png");
  pM.posperso.x = 0;
  pM.posperso.y = 450;
  //position prochaine du personnage principale
  pMprochaine.posperso.x = pM.posperso.x;
  pMprochaine.posperso.y = pM.posperso.y; 
  while (exit)
   {
     start=SDL_GetTicks();
     SDL_BlitSurface(imageFond,NULL,screen,&posBG);
     //affichage de la minimap
     afficherminimap(m,screen);
     SDL_BlitSurface(p.perso,NULL,screen,&p.posperso);
     SDL_BlitSurface(pM.perso,NULL,screen,&pM.posperso);
     //affichage temps
     affichertemps ( temps,screen);
     while (SDL_PollEvent(&event))
      {
        switch (event.type)
         {
           case SDL_QUIT:
             exit = 0;
             break;
           case SDL_KEYDOWN :
             switch(event.key.keysym.sym)
              {
                case SDLK_ESCAPE :
                  exit = 0;
                  break;
                //ymin
                case SDLK_RIGHT :
                  pMprochaine.posperso.x += distance;
                  if (collisionPP(pMprochaine , masked)==0)
                   {
                     poscamera.x=0;
                     pM.posperso.x = pMprochaine.posperso.x;
                     majminimap(&p,&m,poscamera,redimonsionnement);
                   }
                  else
                   {
                     if (i==13)
                       i=0;
                     i++;
                     pMprochaine.posperso.x = pM.posperso.x;
                     SDL_BlitSurface(chiffres[i],NULL,screen,&pM.posperso);
                     SDL_Delay(300);
                   }
                   break;
                //ysar
                case SDLK_LEFT:
                  pMprochaine.posperso.x -= distance;
                  if (collisionPP(pMprochaine , masked)==0)
                   {
                     poscamera.x=1;
                     pM.posperso.x = pMprochaine.posperso.x;
                     majminimap(&p,&m,poscamera,redimonsionnement);
                   }
                  else
                   {
                     if (i==13)
                       i=0;
                     i++;
                     pMprochaine.posperso.x = pM.posperso.x;
                     SDL_BlitSurface(chiffres[i],NULL,screen,&pM.posperso);
                     SDL_Delay(300);
                   }
                   break;
                //louta
                case SDLK_DOWN :
                  pMprochaine.posperso.y += distance;
                  if (collisionPP(pMprochaine , masked)==0)
                   {
                     poscamera.x=2;
                     pM.posperso.y = pMprochaine.posperso.y;
                     majminimap(&p,&m,poscamera,redimonsionnement);
                   }
                  else
                   {
                     if (i==13)
                       i=0;
                     i++;
                     pMprochaine.posperso.y = pM.posperso.y;
                     SDL_BlitSurface(chiffres[i],NULL,screen,&pM.posperso);
                     SDL_Delay(300);
                   }
                   break;
                //fou9
                case SDLK_UP:
                  pMprochaine.posperso.y -= distance;
                  if (collisionPP(pMprochaine , masked)==0)
                   {
                     poscamera.x=3;
                     pM.posperso.y = pMprochaine.posperso.y;
                     majminimap(&p,&m,poscamera,redimonsionnement);
                   }
                  else
                   {
                     if (i==13)
                       i=0;
                     i++;
                     pMprochaine.posperso.y = pM.posperso.y;
                     SDL_BlitSurface(chiffres[i],NULL,screen,&pM.posperso);
                     SDL_Delay(300);
                   }
                   break;
              }
         } 
      }
      SDL_Flip(screen);//permute les tompons dd'ecran
      temps=60;
      if(frame==20)
       {
         if(temps>0)
           temps--;
         frame=0;
       }
      frame++;  
      if(1000/FPS>SDL_GetTicks()-start)
         SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
   } 
   
   freeminimap(&m);
   SDL_FreeSurface(p.perso);
   SDL_FreeSurface(chiffres[1]);
   SDL_FreeSurface(chiffres[2]);
   SDL_FreeSurface(chiffres[3]);
   SDL_FreeSurface(chiffres[4]);
   SDL_FreeSurface(chiffres[5]);
   SDL_FreeSurface(chiffres[6]);
   SDL_FreeSurface(chiffres[7]);
   SDL_FreeSurface(chiffres[8]);
   SDL_FreeSurface(chiffres[9]);
   SDL_FreeSurface(chiffres[10]);
   SDL_FreeSurface(chiffres[11]);
   SDL_FreeSurface(chiffres[12]);
   SDL_FreeSurface(chiffres[13]);
   SDL_FreeSurface(screen);
   TTF_Quit();
   SDL_Quit();
   return EXIT_SUCCESS;
}
