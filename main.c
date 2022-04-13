#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonctionperso.h"

int main()
{
    int done=1,dt=0;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *screen;
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("unable to initialize SDL: %s\n",SDL_GetError());
        return 1;
    }
    screen=SDL_SetVideoMode(1920,1100,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    if(screen==NULL)
    {
        printf("unable to set video mode:%s\n",SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption("game", NULL);

    SDL_Surface *bg;
    SDL_Rect bg_pos;
    bg = IMG_Load("BG2.png");
    bg_pos.x = 0;
    bg_pos.y = 0;

    Personne p;
    initPerso(&p);
    SDL_EnableKeyRepeat(200, 0);
    while(done)
    {

        SDL_PollEvent(&event);

        switch(event.type)

        {
        case SDL_QUIT:
            done=0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_a:
                dt=0;
                deplacerPerso(&p,screen,dt);
                break;

            case
                    SDLK_RIGHT:
                dt=1;
                deplacerPerso(&p,screen,dt);
                break;

            case SDLK_LEFT:
                dt=2;
                deplacerPerso(&p,screen,dt);
                break;
            case SDLK_SPACE:
                dt=3;
                deplacerPerso(&p,screen,dt);
                saut(&p);


                break;

            case SDLK_UP:
                augmenter_vitesse(&p);
                break;

            case SDLK_DOWN:
                diminuer_vitesse(&p);
                break;

            case SDLK_ESCAPE:
                done=0;
                break;

            }

        }

        SDL_BlitSurface(bg,NULL,screen,&bg_pos);
        afficherPerso (p,screen);
        saut(&p);



        SDL_Flip(screen);
    }
    SDL_FreeSurface(bg);
    SDL_Quit();

    return 0;
}










