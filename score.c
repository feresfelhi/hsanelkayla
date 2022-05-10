#include "score.h"

int initscore(Text* T)
{
    int s;
    T->couleurtext.r = 0;
    T->couleurtext.g = 0;
    T->couleurtext.b = 0;
    strcpy(T->txt,"SCORE1: 000");
    T->positiontext.x = 1500;
    T->positiontext.y = 40;
    s=loadFontscore(T,"QUESTIONOFTIME.TTF");
    T->textSurface=TTF_RenderText_Solid(T->police,T->txt,T->couleurtext);
    return s;
}
int initscore2(Text* T)
{
    int s;
    T->couleurtext.r = 0;
    T->couleurtext.g = 0;
    T->couleurtext.b = 0;
    strcpy(T->txt,"SCORE2: 000");
    T->positiontext.x = 1300;
    T->positiontext.y = 40;
    s=loadFontscore(T,"QUESTIONOFTIME.TTF");
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
    T->police = TTF_OpenFont(path,30);
    if (T->police == NULL)
    {
        printf("Unable to load Font: %s\n", SDL_GetError());
        return (-1);
    }
    return (0);
}

void afficher_score(Text T,SDL_Surface *screen)
{
    SDL_BlitSurface(T.textSurface,NULL,screen,&(T.positiontext));

}

void freescore(Text T)
{
    TTF_CloseFont(T.police);
    TTF_Quit();
}


