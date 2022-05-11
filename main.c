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
	SDL_Surface *scre, *perso, *perso2;
	SDL_Rect P, P2, pos, pos2;
	SDL_Event event, event2;
	atexit(SDL_Quit);
	int done=0, lvl=0, collision, U_D1=0, U_D2=0, x=0;
	Background BG[3], BG2[3];
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
	initBack(&BG2[0]);
	
	P.x=40;
	P.y=564;
	P.w=75;
	P.h=150;
	pos.x=BG[0].camera.x+40;
	pos.y=BG[0].camera.y+564;
	perso=IMG_Load("black.png");
		if(perso==NULL)
			return 0;
	P2.x=997;
	P2.y=564;
	P2.w=75;
	P2.h=150;
	pos2.x=BG[0].camera2.x+40;
	pos2.y=BG[0].camera2.y+564;
	perso2=IMG_Load("black.png");
		if(perso2==NULL)
			return 0;
	Uint8 *keystates;
	while(!done)
	{
		SDL_Flip(scre);
		if(BG[lvl].multi_J==1)
		{
			BG[0].camera.w=957;
		}
		else
			BG[0].camera.w=1914;
		//SDL_BlitSurface(BG[0].mask[0], NULL, scre, NULL);
		afficherBack(BG[lvl], scre);
		SDL_BlitSurface(perso, NULL, scre, &P);
		if(BG[lvl].multi_J==1)
			SDL_BlitSurface(perso2, NULL, scre, &P2);
		
		pos.x=BG[0].camera.x+40;
		pos.y=BG[0].camera.y+564;
		pos2.x=BG[0].camera2.x+40;
		pos2.y=BG[0].camera2.y+564;
		if(pos.x<1115 || pos.x>1185)
			U_D1=0;
		if(pos2.x<1115 || pos2.x>1185)
			U_D2=0;
		if(collisionGND( pos, BG[0].mask[0])!=1 && U_D1==0)
			BG[lvl].camera.y+=5;
		if(collisionGND( pos2, BG[0].mask[0])!=1 && U_D2==0)
			BG[lvl].camera2.y+=5;
		
		SDL_PollEvent(&event);
		
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_m:
						BG[lvl].multi_J++;
						BG[lvl].multi_J=BG[lvl].multi_J%2;
						printf("%d",BG[lvl].multi_J);
						SDL_Delay(1000);
						break;
					/*case SDLK_d:
						collision=collisionPP( pos, 0, BG[0].mask[0]);
						scrolling (&(BG[lvl].camera), 0, collision);
						break;
						
					case SDLK_q:
						collision=collisionPP( pos, 1, BG[0].mask[0]);
						scrolling (&(BG[lvl].camera), 1, collision);
						break;
						
					case SDLK_z:
						if(pos.x>=1115 && pos.x<=1185)
						{
							U_D=1;
							collision=collisionPP( pos, 2, BG[0].mask[0]);
							scrolling (&(BG[lvl].camera), 2, collision);
						}
						break;

					case SDLK_s:
						if(pos.x>=1115 && pos.x<=1185)
						{
							U_D=1;
							collision=collisionPP( pos, 3, BG[0].mask[0]);
							scrolling (&(BG[lvl].camera), 3, collision);
						}
						break;
					case SDLK_SPACE:
						while(BG[lvl].camera.y>(-100))
						{
							collision=collisionPP( pos, 2, BG[0].mask[0]);
							scrolling (&(BG[lvl].camera), 2, collision);
							SDL_Flip(scre);
							afficherBack(BG[lvl], scre);
							SDL_BlitSurface(perso, NULL, scre, &P);
							SDL_PollEvent(&event);
							
							switch(event.type)
							{
								case SDL_KEYDOWN:
								switch(event.key.keysym.sym)
								{
									case SDLK_d:
										collision=collisionPP( pos, 0, BG[0].mask[0]);
										scrolling (&(BG[lvl].camera), 0, collision);
										break;
						
									case SDLK_q:
										collision=collisionPP( pos, 1, BG[0].mask[0]);
										scrolling (&(BG[lvl].camera), 1, collision);
										break;
								}
							}
						}
						break;
						
					case SDLK_RIGHT:
						collision=collisionPP( pos2, 0, BG[0].mask[0]);
						scrolling (&BG[lvl].camera2, 0, collision);
						break;
						
					case SDLK_LEFT:
						collision=collisionPP( pos2, 1, BG[0].mask[0]);
						scrolling (&BG[lvl].camera2, 1, collision);
						break;
						
					case SDLK_UP:
						if(pos2.x>=1115 && pos2.x<=1185)
						{
							U_D=1;
							collision=collisionPP( pos2, 2, BG[0].mask[0]);
							scrolling (&BG[lvl].camera2, 2, collision);
						}
						break;

					case SDLK_DOWN:
						if(pos2.x>=1115 && pos2.x<=1185)
						{
							U_D=1;
							collision=collisionPP( pos2, 3, BG[0].mask[0]);
							scrolling (&BG[lvl].camera2, 3, collision);
						}
						break;
					case SDLK_RSHIFT:
						while(BG[lvl].camera2.y>(-100))
						{
							collision=collisionPP( pos2, 2, BG[0].mask[0]);
							scrolling (&BG[lvl].camera2, 2, collision);
							SDL_Flip(scre);
							afficherBack(BG[lvl], scre);
							SDL_BlitSurface(perso, NULL, scre, &P);
							SDL_BlitSurface(perso2, NULL, scre, &P2);
							SDL_PollEvent(&event);
							
							switch(event.type)
							{
								case SDL_KEYDOWN:
								switch(event.key.keysym.sym)
								{
									case SDLK_RIGHT:
										collision=collisionPP( pos2, 0, BG[0].mask[0]);
										scrolling (&BG[lvl].camera2, 0, collision);
										break;
						
									case SDLK_LEFT:
										collision=collisionPP( pos2, 1, BG[0].mask[0]);
										scrolling (&BG[lvl].camera2, 1, collision);
										break;
								}
							}
						}
						/*while(BG[lvl].camera.y<0)
						{
						collision=collisionPP( pos, BG[0].mask[0]);
						scrolling (&BG[lvl], 3, collision);
							SDL_Flip(scre);
							afficherBack(BG[lvl], scre);
							SDL_BlitSurface(perso, NULL, scre, &P);
						}*/
						//break;
				}
				break;
			
			case SDL_QUIT:
				done=1;
				break;
		}
		keystates = SDL_GetKeyState( NULL );
        if( keystates[ SDLK_d ] )
        {
						collision=collisionPP( pos, 0, BG[0].mask[0]);
						scrolling (&(BG[lvl].camera), 0, collision);
        }
        if( keystates[ SDLK_q ] )
        {
						collision=collisionPP( pos, 1, BG[0].mask[0]);
						scrolling (&(BG[lvl].camera), 1, collision);
        }
        if( keystates[ SDLK_z ] && pos.x>=1115 && pos.x<=1185)
        {
							U_D1=1;
							collision=collisionPP( pos, 2, BG[0].mask[0]);
							scrolling (&(BG[lvl].camera), 2, collision);
        }
        if( keystates[ SDLK_s ] && pos.x>=1115 && pos.x<=1185)
        {
							U_D1=1;
							collision=collisionPP( pos, 3, BG[0].mask[0]);
							scrolling (&(BG[lvl].camera), 3, collision);
        }
        if( keystates[ SDLK_SPACE ] && collisionGND( pos, BG[0].mask[0])==1)
        {
						while(BG[lvl].camera.y>(-100))
						{
							collision=collisionPP( pos, 2, BG[0].mask[0]);
							scrolling (&(BG[lvl].camera), 2, collision);
							SDL_Flip(scre);
							afficherBack(BG[lvl], scre);
							SDL_BlitSurface(perso, NULL, scre, &P);
							SDL_PollEvent(&event);
							
							switch(event.type)
							{
								case SDL_KEYDOWN:
								switch(event.key.keysym.sym)
								{
									case SDLK_d:
										collision=collisionPP( pos, 0, BG[0].mask[0]);
										scrolling (&(BG[lvl].camera), 0, collision);
										break;
						
									case SDLK_q:
										collision=collisionPP( pos, 1, BG[0].mask[0]);
										scrolling (&(BG[lvl].camera), 1, collision);
										break;
								}
							}
						}
        }
        if(BG[lvl].multi_J==1)
        {
        		if( keystates[ SDLK_RIGHT ] )
        {
						collision=collisionPP( pos2, 0, BG[0].mask[0]);
						scrolling (&BG[lvl].camera2, 0, collision);
        }
        if( keystates[ SDLK_LEFT ] )
        {
						collision=collisionPP( pos2, 1, BG[0].mask[0]);
						scrolling (&(BG[lvl].camera2), 1, collision);
        }
        if( keystates[ SDLK_UP ] )
        {
						if(pos2.x>=1115 && pos2.x<=1185)
						{
							U_D2=1;
							collision=collisionPP( pos2, 2, BG[0].mask[0]);
							scrolling (&(BG[lvl].camera2), 2, collision);
						}
        }
        if( keystates[ SDLK_DOWN ] )
        {
						if(pos2.x>=1115 && pos2.x<=1185)
						{
							U_D2=1;
							collision=collisionPP( pos2, 3, BG[0].mask[0]);
							scrolling (&(BG[lvl].camera2), 3, collision);
						}
        }
        if( keystates[ SDLK_RSHIFT ] && collisionGND( pos2, BG[0].mask[0])==1)
        {
						while(BG[lvl].camera2.y>(-100))
						{
							collision=collisionPP( pos2, 2, BG[0].mask[0]);
							scrolling (&(BG[lvl].camera2), 2, collision);
							SDL_Flip(scre);
							afficherBack(BG[lvl], scre);
							SDL_BlitSurface(perso, NULL, scre, &P);
							SDL_PollEvent(&event);
							
							switch(event.type)
							{
								case SDL_KEYDOWN:
								switch(event.key.keysym.sym)
								{
									case SDLK_RIGHT:
										collision=collisionPP( pos2, 0, BG[0].mask[0]);
										scrolling (&(BG[lvl].camera2), 0, collision);
										break;
						
									case SDLK_LEFT:
										collision=collisionPP( pos2, 1, BG[0].mask[0]);
										scrolling (&(BG[lvl].camera2), 1, collision);
										break;
								}
							}
						}
        }
        }
	}
	free_BG(BG[0]);
	return 0;
}
		
