#include "fct.h"
#include <unistd.h>
#include <string.h>
#include <SDL/SDL_mixer.h>

int main(int argc, char** argv)
{
	TTF_Init();
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512))
	{
		printf("%s", Mix_GetError());
	}
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	SDL_Surface *scre, *perso;
	SDL_Rect P, pos;
	SDL_Event event, event2;
	atexit(SDL_Quit);
	int done=0, lvl=0, collision;
	Background BG[3];
	Mix_Music *music;
	music=Mix_LoadMUS("music menu.mp3");
	Mix_PlayMusic(music, -1);
	
	scre=SDL_SetVideoMode(1914, 878, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	if(!scre)
	{
		printf("unable to open a 1914x878 wind %s\n", SDL_GetError());
		return 1;
	}
	
	initBack(&BG[0]);
	
	P.x=40;
	P.y=564;
	P.w=75;
	P.h=150;
	pos.x=BG[0].camera.x+40;
	pos.y=BG[0].camera.y+564;
	perso=IMG_Load("black.png");
		if(BG[0].anim[0]==NULL)
			return 0;
	
	while(!done)
	{
		SDL_Flip(scre);
		afficherBack(BG[lvl], scre);
		SDL_BlitSurface(perso, NULL, scre, &P);
		
		pos.x=BG[0].camera.x+40;
		pos.y=BG[0].camera.y+564;
		if(collisionPP( pos, BG[0].mask[0])!=1)
			BG[lvl].camera.y+=5;
		
		SDL_PollEvent(&event);
		
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_d:
						collision=collisionPP( pos, BG[0].mask[0]);
						scrolling (&BG[lvl], 0, collision);
						break;
						
					case SDLK_q:
						collision=collisionPP( pos, BG[0].mask[0]);
						scrolling (&BG[lvl], 1, collision);
						break;
						
					case SDLK_z:
						collision=collisionPP( pos, BG[0].mask[0]);
						scrolling (&BG[lvl], 2, collision);
						break;

					case SDLK_s:
						collision=collisionPP( pos, BG[0].mask[0]);
						scrolling (&BG[lvl], 3, collision);
						break;
					case SDLK_SPACE:
						while(BG[lvl].camera.y>(-100))
						{
							collision=collisionPP( pos, BG[0].mask[0]);
							scrolling (&BG[lvl], 2, collision);
							SDL_Flip(scre);
							afficherBack(BG[lvl], scre);
							SDL_BlitSurface(perso, NULL, scre, &P);
							SDL_PollEvent(&event2);
							
							switch(event2.type)
							{
								case SDL_KEYDOWN:
								switch(event2.key.keysym.sym)
								{
									case SDLK_d:
										collision=collisionPP( pos, BG[0].mask[0]);
										scrolling (&BG[lvl], 0, collision);
										break;
						
									case SDLK_q:
										collision=collisionPP( pos, BG[0].mask[0]);
										scrolling (&BG[lvl], 1, collision);
										break;
								}
							}
						}
						while(BG[lvl].camera.y<0)
						{
						collision=collisionPP( pos, BG[0].mask[0]);
						scrolling (&BG[lvl], 3, collision);
							SDL_Flip(scre);
							afficherBack(BG[lvl], scre);
							SDL_BlitSurface(perso, NULL, scre, &P);
						}
						break;
				}
				break;
			
			case SDL_QUIT:
				done=1;
				break;
		}
	}
	free_BG(BG[0]);
	return 0;
}
		
