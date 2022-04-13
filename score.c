#include "score.h"

int initTextscore(Text* T)
{
    int s;
    T->couleurtext.r = 0;
    T->couleurtext.g = 0;
    T->couleurtext.b = 0;
    strcpy(T->txt,"SCORE: 000");
    T->positiontext.x = 1200;
    T->positiontext.y = 40;
    s=loadFontscore(T,"pol.ttf");
    T->textSurface=TTF_RenderText_Solid(T->police,T->txt,T->couleurtext);
    return s;
}
int loadFontscore(Text* T, char* path)
{


    if(TTF_Init() == -1)
    {
        printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        return -1;
    }
    T->police = TTF_OpenFont(path,60);
    if (T->police == NULL)
    {
        printf("Unable to load Font: %s\n", SDL_GetError());
        return (-1);
    }
    return (0);
}

void displayscore(Text T,SDL_Surface *screen)
{
    SDL_BlitSurface(T.textSurface,NULL,screen,&(T.positiontext));

}

void freeTextscore(Text T)
{
    TTF_CloseFont(T.police);
    TTF_Quit();
}


