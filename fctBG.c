#include "fctBG.h"

void initBack(Background * BG)
{
	int i;
	char B[50];
	//for(i=0; i<3; i++)
	//{
		//sprintf(B,"%dversionlvl1.png",i);
		BG[0].anim[0]=IMG_Load("0versionlvl1.png");
		if(BG[0].anim[0]==NULL)
			return ;
		BG[1].anim[0]=IMG_Load("lvl 2.png");
		if(BG[1].anim[0]==NULL)
			return ;
	//}
	
	BG[0].mask[0]=IMG_Load("0versionlvl1Mask.png");
		if(BG[0].mask[0]==NULL)
			return ;
	BG[1].mask[0]=IMG_Load("lvl 2Mask.png");
		if(BG[1].mask[0]==NULL)
			return ;
	/*BG[0].mask[1]=IMG_Load("lvl1.png");
		if(BG[0].mask[1]==NULL)
			return ;*/
	for(i=0; i<2; i++)
	{
		BG[i].pos_img.x=0;
		BG[i].pos_img.y=0;
		BG[i].pos_img2.x=957;
		BG[i].pos_img2.y=0;
		BG[i].camera.x=0;
		BG[i].camera.y=470;
		BG[i].camera.w=1914;
		BG[i].camera.h=878;
		BG[i].camera2.x=0;
		BG[i].camera2.y=470;
		BG[i].camera2.w=957;
		BG[i].camera2.h=878;
		BG[i].nb_anim=0;
		BG[i].multi_J=0;
	}
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

SDL_Color GetColPixel(SDL_Surface* Mask, int x, int y)
{
	SDL_Color color;
	Uint32 col=0;
	char* pos=(char*)Mask->pixels;
	pos+=(Mask->pitch*y);	
	pos+=(Mask->format->BytesPerPixel*x);
	memcpy(&col, pos, Mask->format->BytesPerPixel);
	SDL_GetRGB(col, Mask->format, &color.r, &color.g, &color.b);
	return (color);
}

int collisionPP( SDL_Rect P, SDL_Surface * Mask)
{
	int i, collision=0;
	SDL_Rect pte[8];
	SDL_Color color[8], obs;
	
	obs.r=0;
	obs.g=0;
	obs.b=255;
	
	pte[0].x=P.x;
	pte[0].y=P.y;
	pte[3].x=(P.x+(P.x+50))/2;
	pte[3].y=P.y;
	pte[5].x=P.x+50;
	pte[5].y=P.y;
	
	pte[1].x=P.x;
	pte[1].y=(P.y+(P.y+163))/2;
	pte[6].x=P.x+50;
	pte[6].y=(P.y+(P.y+163))/2;
	
	pte[2].x=P.x;
	pte[2].y=P.y+163;
	pte[4].x=(P.x+(P.x+50))/2;
	pte[4].y=P.y+163;
	pte[7].x=P.x+50;
	pte[7].y=P.y+163;
	
	for(i=0; i<8; i++)
	{
		color[i]=GetColPixel(Mask, pte[i].x, pte[i].y);
	}
	for(i=0; i<3; i++)
	{
		if(color[i].r==obs.r && color[i].g==obs.g && color[i].b==obs.b)
		{
			return 2;
		}
	}
	for(i=5; i<8; i++)
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
	pte[0].y=P.y+163;
	pte[1].x=(P.x+(P.x+50))/2;
	pte[1].y=P.y+163;
	pte[2].x=P.x+50;
	pte[2].y=P.y+163;
	
	for(i=0; i<3; i++)
	{
		color[i]=GetColPixel(Mask, pte[i].x, pte[i].y);
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
				//if(pos->x<6188-1914)
					pos->x+=10;
			break;
			
			case 1://left
				//if(pos->x>0)
					pos->x-=10;
			break;

			case 2://up
				pos->y-=10;
			break;

			case 3://down
				pos->y+=10;
			break;
		}
	}
	if(pasAvancement==1)
	{
		switch(direct)
		{
			case 1://left
				if(pos->x>0)
					pos->x-=10;
			break;

			case 2://up
				pos->y-=10;
			break;

			case 3://down
				pos->y+=10;
			break;
		}
	}
	if(pasAvancement==2)
	{
		switch(direct)
		{
			case 0://right
				//if(pos->x<6188-1914)
					pos->x+=10;
			break;
			case 2://up
				pos->y-=10;
			break;

			case 3://down
				pos->y+=10;
			break;
		}
	}
	/*if(pasAvancement==1)
	{
		switch(direct)
		{
			case 0://right
				if(pos->x<6188-1914)
					pos->x-=20;
			break;
			
			case 1://left
				if(pos->x>0)
					pos->x+=20;
			break;

			case 3://down
				pos->y-=20;
			break;
		}
	}*/
}

void free_BG(Background BG)
{
	SDL_FreeSurface(BG.anim[0]);
}
