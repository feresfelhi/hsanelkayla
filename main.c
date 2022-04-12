#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h> 
#include <time.h>
#include "fonctionperso.h"

int main()
{
	int hauteur_fenetre = 1100,t,a=1,done=1,sc=1,//g=0,
         dt=0,
        	largeur_fenetre = 1920;
	SDL_Event event;
	
	//printf("donner le mode de jouer  : \n 1 ->  1 joueur || 2 -> 2 joueurs ");
	//scanf("%d",&g);

	SDL_Init(SDL_INIT_VIDEO);
//creation de la fenetre 
	SDL_Surface *screen;
	 if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("unable to initialize SDL: %s\n",SDL_GetError());
        return 1;
    }
 	screen=SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    if(screen==NULL)
    {
        printf("unable to set video mode:%s\n",SDL_GetError());
        return 1;
    }
  
	SDL_WM_SetCaption("JEUX", NULL); 
// creation background
 	SDL_Surface *backg;
	SDL_Rect backg_pos;
	backg = IMG_Load("BG2.png");
	backg_pos.x = 0;
	backg_pos.y = 0;

 //initialisation 


 
	Personne p;
	
	
	initPerso(&p);
	
	
	SDL_EnableKeyRepeat(200, 0);
	 while(done)
    {  
	
    	SDL_PollEvent(&event);
 
     switch(event.type)

     {  
     	case SDL_QUIT: 
		done=0;
		break;
	case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {  
		case SDLK_s: 
               	dt=0;
               	deplacerPerso(&p ,screen,dt);
		break;
		
		case 	
		SDLK_RIGHT: 
               	dt=1;
               	deplacerPerso(&p ,screen,dt);
		break;
			
		case SDLK_LEFT: 
               	dt=2;
               	deplacerPerso(&p ,screen,dt);
		break;
		case SDLK_SPACE:
			dt=3;
               	deplacerPerso(&p ,screen,dt);
	
			
		break;
		
		case SDLK_UP:
			vitesseUP(&p);
		break;
		
		case SDLK_DOWN:
			vitesseDOWN(&p);
		break;
               
		case SDLK_ESCAPE: 
              		done=0;
		break; 
                
            }
      
     }   

	SDL_BlitSurface(backg,NULL,screen,&backg_pos);
	//if (g==1){
		afficherPerso (p,screen);
		saut(&p);
	//}

	
     	SDL_Flip(screen);
    }
	





	
	
	
	SDL_FreeSurface(backg);
	SDL_Quit();

    return 0;
}










