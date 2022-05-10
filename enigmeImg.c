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

void init_Img(Pic *I, char *file, int x, int y)
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

int init_Enigme(enigme *en ,char *nomfichier)
{	
	int find,i,alt;
	char * quest;
	//enigme e1;
	en->position_enigme.x=600;
	en->position_enigme.y=50;
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
		 		 en->image_enigme = IMG_Load(nomfichier);
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

void afficher_Img(Pic I, SDL_Surface *screen)
{
	SDL_BlitSurface(I.img, &I.pos_img, screen, &I.pos_scrn);
}

/**  
* @brief Afficher Enigme
* @param e pour enigme
* @param screen pour fenetre
* @return nothing
*/

void affiche_Enigme(enigme en, SDL_Surface *screen)
{
	SDL_BlitSurface(en.image_enigme, NULL, screen, &(en.position_enigme));
}

/**  
* @brief Resoudre Enigme
* @param e pour enigme
* @return nothing
*/

/*int resoudreEnigme(enigme *en)
{

}
*/

/**  
* @brief Animer Enigme
* @param e pour enigme
* @return nothing
*/

void Enigme_animer(enigme *en)
{
	char nbC[50];
	int x;
	
	for(x=0; x<6 ; x++)
	{
		sprintf(nbC,"Clock/C%d.png",x);
		en->anim[x]=IMG_Load(nbC);
		if(en->anim[x]==NULL)
		{
			return ;
		}
		en->position_anim.x=1;
		en->position_anim.y=1;
		SDL_Delay(50);	
	}
	if(en->alea >= 5)
		en->alea=0;
	en->alea+=1;
		
}
