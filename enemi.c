#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "enemi.h"

    void initenemie (enemie *e){
        e->sprite=IMG_Load("ennemi_spr.png");
        e->direction=0; //sprite la partie droite
        e->pos.x=1000;
        e->pos.y=600;
        e->possprite.x=0; //0
        e->possprite.y=0;
        e->possprite.h=100;  //100
        e->possprite.w=100;  //100
        e->max.x= 1200;  
        e->min.x=20;  
        
    }

    void afficher_enemie (enemie e,SDL_Surface *screen)
    {
        SDL_BlitSurface(e.sprite,&e.possprite,screen,&e.pos);
    }

  void animate_Enemy(enemie * e){

        e->possprite.y= e->direction * 100 ;   
        e->possprite.x += 100;
        if (e->possprite.x > 300) e->possprite.x=0;
	
    }

  void move_enemy( enemie * e){
   if (e->pos.x > e->max.x) e->direction=1; // si pose enemie > max (limite) retoure a droite (0)
        if (e->pos.x < e->min.x) e->direction=0;                         // retoure a gauche (1)

        if (e->direction==0)
        {
            e->pos.x+=20;
        }

        if (e->direction==1)
        {
            e->pos.x-=20;
        }

    }


int collision_E (enemie e,Personne p){
    int collision;
    if (((p.position.x + p.position.w) >= e.pos.x) ||(((p.position.x + p.position.w) <= (e.pos.x + e.pos.w)) ) || ((p.position.y + p.position.y) < e.pos.y) || (p.position.y > (e.pos.y + e.pos.h)))
    {
        collision = 0;
    }
    else
    {
        collision = 1;
    }
    
    return collision;
}

   
void deplacerIA(enemie * e, Personne p) {
  if (((e -> pos.x - p.position.x) < 200) && ((e -> pos.x - p.position.x) > 80)) {
    e -> direction = 1;
    e -> pos.x -= 20;
  } else if (((e -> pos.x - p.position.x) < -80) && ((e -> pos.x - p.position.x) > -200)) {
    e -> direction = 0;
    e -> pos.x += 20;
  } else if (((e -> pos.x - p.position.x) <= 80) && ((e -> pos.x - p.position.x) >= 0)) {
    e -> direction = 3;
  } else if (((e -> pos.x -p.position.x) <= 0) && ((e -> pos.x - p.position.x) >= -80)) {
    e -> direction = 2;
  }
  else move_enemy(e);

}
