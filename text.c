#include "text.h"

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
