#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"

void initminimap (minimap *m)
{
  m->posminimap.x=100;
  m->posminimap.y=30;
  m->minimap[0] = IMG_Load("lvl1.png");
  m->minimap[1] = IMG_Load("lvl 2mini.png");
  m->bonhomme = IMG_Load("miniperso.png");
  m->posbonhomme.x = 100;
  m->posbonhomme.y = 90;
  m->niv=0;
}

void afficherminimap (minimap m, SDL_Surface *screen)
{
  SDL_BlitSurface(m.minimap[m.niv] , NULL , screen , &m.posminimap);
  SDL_BlitSurface(m.bonhomme ,NULL,screen,&m.posbonhomme);
}
void freeminimap(minimap *m)
{
    SDL_FreeSurface(m->minimap[0]);
    SDL_FreeSurface(m->minimap[1]);
}

void affichertemps (int temps , SDL_Surface *screen)
{
  char s[19];
  SDL_Surface *txt;
  TTF_Font *police = NULL;
  police = TTF_OpenFont("QUESTIONOFTIME.TTF",40);
  SDL_Color couleur = {0,0,0}; 
  SDL_Rect post; 
  post.x=0; 
  post.y=0;
  sprintf (s,"Temps : %d" , temps );
  txt = TTF_RenderText_Blended (police, s , couleur);
  SDL_BlitSurface(txt,NULL,screen,&post);
}

/*void afficherscore (SDL_Surface *screen,Personne p,int *score)
{
  char s[19];
  SDL_Surface *sc;
  TTF_Font *police = NULL;
  police = TTF_OpenFont ("Urusans.TTF",40);
  SDL_Color couleur = {0,0,0}; 
  SDL_Rect possc;
  possc.x=0; 
  possc.y=50;
  SDL_Flip(screen);
  if (p.position.x == 400 && p.position.y == 450 ) 
   {
     (*score)++; 
     sprintf (s,"Score : %d" , *score );
     sc = TTF_RenderText_Blended (police, s , couleur);
     SDL_BlitSurface(sc,NULL,screen,&possc);
   }
   else
    {
      sprintf (s,"Score : %d",*score);
      sc = TTF_RenderText_Blended(police , s, couleur);
      SDL_BlitSurface(sc,NULL,screen,&possc);
    }
  TTF_CloseFont(police);
}*/

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

int collisionPPP (Personne p , SDL_Surface *masque)
{
  int collision = 0;
  int x,y,i;
  SDL_Color test , couleurnoir = {0,0,0};
  SDL_Rect pos[8];
  pos[0].x = p.position.x;
  pos[0].y = p.position.y;
  pos[1].x = p.position.x + p.position.w / 2;
  pos[1].y = p.position.y;
  pos[2].x = p.position.x + p.position.w;
  pos[2].y = p.position.y;
  pos[3].x = p.position.x;
  pos[3].y = p.position.y + p.position.h / 2;
  pos[4].x = p.position.x;
  pos[4].y = p.position.y + p.position.h;
  pos[5].x = p.position.x + p.position.w / 2;
  pos[5].y = p.position.y + p.position.h;
  pos[6].x = p.position.x + p.position.w;
  pos[6].y = p.position.y + p.position.h;
  pos[7].x = p.position.x + p.position.w;
  pos[7].y = p.position.y + p.position.h / 2;
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

void majminimap (Personne *p, minimap *m ,SDL_Rect camera , int redimensionnement)
{
  int JoueurABSx ;
  int JoueurABSy;
  JoueurABSx = p->position.x + camera.x;
  JoueurABSy = p->position.y + camera.y;
  m->posbonhomme.x = (JoueurABSx * redimensionnement/100)+100;
  m->posbonhomme.y = (JoueurABSy * redimensionnement/100)-83;
}

void sauvegarder (int score , char nomjoueur[] , char nomfichier[])
{
    FILE * sauvegarde = NULL;
    
    sauvegarde = fopen (nomfichier,"r+"); 
    if (sauvegarde != NULL) 
    	  cherchermeuilleurscore (&score , nomjoueur ,sauvegarde);
    else
        printf ("ERREUR!! \n IMPOSSIBKE D'OUVRIR LE FICHIER\n");
    fclose(sauvegarde);
    
    sauvegarde = fopen (nomfichier,"w"); 
    if (sauvegarde != NULL) 
    	  fprintf(sauvegarde,"%s %d",nomjoueur,score);
    else
        printf ("ERREUR!! \n IMPOSSIBKE D'OUVRIR LE FICHIER\n");
    fclose (sauvegarde);
}

int entrernom (SDL_Surface * screen, char nom[30], int *x, Background *B)
{
  int continuer=1, done=0, a=0, b=0;
  char ch[30];
  char txt[50];
  SDL_Surface *surftxt;
  SDL_Rect pos, pos2, pos3, pos4, pos5, pos6, pos7;
  TTF_Font *font = NULL;
  SDL_Color noir = {0,0,0};
  SDL_Color blanc = {255,255,255};
  SDL_Surface *ecriture ;
  SDL_Rect posecriture;
  TTF_Init();
  posecriture.x = 805;
  posecriture.y = 375;
  font = TTF_OpenFont("Urusans.TTF",80);
  SDL_Event event ;
  SDL_Surface *image, *bg1, *bg2, *single, *multi, *C1, *C2, *C1Grey;
  SDL_Rect posimg ;
  posimg.x = 0;
  posimg.y = 0;
  image = IMG_Load("taille/BG2_4.png");
  bg1 = IMG_Load("menu/startbg0.png");
  bg2 = IMG_Load("menu/startbg1.png");
  single = IMG_Load("menu/single.png");
  multi = IMG_Load("menu/multi.png");
  C1 = IMG_Load("menu/1charac.png");
  C2 = IMG_Load("menu/charac2.png");
  C1Grey = IMG_Load("menu/greyed out.png");
  pos.x = 455;
  pos.y = 80;
  pos2.x = 813;
  pos2.y = 155;
  pos3.x = 810;
  pos3.y = 155;
  pos4.x = 680;
  pos4.y = 330;
  pos5.x = 650;
  pos5.y = 350;
  pos6.x = 1200;
  pos6.y = 330;
  pos7.x = 1200;
  pos7.y = 350;
  surftxt=TTF_RenderText_Blended(font, "entrer votre nom", noir);
  SDL_BlitSurface(image,NULL,screen,&posimg);
  SDL_BlitSurface(bg1,NULL,screen,&pos);
  SDL_BlitSurface(single,NULL,screen,&pos2);
  SDL_BlitSurface(C1,NULL,screen,&pos4);
  SDL_BlitSurface(C1Grey,NULL,screen,&pos6);
  while(!done)
  {	
  		SDL_Flip(screen);
  		SDL_BlitSurface(image,NULL,screen,&posimg);
  		SDL_BlitSurface(bg1,NULL,screen,&pos);
  		if(B->multi_J==0)
  		{
  			SDL_BlitSurface(single,NULL,screen,&pos2);
  			SDL_BlitSurface(C1Grey,NULL,screen,&pos6);
  		}
  		else
  		{
  			SDL_BlitSurface(multi,NULL,screen,&pos3);
			if(b==0)
				SDL_BlitSurface(C1,NULL,screen,&pos6);
			else
				SDL_BlitSurface(C2,NULL,screen,&pos7);
      }
       if(a==0)
			SDL_BlitSurface(C1,NULL,screen,&pos4);
		else
			SDL_BlitSurface(C2,NULL,screen,&pos5);
    	affichermeilleurscore(screen);
    	
    	SDL_WaitEvent(&event);
    	switch(event.type)
    	{
    	  case SDL_QUIT :
    	     	*x=0;
    	     	done=1;
    	      continuer = 0;
    	      break;
    	   
        case SDL_MOUSEBUTTONDOWN :
            if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=935 && event.button.x<=975 && event.button.y>=225 && event.button.y<=260)
            {    
  					if(B->multi_J==0)
  						B->multi_J=1;
  					else
  						B->multi_J=0;
            }
            else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=555 && event.button.x<=635 && event.button.y>=410 && event.button.y<=445)
            {
                if(a==0)
                	a=1;
  					else
  						a=0;
            }
            else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=770 && event.button.x<=855 && event.button.y>=410 && event.button.y<=445)
            {
                if(a==0)
                	a=1;
  					else
  						a=0;
            }
            else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=1075 && event.button.x<=1160 && event.button.y>=410 && event.button.y<=445 && B->multi_J==1)
            {
                if(b==0)
                	b=1;
  					else
  						b=0;
            }
            else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=1290 && event.button.x<=1375 && event.button.y>=410 && event.button.y<=445 && B->multi_J==1)
            {
                if(b==0)
                	b=1;
  					else
  						b=0;
            }
            else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=835 && event.button.x<=1075 && event.button.y>=650 && event.button.y<=715)
            {
                done=1;
            }
            break;
    	}
  }
  B->charac1=a;
  B->charac2=b;
  while (continuer)
  {
    SDL_BlitSurface(image,NULL,screen,&posimg);
    SDL_BlitSurface(bg2, NULL, screen, &pos);
    ecriture = TTF_RenderText_Blended (font , nom , noir);
    SDL_BlitSurface(ecriture,NULL,screen,&posecriture);
    affichermeilleurscore(screen);
    SDL_Flip(screen);
    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT :
         *x=0;
          continuer = 0;
          break;
      case SDLK_ESCAPE :
          *x=0;
          continuer = 0;
          break;
      case SDL_KEYUP :
        switch (event.key.keysym.sym)
        {
          case SDLK_a:
             strcat(nom,"a");
             break;
          case SDLK_z :
             strcat(nom,"z");
             break;
          case SDLK_e :
             strcat(nom,"e");
             break;
             case SDLK_r:
             strcat(nom,"r");
             break;
          case SDLK_t:
             strcat(nom,"t");
             break;
          case SDLK_y :
             strcat(nom,"y");
             break;
             case SDLK_u:
             strcat(nom,"u");
             break;
          case SDLK_i :
             strcat(nom,"i");
             break;
          case SDLK_o :
             strcat(nom,"o");
             break;
             case SDLK_p:
             strcat(nom,"p");
             break;
          case SDLK_q :
             strcat(nom,"q");
             break;
          case SDLK_s :
             strcat(nom,"s");
             break;
             case SDLK_d:
             strcat(nom,"d");
             break;
          case SDLK_f :
             strcat(nom,"f");
             break;
          case SDLK_g :
             strcat(nom,"g");
             break;
             case SDLK_h:
             strcat(nom,"h");
             break;
          case SDLK_j :
             strcat(nom,"j");
             break;
          case SDLK_k :
             strcat(nom,"k");
             break;
             case SDLK_l:
             strcat(nom,"l");
             break;
          case SDLK_m :
             strcat(nom,"m");
             break;
          case SDLK_w :
             strcat(nom,"w");
             break;
             case SDLK_x:
             strcat(nom,"x");
             break;
          case SDLK_c :
             strcat(nom,"c");
             break;
          case SDLK_v :
             strcat(nom,"v");
             break;
             case SDLK_b :
             strcat(nom,"b");
             break;
          case SDLK_n :
             strcat(nom,"n");
             break;
          case SDLK_SPACE :
             strcat(nom," ");
             break;
          case SDLK_RETURN : 
              continuer = 0;
              break;
          case SDLK_BACKSPACE :
             strcpy(nom,"");
             break;
        }
    }
  }
  return continuer ;
}

void cherchermeuilleurscore (int *score , char* nomjoueur , FILE* f) 
{
	char ch[20] = "\0"; 
  	int x=0;
  	char meilleur[20];
  	if (f != NULL)
  	{
  		rewind(f);
     	fscanf(f,"%s %d",meilleur,&x); 
    	printf("%d\n", x);
     	printf("%d\n", *score);
		if(x>(*score))
    	{
      	(*score)=x;
      	strcpy(nomjoueur,meilleur);
     	}
 	}
}
 
void affichermeilleurscore (SDL_Surface *screen)
{
  FILE* f;
  SDL_Rect pos ,pos1;
  SDL_Color noir = {0,0,0};
  SDL_Surface *surftxt;
  SDL_Surface *surfmeil;
  TTF_Font *font;
  char nomjoueur[10],copie[30] ; 
  int score = 0;
  pos.x = 0;
  pos.y = 0;
  pos1.x = 300;
  pos1.y = 0;
  font = TTF_OpenFont ("Urusans.TTF",50);
  TTF_Init();
  f=fopen("score.txt", "r");
  //cherchermeuilleurscore (&score, nomjoueur,f) ;
  fscanf(f,"%s %d",nomjoueur,&score); 
  //printf("%d", x);
  //printf("%d", score);
  fclose(f);
  sprintf(copie,"%s %d",nomjoueur,score);
  surftxt = TTF_RenderText_Blended(font,"meilleur score : ",noir);
  surfmeil = TTF_RenderText_Blended(font,copie,noir);
  SDL_BlitSurface(surftxt,NULL,screen,&pos);
  SDL_BlitSurface(surfmeil,NULL,screen,&pos1);
  //SDL_Flip(screen);
}
