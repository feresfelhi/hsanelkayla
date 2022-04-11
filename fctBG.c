#include "fct.h"

void initBack(Background * BG)
{
	int i;
	char* B;
	/*for(i=0; i<5; i++)
	{
		sprintf(B,"lvl1BG%d.png",i);
		BG[0]->anim[i]=IMG_Load(B);
		if(BG[0]->anim[i]==NULL)
			return ;
	}
	
	for(i=0; i<5; i++)
	{
		sprintf(B,"lvl2BG%d.png",i);
		BG[1]->anim[i]=IMG_Load(B);
		if(BG[1]->anim[i]==NULL)
			return ;
	}
	
	for(i=0; i<5; i++)
	{
		sprintf(B,"lvl3BG%d.png",i);
		BG[2]->anim[i]=IMG_Load(B);
		if(BG[2]->anim[i]==NULL)
			return ;
	}
	
	for(i=0; i<3; i++)
	{
		BG[i]->pos_scrn.x=0;
		BG[i]->pos_scrn.y=0;
		BG[i]->pos_img.x=0;
		BG[i]->pos_img.y=0;
		BG[i]->pos_img.w=BG->anim[0]->w;
		BG[i]->pos_img.h=BG->anim[0]->h;
		BG[i].nb_anim=0;
	}*/
	BG[0].anim[0]=IMG_Load("lvl1.png");
		if(BG[0].anim[0]==NULL)
			return ;
	BG[0].mask[0]=SDL_LoadBMP("lvl1mask.bmp");
		if(BG[0].mask[0]==NULL)
			return ;
	BG[0].camera.x=0;
	BG[0].camera.y=0;
	BG[0].camera.w=1914;
	BG[0].camera.h=878;
	BG[0].nb_anim=0;
}

void afficherBack(Background BG, SDL_Surface * scre)
{
	SDL_BlitSurface(BG.anim[BG.nb_anim], &BG.camera, scre, NULL);
}

void animerBackground(Background * BG)
{
	BG->nb_anim++;
}

int collisionPP( SDL_Rect P, SDL_Surface * Mask)
{
	int i, collision=0;
	SDL_Rect pte[8];
	SDL_Color color[8], obs1, obs2;
	Uint32 col=0;
	
	obs1.r=0;
	obs1.g=0;
	obs1.b=255;
	
	obs2.r=0;
	obs2.g=255;
	obs2.b=255;
	
	pte[0].x=P.x;
	pte[0].y=P.y;
	pte[1].x=(P.x+(P.x+50))/2;
	pte[1].y=P.y;
	pte[2].x=P.x+50;
	pte[2].y=P.y;
	
	pte[3].x=P.x;
	pte[3].y=(P.y+(P.y+100))/2;
	pte[4].x=P.x+50;
	pte[4].y=(P.y+(P.y+100))/2;
	
	pte[5].x=P.x;
	pte[5].y=P.y+100;
	pte[6].x=(P.x+(P.x+50))/2;
	pte[6].y=P.y+100;
	pte[7].x=P.x+50;
	pte[7].y=P.y+100;
	
	for(i=0; i<8; i++)
	{
		char* pos=(char*)Mask->pixels;
		pos+=(Mask->pitch*pte[i].y);
		pos+=(Mask->format->BytesPerPixel*pte[i].x);
		memcpy(&col, pos, Mask->format->BytesPerPixel);
		SDL_GetRGB(col, Mask->format, &color[i].r, &color[i].g, &color[i].b);
	}
	if((color[6].r==obs1.r && color[6].g==obs1.g && color[6].b==obs1.b) || (color[5].r==obs1.r && color[5].g==obs1.g && color[5].b==obs1.b) || (color[7].r==obs1.r && color[7].g==obs1.g && color[7].b==obs1.b))
		return 1;
	for(i=0; i<8; i++)
	{
		if(color[i].r==obs2.r && color[i].g==obs2.g && color[i].b==obs2.b)
		/*{
			if(direct==1)
				return 2;
			else if(direct==2)
				return 3;
			else if(direct==3)
				return 4;
			else if(direct==4)
				return 5;
		}*/
			return 2;
	}
	return 0;
}

void scrolling (Background * BG, int direct, int pasAvancement)
{
	int i, j;
	if(pasAvancement==0)
	{
		BG->camera.y+=5;
		switch(direct)
		{
			case 0://right
				if(BG->camera.x<6188-1914)
					BG->camera.x+=5;
			break;
			
			case 1://left
				if(BG->camera.x>0)
					BG->camera.x-=5;
			break;
		}
	}
	if(pasAvancement!=0)
	{
		if(pasAvancement==2)
			BG->camera.y+=5;
		else
		{
			switch(direct)
			{
				case 0://right
					if(BG->camera.x<6188-1914)
						BG->camera.x+=5;
				break;
				
				case 1://left
					if(BG->camera.x>0)
						BG->camera.x-=5;
				break;

				case 2://up
						BG->camera.y-=5;
						//SDL_Delay(30);
					/*for(i=1; i<6; i++)
					{
						BG->camera.y+=i;
						SDL_Delay(40);
					}*/
				break;

				case 3://down
						BG->camera.y+=5;
				break;
			}
		}
	}
}

void free_BG(Background BG)
{
	SDL_FreeSurface(BG.anim[0]);
}
