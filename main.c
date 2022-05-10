#include "enigme.h"
#include <unistd.h>
#include <string.h>
#include <SDL/SDL_mixer.h>

/**  
* @file main.c  
* @brief Testing Program.  
* @author Checkmate  
* @version 0.1  
* @date 2021-2022 
*  
* Testing program for background scrollilng  *  
*/


int main()
{    	enigme e;
	pic mat[3][4];
	char nomfichier[20];
	int done=0,P=0,x,i;
	//x = rand() % 3;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *screen;
	SDL_Event event;
	SDL_Quit();	
	
	initImg(&mat[0][0], "Q10.png", 600, 50);
	initImg(&mat[0][1], "Q11.png", 600, 50);
	initImg(&mat[0][2], "Q12.png", 600, 50);
	initImg(&mat[0][3], "Q13.png", 600, 50);
	initImg(&mat[1][0], "Q20.png", 600, 50);
	initImg(&mat[1][1], "Q21.png", 600, 50);
	initImg(&mat[1][2], "Q22.png", 600, 50);
	initImg(&mat[1][3], "Q23.png", 600, 50);
	initImg(&mat[2][0], "Q30.png", 600, 50);
	initImg(&mat[2][1], "Q31.png", 600, 50);
	initImg(&mat[2][2], "Q32.png", 600, 50);
	initImg(&mat[2][3], "Q33.png", 600, 50);
	
	screen=SDL_SetVideoMode(1914, 934, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	if(!screen)
	{
		printf("unable to open a 1914x934 wind %s\n", SDL_GetError());
		return 1;
	}
	
	x=initEnigme(&e ,nomfichier)-1;
	while(!done)
	{	
		SDL_Flip(screen);
		afficheEnigme(e, screen);
		animerEnigme(&e);
		SDL_BlitSurface(e.anim[e.alea],NULL,screen,(&e.position_anim));
		SDL_PollEvent(&event);
		
		switch(event.type)
		
		{
			case SDL_QUIT:
			{
				done=1;
			}
			break;
		
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_DOWN:
						if(P==0)
						{
							P=1;
							afficher_img(mat[x][2], screen);
						}
						else if(P==1)
						{
							P=2;
							afficher_img(mat[x][3], screen);
						}
						else if(P==2)
						{
							P=0;
							afficher_img(mat[x][1], screen);
						}
						break;
						
					case SDLK_UP:
						if(P==0)
						{
							P=2;
							afficher_img(mat[x][3], screen);
						}
						else if(P==1)
						{
							P=0;
							afficher_img(mat[x][1], screen);
						}
						else if(P==2)
						{
							P=1;
							afficher_img(mat[x][2], screen);
						}
						break;
				}
				break;
				
				
		case SDL_MOUSEMOTION:
            	if(event.motion.x>=650 && event.motion.x<=1300 && event.motion.y>=250 && event.motion.y<=400)
            {
		afficher_img(mat[x][1], screen);
                P=0;
            }
            else if(event.motion.x>=650 && event.motion.x<=1300 && event.motion.y>=450 && event.motion.y<=550)
            {
		afficher_img(mat[x][2], screen);
                P=1;
            }
            else if(event.motion.x>=650 && event.motion.x<=1300 && event.motion.y>=600 && event.motion.y<=750)
            {
            	afficher_img(mat[x][3], screen);
                P=2;
            }
            else
            {
                afficher_img(mat[x][0], screen);
            }
            break;
						
			}
	}
	
	SDL_FreeSurface(screen);
}
