#include "fonctionperso.h"

void initPerso(Personne *p, char* ch)
{

    int s;
    s=initscore(&p->score);
    p->vie=IMG_Load("love.png");
    p->posvie.x=1500;
    p->posvie.y=77;
    p->posvie2.x=0;
    p->posvie2.y=0;
    p->posvie2.h=p->vie->h;
    p->posvie2.w=p->vie->w;
    
    p->image=IMG_Load(ch);

    p->position.x=0;
    p->position.y=500;

    p->frame.w=110;
    p->frame.h=200;
    p->frame.x=0;
    p->frame.y=0;

    p->nbframe=0;
    p->nbmax=9;
    p->direction=0;
    p->courant=0;

    p->vx = 3;
    p->vgrav = 0.3;
    p->vsaut = -6.5;
    p->vy = p->vsaut;

    p->acceleration=5;
    p->vitesse=10;

}
void initPerso2(Personne *p, char* ch){

 int s;
   s=initscore2 (&p->score);
    p->vie=IMG_Load("love.png");
    p->posvie.x=1300;
    p->posvie.y=77;
    p->posvie2.x=0;
    p->posvie2.y=0;

    p->image=IMG_Load(ch);

    p->position.x=957;
    p->position.y=500;

    p->frame.w=110;
    p->frame.h=200;
    p->frame.x=0;
    p->frame.y=0;

    p->nbframe=0;
    p->nbmax=9;
    p->direction=0;
    p->courant=0;

    p->vx = 3;
    p->vgrav = 0.3;
    p->vsaut = -6.5;
    p->vy = p->vsaut;

    p->acceleration=5;
    p->vitesse=10;


}

void afficherscore (SDL_Surface *screen,int *score)
{
  char s[19];
  SDL_Surface *sc;
  TTF_Font *police = NULL;
  police = TTF_OpenFont ("QUESTIONOFTIME.TTF",30);
  SDL_Color couleur = {0,0,0}; 
  SDL_Rect possc;
  possc.x=1500; 
  possc.y=40;
  sprintf (s,"Score : %d" , *score );
  sc = TTF_RenderText_Blended (police, s , couleur);
  SDL_BlitSurface(sc,NULL,screen,&possc);
  TTF_CloseFont(police);
}

void afficherPerso (Personne p,SDL_Surface *screen)
{


    SDL_BlitSurface(p.vie,&p.posvie2,screen,&(p.posvie));
    //afficher_score(p.score,screen);
    SDL_BlitSurface(p.image,&(p.frame),screen,&(p.position));
}
void animerPerso(Personne *p)
{

    if(p->direction==1)
    {
        p->frame.y=0;
        p->nbframe++;
        if(p->nbframe>=p->nbmax)
        {
            p->nbframe=0;
        }
        p->frame.x=p->nbframe * p->frame.w;

    }
    else if(p->direction==2)
    {
        p->frame.y=200;
        p->nbframe++;
        if(p->nbframe>=p->nbmax)
        {
            p->nbframe=0;
        }
        p->frame.x=p->nbframe * p->frame.w;

    }
    else if(p->direction==3)
    {
        p->frame.y=1600;
        p->nbframe++;
        if(p->nbframe>=5)
        {
           p->nbframe=0;
        }
        p->frame.x=p->nbframe * p->frame.w;

    }
    
    
    else if(p->direction==0)
    {
        p->frame.x=0;

    }

}



void deplacerPerso(Personne *p,SDL_Surface *screen,int dt)
{


    if(dt!= p->courant)
    {
        p->direction=0;
        p->courant = p->direction;
    }

    if (dt==0)
    {
        while(p->position.y<500)
        {
            p->position.y= p->position.y+3;
        }
        p->direction=dt;
        animerPerso(p);

    }

    if (dt==1)
    {
        p->position.x=p->position.x+p->vitesse;
        p->direction=dt;
        animerPerso(p);

    }

    if (dt==2)
    {
        p->position.x= p->position.x-p->vitesse;
        p->direction=dt;
        animerPerso(p);

    }
    if (dt==3)
    {
        //p->position.x= p->position.x-p->vitesse;
        p->direction=dt;
        animerPerso(p);

    }

    if (dt==4)
    {
 
        p->position.y=p->position.y-4;

    }
}
void saut(Personne *p)
{
    if(p->position.y<500)
    {

        p->position.x =  p->position.x +p->vx;
        p->position.y=p->position.y+ p->vy;
        p->vy =p->vy + p->vgrav;

    }
    if (p->position.y> 500)


        p->vy = p->vsaut;


}


void augmenter_vitesse(Personne *p)
{
    SDL_Delay(10);
    p->vitesse= p->vitesse+p->acceleration;
    if(p->vitesse>=40)
    {
        p->vitesse=40;
    }
}
void diminuer_vitesse(Personne *p)
{
    p->vitesse=10;

}


