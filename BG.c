#include "fct.h"

void initBack(Background * BG)
{
	int i;
	char B[50];
	for(i=0; i<3; i++)
	{
		sprintf(B,"%dversionlvl1.png",i);
		BG[0].anim[i]=IMG_Load(B);
		if(BG[0].anim[i]==NULL)
			return ;
	}
	
	BG[0].mask[0]=IMG_Load("versionlvl1Mask.png");
		if(BG[0].mask[0]==NULL)
			return ;
	/*BG[0].mask[1]=IMG_Load("lvl1.png");
		if(BG[0].mask[1]==NULL)
			return ;*/
	BG[0].pos_img.x=0;
	BG[0].pos_img.y=0;
	BG[0].pos_img2.x=957;
	BG[0].pos_img2.y=0;
	BG[0].camera.x=0;
	BG[0].camera.y=0;
	BG[0].camera.w=1914;
	BG[0].camera.h=878;
	BG[0].camera2.x=0;
	BG[0].camera2.y=0;
	BG[0].camera2.w=957;
	BG[0].camera2.h=878;
	BG[0].nb_anim=0;
	BG[0].multi_J=0;
}

void afficherBack(Background BG, SDL_Surface * scre)
{
	SDL_BlitSurface(BG.anim[BG.nb_anim], &BG.camera2, scre, &BG.pos_img2);
	SDL_BlitSurface(BG.anim[BG.nb_anim], &BG.camera, scre, &BG.pos_img);
}

void animerBackground(Background * BG)
{
	BG->nb_anim++;
}

int collisionPP( SDL_Rect P, int direct, SDL_Surface * Mask)
{
	int i, collision=0;
	SDL_Rect pte[8];
	SDL_Color color[8], obs;
	Uint32 col=0;
	
	obs.r=0;
	obs.g=0;
	obs.b=255;
	
	pte[0].x=P.x;
	pte[0].y=P.y;
	pte[1].x=(P.x+(P.x+75))/2;
	pte[1].y=P.y;
	pte[2].x=P.x+75;
	pte[2].y=P.y;
	
	pte[3].x=P.x;
	pte[3].y=(P.y+(P.y+150))/2;
	pte[4].x=P.x+75;
	pte[4].y=(P.y+(P.y+150))/2;
	
	pte[5].x=P.x;
	pte[5].y=P.y+150;
	pte[6].x=(P.x+(P.x+75))/2;
	pte[6].y=P.y+150;
	pte[7].x=P.x+75;
	pte[7].y=P.y+150;
	
	for(i=0; i<8; i++)
	{
		char* pos=(char*)Mask->pixels;
		pos+=(Mask->pitch*pte[i].y);
		pos+=(Mask->format->BytesPerPixel*pte[i].x);
		memcpy(&col, pos, Mask->format->BytesPerPixel);
		SDL_GetRGB(col, Mask->format, &color[i].r, &color[i].g, &color[i].b);
	}
	for(i=0; i<8; i++)
	{
		if(color[i].r==obs.r && color[i].g==obs.g && color[i].b==obs.b)
		{
			return 1;
		}
	}
	return 0;
}
int collisionGND( SDL_Rect P, SDL_Surface * Mask)
{
	int i, collision=0;
	SDL_Rect pte[3];
	SDL_Color color[3], obs;
	Uint32 col=0;
	
	obs.r=0;
	obs.g=255;
	obs.b=255;
	
	pte[0].x=P.x;
	pte[0].y=P.y+150;
	pte[1].x=(P.x+(P.x+75))/2;
	pte[1].y=P.y+150;
	pte[2].x=P.x+75;
	pte[2].y=P.y+150;
	
	for(i=0; i<3; i++)
	{
		char* pos=(char*)Mask->pixels;
		pos+=(Mask->pitch*pte[i].y);
		pos+=(Mask->format->BytesPerPixel*pte[i].x);
		memcpy(&col, pos, Mask->format->BytesPerPixel);
		SDL_GetRGB(col, Mask->format, &color[i].r, &color[i].g, &color[i].b);
	}
	if((color[1].r==obs.r && color[1].g==obs.g && color[1].b==obs.b) || (color[0].r==obs.r && color[0].g==obs.g && color[0].b==obs.b) || (color[2].r==obs.r && color[2].g==obs.g && color[2].b==obs.b))
		return 1;
	return 0;
}

void scrolling (SDL_Rect *pos, int direct, int pasAvancement)
{
	int i, j;
	if(pasAvancement==0)
	{
		switch(direct)
		{
			case 0://right
				if(pos->x<6188-1914)
					pos->x+=5;
			break;
			
			case 1://left
				if(pos->x>0)
					pos->x-=5;
			break;

			case 2://up
				pos->y-=5;
			break;

			case 3://down
				pos->y+=5;
			break;
		}
	}
	if(pasAvancement==1)
	{
		switch(direct)
		{
			case 0://right
				if(pos->x<6188-1914)
					pos->x-=5;
			break;
			
			case 1://left
				if(pos->x>0)
					pos->x+=5;
			break;

			case 2://up
				pos->y+=5;
			break;

			case 3://down
				pos->y-=5;
			break;
		}
	}
}

void free_BG(Background BG)
{
	SDL_FreeSurface(BG.anim[0]);
}
