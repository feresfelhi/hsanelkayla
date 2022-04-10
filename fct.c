#include "fct.h"

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

void initImgS(pic *I, char *file, int x, int y)
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
void free_img(pic I)
{
	SDL_FreeSurface(I.img);
}

void afficher_img(pic I, SDL_Surface *screen)
{
	SDL_BlitSurface(I.img, &I.pos_img, screen, &I.pos_scrn);
}

void initText(text *T, int x, int y, int size, char* font)
{
	T->pos.x=x;
	T->pos.y=y;
	T->color.r=255;
	T->color.g=255;
	T->color.b=255;
	T->font=TTF_OpenFont(font, size);
}

void initTitle(text *T, int x, int y, int size, char* font)
{
	T->pos.x=x;
	T->pos.y=y;
	T->color.r=255;
	T->color.g=0;
	T->color.b=0;
	T->font=TTF_OpenFont(font, size);
}

void freetext(text T)
{
	SDL_FreeSurface(T.surftxt);
}

void affichertxt(text T, SDL_Surface * screen, char *ch)
{
	T.surftxt=TTF_RenderText_Blended(T.font, ch, T.color);
	SDL_BlitSurface(T.surftxt, NULL, screen, &T.pos);
}
