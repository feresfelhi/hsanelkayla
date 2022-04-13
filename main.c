#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "enemi.h"
#include "perso.h"

int main (int argc,char *argv)
{


TTF_Init ();
SDL_Init(SDL_INIT_VIDEO);

SDL_Surface *screen;
SDL_Surface *img;
perso p;

int done ;
enemie e;

SDL_Event event;
screen = SDL_SetVideoMode (1200,800,32,SDL_HWSURFACE | SDL_SRCALPHA );
if (!screen )
{
printf ("Unable to set 19201080 video : %s \n",SDL_GetError());
return 1;
}
img=IMG_Load ("013847e254bee2b33d4996894e9933fe.jpg");
p.image =IMG_Load ("2.png");
p.pos.x=300;
p.pos.y=350;
p.pos.h=200;
p.pos.w=200;
p.max.x=900;
p.min.x=500;

initenemie (&e);
while(!done){
SDL_BlitSurface(img,NULL,screen,NULL);
SDL_BlitSurface(p.image,NULL,screen,&p.pos);

afficher_enemie (e,screen);
SDL_Flip(screen);
animate_Enemy(&e);
move_enemy(&e);
if (p.pos.x<p.min.x)
{
p.direction=1;
}
if (p.pos.x>p.max.x)
{
p.direction=0;
}
if (p.direction ==1)
{
p.pos.x+=2;
}
else
{
p.pos.x-=2;
}
if(collision(e,p))
{printf("collison = 1 \n ");
done=1;
}
SDL_PollEvent (&event); {
switch (event.type)
{
case SDL_QUIT :
done =1;
}
}
}

}
