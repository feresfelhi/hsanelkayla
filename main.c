#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"

int main()
{
    int collision, distance = 100;
    SDL_Event event;
    minimap m;
    Personne p, pM, pMprochaine;
    temps t;
    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *masked = NULL,*chiffres[30];
    SDL_Rect position_BG, position_chiffres , position_camera;
    int longueurM = 8000, largeurM = 800, longueur = 800, largeur = 80, i = 0;
    int redimensionnement =  distance * longueur / longueurM;
    ecran = SDL_SetVideoMode(1600, 800, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    TTF_Init();
    if (ecran == NULL)
    {
        printf("ERREUR: %s\n", SDL_GetError());
        return 1;
    }

    position_BG.x = 0;
    position_BG.y = 0;

    imageDeFond = IMG_Load("niveau1.png");
    int continuer = 1;
    initmap(&m);
    initialiser_temps(&t);
    
    masked = IMG_Load("map1_masked.png");

    p.sprite = IMG_Load("miniperso.png");
    p.position_perso.x = 0;
    p.position_perso.y = 40;

    pM.sprite = IMG_Load("perso.png");
    pM.position_perso.x = 0;
    pM.position_perso.y = 350; //550

    pMprochaine.position_perso.x = pM.position_perso.x;
    pMprochaine.position_perso.y = pM.position_perso.y;

    /*chiffres[1] = IMG_Load("img/1.png");
    chiffres[2] = IMG_Load("img/2.png");
    chiffres[3] = IMG_Load("img/3.png");
    chiffres[4] = IMG_Load("img/4.png");
    chiffres[5] = IMG_Load("img/5.png");
    chiffres[6] = IMG_Load("img/6.png");
    chiffres[7] = IMG_Load("img/7.png");
    chiffres[8] = IMG_Load("img/8.png");
    chiffres[9] = IMG_Load("img/9.png");
    chiffres[10] = IMG_Load("img/10.png");
    chiffres[11] = IMG_Load("img/11.png");
    chiffres[12] = IMG_Load("img/12.png");
    chiffres[13] = IMG_Load("img/13.png");*/
   

    while (continuer)
    {

        SDL_BlitSurface(imageDeFond, NULL, ecran, &position_BG);
        afficherminimap(m, ecran);
        SDL_BlitSurface(p.sprite, NULL, ecran, &p.position_perso);
        SDL_BlitSurface(pM.sprite, NULL, ecran, &pM.position_perso);
        afficher_temps(&t, ecran);

        //mapCollision(Hero *entity);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                case SDLK_RIGHT:
                    pMprochaine.position_perso.x += distance;
                    if (collisionPP(pMprochaine, masked) == 0)
                    { position_camera.x=0;
 
                        pM.position_perso.x = pMprochaine.position_perso.x;
                        
                        majminimap(&p,&m,position_camera,redimensionnement);
                    }
                    else
                    {  if (i==13)
                          i=0; 
                        i++;
                        pMprochaine.position_perso.x = pM.position_perso.x;
                        SDL_BlitSurface(chiffres[i], NULL, ecran, &pM.position_perso);
                        SDL_Delay(300);
                    }
                    break;

                case SDLK_LEFT:
                    pMprochaine.position_perso.x -= distance;
                    if (collisionPP(pMprochaine, masked) == 0)
                    {   position_camera.x=1;
                        pM.position_perso.x = pMprochaine.position_perso.x;
                        majminimap(&p,&m,position_camera,redimensionnement);
                    }
                    else
                    {  if (i==13)
                          i=0;
                        i++;
                        pMprochaine.position_perso.x = pM.position_perso.x;
                        SDL_BlitSurface(chiffres[i], NULL, ecran, &pM.position_perso);
                        SDL_Delay(300);
                    }
                break;


                    case SDLK_DOWN:
                    pMprochaine.position_perso.y += distance;
                    if (collisionPP(pMprochaine, masked) == 0)
                    {
                        position_camera.x=2;
                        pM.position_perso.y = pMprochaine.position_perso.y;
                        majminimap(&p,&m,position_camera,redimensionnement);
                    }
                    else
                    {  if (i==13)
                          i=0;
                        i++;
                        pMprochaine.position_perso.y = pM.position_perso.y;
                        SDL_BlitSurface(chiffres[i], NULL, ecran, &pM.position_perso);
                        SDL_Delay(300);
                    }
                    break;



                case SDLK_UP:
                    pMprochaine.position_perso.y -= distance;
                    if (collisionPP(pMprochaine, masked) == 0)
                    {   position_camera.x=3;
                        pM.position_perso.y = pMprochaine.position_perso.y;
                        majminimap(&p,&m,position_camera,redimensionnement);
                    }
                    else
                    {   if (i==13)
                          i=0;
                        i++;
                        pMprochaine.position_perso.y = pM.position_perso.y;
                        SDL_BlitSurface(chiffres[i], NULL, ecran, &pM.position_perso);
                        SDL_Delay(300);
                    }

                    break;

                case SDLK_p:
                    imageDeFond = IMG_Load("map1_masked.png");
                    break;
                case SDLK_o:
                  imageDeFond = IMG_Load("niveau1.png");

                }
                
            }
        }
        SDL_Flip(ecran);
    }
    free_minimap(&m);
    SDL_FreeSurface(p.sprite);

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

    free_temps(&t, ecran);
    SDL_FreeSurface(ecran);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}


/*#include <stdlib.h>
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
   image=IMG_Load("nBG.png");//background
   imageM=IMG_Load("cadre minimap.png");//masque
   //personnage
   Personne p;
   p.posperso.x=0;
   p.posperso.y=600;
   p.posperso.h=267;
   p.posperso.w=200;
   p.perso=IMG_Load("perso.png");
   screen=SDL_SetVideoMode(1920,1360,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if(screen==NULL)
    {
        printf("error : %s \n",SDL_GetError());
        return 1;
    }
    
   int exit=1; //variable pour boucle while
   int frame=0; //pour savoir fps
   Uint32 start,end; //pour fps
   const int FPS=20; //fixation fps en 20
   temps=1800;
   //minimap
   minimap m; //declaration minimap
   initminimap(&m);
   SDL_EnableKeyRepeat(1,1); //to press many times on keys
   while(exit)
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
                exit=0;
                break;
              case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                  {
                    case SDLK_ESCAPE:
                      exit=0;
                      break;
                    case SDLK_RIGHT:
                       p.direction=1;
		        if(collisionPP(p,imageM)==0) //if collision il ya arret de mvt
		         {
                          p.posperso.x+=11;
		           if(m.pospoint.x>=m.posminimap.x) //point follow player
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
}*/



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
