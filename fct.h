#ifndef PICTURE_H_
#define PICTURE_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


typedef struct
{
	SDL_Rect pos_scrn;
	SDL_Rect pos_img;
	SDL_Surface *img;
}pic;

typedef struct
{
	SDL_Rect pos;
	SDL_Color color;
	SDL_Surface *surftxt;
	TTF_Font *font;
	char* txt;
}text;

void initImg(pic *, char *, int, int);
void initBG(pic *, char *);
void free_img(pic);
void afficher_img(pic, SDL_Surface *);
void initText(text *T, int x, int y, int s, char* font);
void initTitle(text *T, int x, int y, int size, char* font);
void freetext(text T);
void affichertxt(text T, SDL_Surface * screen, char *ch);
#endif
