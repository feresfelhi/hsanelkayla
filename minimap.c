#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"

void initmap(minimap *m)
{
    m->position_mini.x = 0;
    m->position_mini.y = 0;
    m->sprite = NULL;
    m->sprite = IMG_Load("minimap1.png");
}

void afficherminimap(minimap m, SDL_Surface *ecran)
{

    SDL_BlitSurface(m.sprite, NULL, ecran, &m.position_mini);
}
void free_minimap(minimap *m)
{
    SDL_FreeSurface(m->sprite);
}

void initialiser_temps(temps *t)
{
    t->texte = NULL;
    t->position.x = 1390;
    t->position.y = 15;
    t->police = NULL;
    t->police = TTF_OpenFont("Bubble Mint.ttf", 40);
    strcpy(t->entree, "");
    (t->secondesEcoulees) = 0;
    time(&(t->t1)); //temps du debut
}

void afficher_temps(temps *t, SDL_Surface *ecran)
{
    SDL_Color couleurnoir = {0, 0, 0};
    
    time(&(t->t2)); // temps actuel

    t->secondesEcoulees = t->t2 - t->t1;

    t->min = ((t->secondesEcoulees / 60) % 60);
    t->sec = ((t->secondesEcoulees) % 60);
    int millisecondes=SDL_GetTicks()%60;
    
    sprintf(t->entree, "%02d:%02d:%02d", t->min, t->sec, millisecondes);    //tekteb l wa9t mm:ss:ms

    t->texte = TTF_RenderText_Blended(t->police, t->entree, couleurnoir);

    SDL_BlitSurface(t->texte, NULL, ecran, &(t->position)); /* Blit du texte */
}

void free_temps(temps *t, SDL_Surface *ecran)
{
    SDL_FreeSurface(t->texte);
    TTF_CloseFont(t->police);
}

SDL_Color GetPixel(SDL_Surface *Background, int x, int y)    //traajaalek l couleur taa lposition eli fiha l perso
{

    SDL_Color color;
    Uint32 col = 0;
    //Determine position

    char *pixelPosition = (char *)Background->pixels;
    //Offset by Y
    pixelPosition += (Background->pitch * y);
    //Offset by X
    pixelPosition += (Background->format->BytesPerPixel * x);
    //Copy pixel data
    memcpy(&col, pixelPosition, Background->format->BytesPerPixel);
    //Convert to color
    SDL_GetRGB(col, Background->format, &color.r, &color.g, &color.b);

    return (color);
}

int collisionPP(Personne p, SDL_Surface *Masque)
{
    SDL_Color test, couleurnoir = {0, 0, 0};

    SDL_Rect pos[8];
//W : 3ardh     H:hauteur 
    pos[0].x = p.position_perso.x;
    pos[0].y = p.position_perso.y;
    pos[1].x = p.position_perso.x + p.position_perso.w / 2;
    pos[1].y = p.position_perso.y;
    pos[2].x = p.position_perso.x + p.position_perso.w;
    pos[2].y = p.position_perso.y;
    pos[3].x = p.position_perso.x;
    pos[3].y = p.position_perso.y + p.position_perso.h / 2;
    pos[4].x = p.position_perso.x;
    pos[4].y = p.position_perso.y + p.position_perso.h;
    pos[5].x = p.position_perso.x + p.position_perso.w / 2;
    pos[5].y = p.position_perso.y + p.position_perso.h;
    pos[6].x = p.position_perso.x + p.position_perso.w;
    pos[6].y = p.position_perso.y + p.position_perso.h;
    pos[7].x = p.position_perso.x + p.position_perso.w;
    pos[7].y = p.position_perso.y + p.position_perso.h / 2;
    int collision = 0, x, y;

    for (int i = 0; i < 8 && collision == 0; i++)  //i hiya l indice mnin mes l perso
    {
        x = pos[i].x;
        y = pos[i].y;
        test = GetPixel(Masque, x, y);
        if (test.r == 0 && test.g == 0 && test.b == 0)
            collision = 1;
    }
    return collision;
}
void majminimap (Personne *p, minimap *m ,SDL_Rect camera ,int redimensionnement)
{      
  if (camera.x==0)
  p->position_perso.x += redimensionnement;

  if (camera.x==1)
  p->position_perso.x -= redimensionnement;

  if (camera.x==2)
  p->position_perso.y += redimensionnement;

  if (camera.x==3)
  p->position_perso.y -= redimensionnement;

}



/*void initminimap(minimap* m)
{
    char *file ;
    int x ,y ;
    m->mini_map=IMG_Load(file);
	if(m->mini_map==NULL)
	{
		return ;
	}
	m->pos_minimap.x=x;
	m->pos_minimap.y=y;
	m->pos_minihero.x=0;
	m->pos_minihero.y=0;
	m->pos_minihero.w=m->mini_hero->w;
	m->pos_minihero.h=m->mini_hero->h;
	m->pos_miniennemi.x=0;
	m->pos_miniennemi.y=0;
	m->pos_miniennemi.w=m->mini_ennemi->w;
	m->pos_miniennemi.h=m->mini_ennemi->h;
	m->pos_minobs.x=0;
	m->pos_minobs.y=0;
	m->pos_minobs.w=m->mini_obs->w;
	m->pos_minobs.h=m->mini_obs->h;
}

void MAJMinimap (SDL_Rect* pos_perso,minimap *m , SDL_Rect camera,int redimensionnement)
{

}

void afficherminimap( minimap m,SDL_Surface *screen)
{
    SDL_BlitSurface(m.mini_map, &m.pos_minimap, screen, &m.pos_scrn);
    SDL_BlitSurface(m.mini_bg, &m.pos_minibg, screen, &m.pos_scrn);
    SDL_BlitSurface(m.mini_ennemi, &m.pos_miniennemi, screen, &m.pos_scrn);
    SDL_BlitSurface(m.mini_hero, &m.pos_minihero, screen, &m.pos_scrn);
    SDL_BlitSurface(m.mini_obs, &m.pos_minobs, screen, &m.pos_scrn);
}

void sauvegarder (int score , char nomjoueur[] , char nomfichier[])
{
    int i;
    FILE * fichier = NULL;
    fichier = fopen ("historique .txt","a+");
    if (fichier != NULL)
    {
        fseek(fichier , 0 , SEEK_END);
        fprintf(fichier,"SCORE %d : %d \n",i,score);
        i=i+1;
        fclose (fichier);
    }
    else
    {
        printf ("ERREUR!! \n IMPOSSIBKE D'OUVRIR LE FICHIER\n");
    }
    return 0;
    /*int i,j;
    FILE* f;
    if (niveau==1)
     {
       f = fopen("historique.txt", "r");
     }
    if (f != NULL)
    {
        for (i=0;i<1;i++)
        {
            fscanf(f,"%u",&score[i]);
            printf("Nom de joueur : %s \n",nomjoueur[i]);
            printf("Record precedent %u\n",score[i]);
        }
        printf("\n");
        fclose(f);
    }
    else
    {
        printf("ERREUR !!!!! \n PS: IMPOSSIBLE D4OUVRIR LE FICHIER\n");
    }
    fflush(stdout);
    if (sec<score[0])
    {
        if (niveau==1)
        f = fopen("rec_fac.txt", "w");
        if (f != NULL)
        {
            fseek(f, 0, SEEK_SET);
            fprintf(,"%u",sec);
            printf("\n");
            fclose(f);
            printf("Nouveau Meilleur Temps sauvegarder\n");
        }
        else
        {
            printf("Impossible d'ouvrir le fichier .txt");
        }
        fflush(stdout);
    }
    getch();
}

void free_minimap(minimap* m)
{
  SDL_FreeSurface(m->mini_bg);
  SDL_FreeSurface(m->mini_ennemi);
  SDL_FreeSurface(m->mini_hero);
  SDL_FreeSurface(m->mini_map);
  SDL_FreeSurface(m->mini_obs);
}
//found on github
/*#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "minimap.h"

image init_image(char nameofpicture[100],int x,int y)
{
image image;
image.img=IMG_Load(nameofpicture);//load image
image.pos.x=x;//position x de bg
image.pos.y=y;//position y de bg
return image;
}
void affichage(SDL_Surface *ecran,image image)
{
SDL_BlitSurface(image.img,NULL,ecran,&image.pos);
}

void librer_image(image image)
{
 SDL_FreeSurface(image.img);//Liberer memoire
}
//amine
void affichertemps (int  temps,SDL_Surface *screen) //temps compteur
{

    TTF_Init();
    TTF_Font *police=NULL;
    police=TTF_OpenFont("Urusans.TTF",40);
    SDL_Color couleur= {255,255,255};
    SDL_Rect postemps;
    postemps.x=0;
    postemps.y=0;
    char s[20]; //pour mettre "temps:"

    sprintf(s,"Temps: %d",temps);
    SDL_Surface *txt;
    txt=TTF_RenderText_Blended(police,s,couleur);
    SDL_BlitSurface(txt,NULL,screen,&postemps); //affichage temps

}
void initmap( minimap * m)
{
  m->minimap=IMG_Load ("cadre minimap.png"); //initialiser cadre minimap
  m->posminimap.x=400;
  m->posminimap.y=20;
  m->minimap=IMG_Load ("niveau1.png"); //initialiser minimap
  m->posminimap.x=1200;
  m->posminimap.y=520;
  m->point=IMG_Load ("miniperso.png"); //initialiser point perso
  m->pospoint.x=400;
  m->pospoint.y=80;
}
void afficherminimap (minimap m, SDL_Surface * screen)
{   
    SDL_BlitSurface(m.minimap,NULL,screen,&m.poscadreminimap); //affichage cadre minimap
    SDL_BlitSurface(m.minimap,NULL,screen,&m.posminimap); //affichage minimap
    SDL_BlitSurface(m.point,NULL,screen,&m.pospoint); //affichage point
}
//x+imin y+tahbet

SDL_Color GetPixel (SDL_Surface* pSurface,int x,int y) //na3tiwha cordonne ta3 il point traj3ilna couleur
{
  SDL_Color color;
  Uint32 col= 0;
  char* pPosition = (char*) pSurface->pixels;
  pPosition += (pSurface->pitch * y);
  pPosition += (pSurface->format->BytesPerPixel * x);
  memcpy (&col,pPosition,pSurface->format->BytesPerPixel);
  SDL_GetRGB (col,pSurface->format,&color.r,&color.g,&color.b);
 return (color);
}

int collisionPP( Personne p, SDL_Surface * Masque)
{
   SDL_Color col;//detecteur du coleur
   if(p.direction==1)//imin
   col=GetPixel(Masque,p.posperso.x+p.perso->w,p.posperso.y+(p.perso->h/2));
   if(p.direction==2)//isar
   col=GetPixel(Masque,p.posperso.x,p.posperso.y+(p.perso->h/2));
   //lfou9
   //col=GetPixel(Masque,p.posperso.x+(p.perso->w/2) ,p.posperso.y); 
  //louta 
   if(p.direction==4)
   col=GetPixel(Masque,p.posperso.x+(p.perso->w/2),p.posperso.y+p.perso->h); 
   if ((col.r==0)&&(col.b==0)&&(col.g==0))
    {
      return 1;
    }
   else return 0;
}

void sauvegarder (int score , char nomjoueur[] , char nomfichier[])
{
    int i;
    FILE * fichier = NULL;
    fichier = fopen ("historique .txt","a+");
    if (fichier != NULL)
    {
        fseek(fichier , 0 , SEEK_END);
        fprintf(fichier,"SCORE %d : %d \n",i,score);
        i=i+1;
        fclose (fichier);
    }
    else
    {
        printf ("ERREUR!! \n IMPOSSIBKE D'OUVRIR LE FICHIER\n");
    }
 }*/
 
