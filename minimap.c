/*#include "minimap.h"
#include "text.h"
void initminimap(minimap* m)
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
}*/

#include <stdio.h>
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
