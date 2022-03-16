#include "minimap.h"

void initminimap(minimap* m)
{
    char *file ;
    int x ,y ;
    m->minimap=IMG_Load(file);
	if(m->minimap==NULL)
	{
		return ;
	}
	m->pos_minimap.x=x;
	m->pos_minimap.y=y;
	m->pos_minihero.x=0;
	m->pos_minihero.y=0;
	m->pos_minihero.w=I->img->w;
	m->pos_minihero.h=I->img->h;
	m->pos_miniennemi.x=0;
	m->pos_miniennemi.y=0;
	m->pos_miniennemi.w=I->img->w;
	m->pos_miniennemi.h=I->img->h;
	m->pos_minobs.x=0;
	m->pos_minobs.y=0;
	m->pos_minobs.w=I->img->w;
	m->pos_minobs.h=I->img->h;
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

void sauvegarder (int score[] , char nomjoueur[] , char nomfichier[])
{
    int i,j;
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
    return 0;
}

void free_minimap(minimap* m)
{
  SDL_FreeSurface(m.mini_bg);
  SDL_FreeSurface(m.mini_ennemi);
  SDL_FreeSurface(m.mini_hero);
  SDL_FreeSurface(m.mini_map);
  SDL_FreeSurface(m.mini_obs);
}
