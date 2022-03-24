#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "minimap.h"
int main()
{
   int temps;
   SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO);//audio
   if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)!=0)
    {
        printf("error : %s \n",SDL_GetError());
        return 1;
    }
   SDL_Event event;//manipulation du clavier
   SDL_Surface *screen;
   //environnement
   SDL_Surface *image;//background
   SDL_Surface *imageM;//masque
   SDL_Rect posimage;//position background
   posimage.x=0;
   posimage.y=0;
   image=IMG_Load("lbo3.jpg");//background
   imageM=IMG_Load("masque.jpg");//masque
   //personnage
   Personne p;
   p.posperso.x=0;
   p.posperso.y=600;
   p.posperso.h=267;
   p.posperso.w=200;
   p.perso=IMG_Load("8.png");
   screen=SDL_SetVideoMode(1920,1360,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if(screen==NULL)
    {
        printf("error : %s \n",SDL_GetError());
        return 1;
    }
    
   int gamerunning=1;//variable pour boucle while
   int frame=0;//pour savoir fps
   Uint32 start,end;//pour fps
   const int FPS=20;//fixation fps en 20
   temps=60;
   //minimap
   minimap m;//declaration minimap
   initmap(&m);
   SDL_EnableKeyRepeat(1,1);//to press many times on keys
   while(gamerunning)
    {
      start=SDL_GetTicks();
      // SDL_BlitSurface(imageM,NULL,screen,&posimage);
      SDL_BlitSurface(image,NULL,screen,&posimage);
      SDL_BlitSurface(p.perso,NULL,screen,&p.posperso);
      afficherminimap (m,  screen);
      //generer le temps
      affichertemps ( temps,screen);
       while(SDL_PollEvent(&event))
        {
          switch(event.type)
            {
              case SDL_QUIT:
                gamerunning=0;
                break;
              case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                  {
                    case SDLK_ESCAPE:
                      gamerunning=0;
                      break;
                    case SDLK_RIGHT:
                       p.direction=1;
		        if(collisionPP(p,imageM)==0)//if collision il ya arret de mvt
		         {
                          p.posperso.x+=11;
		           if(m.pospoint.x>=m.posminimap.x)//point follow player
		           m.pospoint.x++;
                         }
                        break;
                    case SDLK_LEFT:
		       p.direction=2;
		       if(collisionPP(p,imageM)==0)
		        {
                         p.posperso.x-=11;
		          if(m.pospoint.x>=m.posminimap.x)
		          m.pospoint.x--;
                        }
                        break;
                    case SDLK_UP:
		       p.direction=3;
		       if(collisionPP(p,imageM)==0)
		        {
                          p.posperso.y-=11;
                        }
                        break;
                    case SDLK_DOWN:
		       p.direction=4;
		       if(collisionPP(p,imageM)==0)
		        {
                          p.posperso.y+=11;
	
                        }
                       break;
                     }
                     break;
            }
        }
        SDL_Flip(screen);
       //temps
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
}



//found on github
/*void main()
{
    int compteur=1;
    int i;
    int continuer=1;
    SDL_Event event;
    SDL_Surface *ecran =NULL;
    ecran = SDL_SetVideoMode(798, 582, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    image personnage,minimap,minimap2,minimap3,minimap4,minimap5,point,youssef,perso_initial,map,map2,map3,map4,map5;

    SDL_Surface *perso[8] = {NULL};
    perso[0] = IMG_Load("image/mage1.png");
    perso[1] = IMG_Load("image/mage2.png");
    perso[2] = IMG_Load("image/mage3.png");
    perso[3] = IMG_Load("image/mage4.png");
    perso[4] = IMG_Load("image/mage5.png");
    perso[5] = IMG_Load("image/mage6.png");
    perso[6] = IMG_Load("image/mage7.png");
  
    //////////////////////////////////////////
    personnage=init_image("image/character.png",23,390);
    point=init_image("image/icontest.png",0,80);
    //////////////////////////////////////////
    minimap=init_image("image/min.png",0,0);
    minimap2=init_image("image/min2.png",0,0);
    minimap3=init_image("image/min3.png",0,0);
    minimap4=init_image("image/min4.png",0,0);
    minimap5=init_image("image/min5.png",0,0);
    //////////////////////////////////////////
    map=init_image("image/stage1.png",0,0);
    map2=init_image("image/stage2.png",0,0);
    map3=init_image("image/stage3.png",0,0);
    map4=init_image("image/stage4.png",0,0);
    map5=init_image("image/stage5.png",0,0);

    SDL_EnableKeyRepeat(100,100);
    while(continuer)
        {
        while(SDL_PollEvent(&event))
          {
            switch(event.type){
                case SDL_QUIT:
                    continuer=0;
                break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                        if(i >= 6)
                        i = 0;    
                        i++;                 
                            if(personnage.pos.x < 743)
                            {
                                personnage.pos.x += 20;
                                point.pos.x += 3;
                            }
                        break;
                        case SDLK_LEFT:
                        if(i >= 6)
                        i = 0;    
                        i++; 
                            if(personnage.pos.x > 10)
                            {
                                personnage.pos.x -= 20;
                                point.pos.x -= 3;
                            }
                        break;
                    }
                printf("pos %d \n",personnage.pos.x);
                break;
                }
            }
            if(personnage.pos.x>=743)
            {
             personnage.pos.x=0;
             point.pos.x=0;
             if(compteur<5)
             {
             compteur++;
             }
             printf("compteur %d \n",compteur);
            }
            if(compteur==1)
           {
            affichage(ecran,map);
            affichage(ecran,minimap); 
           }
            if(compteur==2)
            {
            affichage(ecran,map2); 
            affichage(ecran,minimap2); 
            }
            if(compteur==3)
            {
            affichage(ecran,map3); 
            affichage(ecran,minimap3); 
            }
            if(compteur==4)
            {
            affichage(ecran,map4); 
            affichage(ecran,minimap4); 
            }
            if(compteur==5)
            {
            affichage(ecran,map5); 
            affichage(ecran,minimap5); 
            }
        affichage(ecran,point);   
        SDL_BlitSurface(perso[i], NULL,ecran, &personnage.pos);  
        SDL_Flip(ecran);   
    }

    librer_image(map);
    librer_image(map2);
    librer_image(map3);
    librer_image(map4);
    librer_image(map5);
    librer_image(point);
    librer_image(minimap);
    librer_image(minimap2);
    librer_image(minimap3);
    librer_image(minimap4);
    librer_image(minimap5);
    SDL_Quit();     
}*/
