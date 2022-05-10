/**  
* @file enigmeImg.c  
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "enigmeImg.h"

/**  
* @brief Initialiser Image
* @param I pour picture
* @param file pour nom de fichier
* @param x pour position de l'image
* @param y pour position de l'image
* @return nothing
*/

void initImg(pic *I, char *file, int x, int y)
{
	I->img=IMG_Load(file);
	if(I->img==NULL)
	{
		return ;
	}
	I->pos_scrn.x=x;
	I->pos_scrn.y=y;
	I->pos_img.x=0;
	I->pos_img.y=0;
	I->pos_img.w=I->img->w;
	I->pos_img.h=I->img->h;
}

/**  
* @brief Initialiser Enigme
* @param e pour enigme
* @param file pour nom de fichier
* @return nothing
*/

int initEnigme(enigme *e ,char *nomfichier)
{	
	int find,i,alt;
	char * quest;
	//enigme e1;
	e->position_enigme.x=600;
	e->position_enigme.y=50;
	srand(time(NULL));
	alt = 1 + rand() % 3 ;
	FILE* Question;
	Question = fopen("question.txt","r");
	if (Question != NULL)
	{i=0;
		while(fscanf(Question,"%s",nomfichier)!=EOF)
		{
		 	if (i == alt)
			{
		 		 e->image_enigme = IMG_Load(nomfichier);
		 	}
		 	else i++;	 	
		}
		fclose(Question);
		return alt;
	}
	else printf("\n ERROR ");
	return alt;
}

/**  
* @brief Afficher Image
* @param I pour picture
* @param screen pour fenetre
* @return nothing
*/

void afficher_img(pic I, SDL_Surface *screen)
{
	SDL_BlitSurface(I.img, &I.pos_img, screen, &I.pos_scrn);
}

/**  
* @brief Afficher Enigme
* @param e pour enigme
* @param screen pour fenetre
* @return nothing
*/

void afficheEnigme(enigme e, SDL_Surface *screen)
{
	SDL_BlitSurface(e.image_enigme, NULL, screen, &(e.position_enigme));
}

/**  
* @brief Resoudre Enigme
* @param e pour enigme
* @return nothing
*/

int resoudreEnigme(enigme *e)
{

}

/**  
* @brief Animer Enigme
* @param e pour enigme
* @return nothing
*/

void animerEnigme(enigme *e)
{
	char nbC[50];
	int x;
	
	for(x=0; x<6 ; x++)
	{
		sprintf(nbC,"Clock/C%d.png",x);
		e->anim[x]=IMG_Load(nbC);
		if(e->anim[x]==NULL)
		{
			return ;
		}
		e->position_anim.x=1;
		e->position_anim.y=1;
		SDL_Delay(50);	
	}
	if(e->alea >= 5)
		e->alea=0;
	e->alea+=1;
		
}
