#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fct.h"
#include "fctBG.h"
#include "enigme.h"
#include "fonctionperso.h"
#include "minimap.h"
#include "enemi.h"
#include "enigmeImg.h"
#include "blanc.h"

int arduinoWriteData(int x)
{
    char chemin[]="/dev/ttyUSB0";
    FILE*f;

    f=fopen(chemin,"w");
    if(f == NULL)
        return(-1);

    fprintf(f,"%d",x);
    fclose(f);

    return(0);
}

int arduinoReadData(int *x)
{
    char chemin[]="/dev/ttyUSB0";
    FILE*f;
    char c;
    f=fopen(chemin,"r");

    if(f == NULL)
        return(-1);

    fscanf(f,"%d",x);

    fclose(f);

    return(0);
}

int main(int argc, char** argv)
{
    TTF_Init();
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512))
    {
        printf("%s", Mix_GetError());
    }
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    SDL_Surface *screen;
    pic BG, BG2, str1, sett1, cred1, qt1, str2, sett2, cred2, qt2, settBG, sound2, sound1, arr1, arr2, X1, X2, plus1, plus2, mins1, mins2, on, off, on2, off2, res, res1, res2;
    pic qtBG, YES, YES2, NO, NO2, cred, Menu_anime[118];
    int done=0, P=0, P2=0, choice=0, choice2=-1, choice3=-1, exit, O=0, volM, volS, NSFX=0, fulls=1, x, receive=-1, U_D2=0, U_D1=0, a, posmax;
    float i=0;
    char nbBG[20];
    SDL_Event event, event2, event3;
    text txt, txt1, txt2, txt3, txt4, qttxt;
    Mix_Music *music;
    Mix_Chunk * eff;
    atexit(SDL_Quit);

    screen=SDL_SetVideoMode(1914, 878, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
    if(!screen)
    {
        printf("unable to open a 1914x878 wind %s\n", SDL_GetError());
        return 1;
    }

    music=Mix_LoadMUS("scarymusic.mp3");
    eff=Mix_LoadWAV("menu/click.wav");

    initImg(&BG, "menu/BG2.png", 0, 0);
    initImg(&BG2, "menu/nBG.png", 0, 0);
    initImg(&str1, "menu/start1.png", 100, 470);
    initImg(&str2, "menu/start2.png", 100, 470);
    initImg(&sett1, "menu/settings1.png", 100, 620);
    initImg(&sett2, "menu/settings2.png", 100, 620);
    initImg(&cred1, "menu/credits1.png", 1200, 470);
    initImg(&cred2, "menu/credits2.png", 1200, 470);
    initImg(&qt1, "menu/quit1.png", 1200, 620);
    initImg(&qt2, "menu/quit2.png", 1200, 620);
    initImg(&settBG, "menu/SettBG.png", 689, 100);
    initImg(&X1, "menu/X.png", 1135, 180);
    initImg(&X2, "menu/X2.png", 1135, 180);
    initImg(&arr1, "menu/arrow1.png", 735, 180);
    initImg(&arr2, "menu/arrow2.png", 735, 180);
    initImg(&sound1, "menu/sound1.png", 809, 360);
    initImg(&sound2, "menu/sound2.png", 809, 360);
    initImg(&plus1, "menu/+.png", 1130, 378);
    initImg(&plus2, "menu/+2.png", 1130, 378);
    initImg(&mins1, "menu/-.png", 730, 378);
    initImg(&mins2, "menu/-2.png", 730, 378);
    initImg(&on, "menu/on.png", 833, 480);
    initImg(&off, "menu/off.png", 833, 450);
    initImg(&on2, "menu/on.png", 1100, 480);
    initImg(&off2, "menu/off.png", 1100, 480);
    initImg(&res, "menu/res.png", 881, 625);
    initImg(&res1, "menu/resF.png", 881, 625);
    initImg(&res2, "menu/resXF.png", 881, 625);
    initImg(&qtBG, "menu/qt conf.png", 450, 350);
    initImg(&YES, "menu/YES.png", 810, 465);
    initImg(&YES2, "menu/YES2.png", 810, 465);
    initImg(&NO, "menu/NO.png", 1008, 465);
    initImg(&NO2, "menu/NO2.png", 1008, 465);
    initImg(&cred, "menu/credits.png", 720, 270);
    for (x=0; x<49; x++)
    {
        sprintf(nbBG, "taille/BG2_%d.png", x+1);
        initImg(&Menu_anime[x], nbBG, 0, 0);
    }

    initTitle(&txt, 650, 90, 80, "menu/Bleeding_Cowboys.ttf");
    initText(&qttxt, 660, 375, 40, "menu/MedusaGothic D.otf");
    initText(&txt1, 720, 270, 50, "menu/MedusaGothic D.otf");
    initText(&txt2, 1020, 475, 32, "menu/MedusaGothic D.otf");
    initText(&txt3, 760, 535, 50, "menu/MedusaGothic D.otf");

    Mix_PlayMusic(music, -1);
    volM=Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    volM=MIX_MAX_VOLUME/2;
    volS=Mix_Volume(-1, volM);
    sound2.pos_img.w=150;
//BG
    SDL_Rect pos, pos2;
    SDL_Event event4;
    int lvl=0, collision, collision2;
    Background Bg[3];
    Uint8 *keystates;

    initBack(Bg);

//perso
    int dt=0;

    SDL_WM_SetCaption("game", NULL);

    Personne p;
    Personne p2;
    initPerso(&p);
    initPerso2(&p2);
    SDL_EnableKeyRepeat(200, 0);

    // enigme

    SDL_Surface *porte[14];

    SDL_Rect port ;
    Enigme e;
    int boucle=1;
    int scene=1;

    //Init_Enigme(&e, "enigme/questions.txt", "enigme/reponses.txt" , "enigme/vraireponses.txt");
    int Game;

//mininap
    char nom[30]="\0";
    int distance=100, j,y=1;  //continuer=0; //exit variable de la boucle du jeux et continuer la variable de la boucle saisie du nom joueur
    int score=0;
    int xo ;
    grille gril;
    int temps=120;
    int frame=0; //pour savoir frame par seconde  fps
    Uint32 start; //pour fps
    const int FPS=20; //fixation fps en 20
    char sh[70]="score.txt";
    minimap m;
    Personne pMprochaine ;
    SDL_Rect posb;
    SDL_Surface *b;
    SDL_Surface *imageFond = NULL, *masked = NULL, *chiffres[30];
    SDL_Rect posBG, poschiffres, poscamera;
    int redimonsionnement = 30;

    posBG.x=0;
    posBG.y=0;
    imageFond = IMG_Load("lvl1.png");//image kbira il principal
    //initialisation du minimap
    initminimap(&m);
    InitGrille (&gril);
    masked = IMG_Load("map1_masked.png");
    //position prochaine du personnage principale
    pMprochaine.position.x = p.position.x;
    pMprochaine.position.y = p.position.y;
    b = IMG_Load("rouge.png");
    posb.x = 700;
    posb.y = 570;

//enemy
    enemie enmy;
    initenemie (&enmy);

//enigmeimg
    enigme en;
    Pic mat[3][4];
    char nomfichier[20];
    int g;

    init_Img(&mat[0][0], "Q10.png", 600, 50);
    init_Img(&mat[0][1], "Q11.png", 600, 50);
    init_Img(&mat[0][2], "Q12.png", 600, 50);
    init_Img(&mat[0][3], "Q13.png", 600, 50);
    init_Img(&mat[1][0], "Q20.png", 600, 50);
    init_Img(&mat[1][1], "Q21.png", 600, 50);
    init_Img(&mat[1][2], "Q22.png", 600, 50);
    init_Img(&mat[1][3], "Q23.png", 600, 50);
    init_Img(&mat[2][0], "Q30.png", 600, 50);
    init_Img(&mat[2][1], "Q31.png", 600, 50);
    init_Img(&mat[2][2], "Q32.png", 600, 50);
    init_Img(&mat[2][3], "Q33.png", 600, 50);


    g=init_Enigme(&en,nomfichier)-1;
    
    FILE* f;
  SDL_Rect pos3 ,pos1;
  SDL_Color noir = {0,0,0};
  SDL_Surface *surftxt;
  SDL_Surface *surfmeil;
  TTF_Font *font;
  char nomjoueur[10],copie[30] ; 
  int scoree = 0;
  pos3.x = 0;
  pos3.y = 0;
  pos1.x = 300;
  pos1.y = 0;
  font = TTF_OpenFont ("Urusans.TTF",50);
  f=fopen("score.txt", "r");
  fscanf(f,"%s %d",nomjoueur,&scoree); 
  fclose(f);
  sprintf(copie,"%s %d",nomjoueur,scoree);

    while(!done)
    {
        SDL_Flip(screen);
        if(choice!=1)
        {
            if(x>48)
                i=0;
            i+=0.1;
            x=i;
            SDL_PollEvent(&event);
            afficher_img(Menu_anime[x], screen);
            if(choice==0)
            {
					  surftxt = TTF_RenderText_Blended(font,"meilleur score : ",noir);
					  surfmeil = TTF_RenderText_Blended(font,copie,noir);
					  SDL_BlitSurface(surftxt,NULL,screen,&pos);
					  SDL_BlitSurface(surfmeil,NULL,screen,&pos1);
                if(P==0)
                    afficher_img(str2, screen);
                else
                    afficher_img(str1, screen);
                if(P==1)
                    afficher_img(sett2, screen);
                else
                    afficher_img(sett1, screen);
                if(P==2)
                    afficher_img(cred2, screen);
                else
                    afficher_img(cred1, screen);
                if(P==3)
                    afficher_img(qt2, screen);
                else
                    afficher_img(qt1, screen);

                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_DOWN:
                        if(P==0)
                            P=1;
                        else if(P==1)
                        {
                            P=2;
                        }
                        else if(P==2)
                        {
                            P=3;
                        }
                        else if(P==3)
                        {
                            P=0;
                        }
                        Mix_PlayChannel(-1, eff, 0);
                        SDL_Delay(200);
                        break;
                    case SDLK_UP:
                        if(P==0)
                        {
                            P=3;
                        }
                        else if(P==1)
                        {
                            P=0;
                        }
                        else if(P==2)
                        {
                            P=1;
                        }
                        else if(P==3)
                        {
                            P=2;
                        }
                        Mix_PlayChannel(-1, eff, 0);
                        SDL_Delay(200);
                        break;
                    case SDLK_ESCAPE:
                        choice=4;
                        break;
                    case SDLK_RETURN:
                        if(P==0)
                            choice=1;
                        if(P==1)
                            choice=2;
                        if(P==2)
                            choice=3;
                        if(P==3)
                            choice=4;
                        break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if(event.motion.x>=100 && event.motion.x<=100+str1.pos_img.w && event.motion.y>=470 && event.motion.y<=470+str1.pos_img.h)
                    {
                        if(P!=0)
                            Mix_PlayChannel(-1, eff, 0);
                        P=0;
                    }
                    else if(event.motion.x>=100 && event.motion.x<=100+sett1.pos_img.w && event.motion.y>=620 && event.motion.y<=620+sett1.pos_img.h)
                    {
                        if(P!=1)
                            Mix_PlayChannel(-1, eff, 0);
                        P=1;
                    }
                    else if(event.motion.x>=1200 && event.motion.x<=1200+cred1.pos_img.w && event.motion.y>=470 && event.motion.y<=470+cred1.pos_img.h)
                    {
                        if(P!=2)
                            Mix_PlayChannel(-1, eff, 0);
                        P=2;
                    }
                    else if(event.motion.x>=1200 && event.motion.x<=1200+qt1.pos_img.w && event.motion.y>=620 && event.motion.y<=620+qt1.pos_img.h)
                    {
                        if(P!=3)
                            Mix_PlayChannel(-1, eff, 0);
                        P=3;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN :
                    if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=100 && event.button.x<=100+str1.pos_img.w && event.button.y>=470 && event.button.y<=470+str1.pos_img.h)
                    {
                        choice=1;
                    }
                    else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=100 && event.button.x<=100+sett1.pos_img.w && event.button.y>=620 && event.button.y<=620+sett1.pos_img.h)
                    {
                        choice=2;
                    }
                    else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=1200 && event.button.x<=1200+cred1.pos_img.w && event.button.y>=470 && event.button.y<=470+cred1.pos_img.h)
                    {
                        choice=3;
                    }
                    else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=1200 && event.button.x<=1200+qt1.pos_img.w && event.button.y>=620 && event.button.y<=620+qt1.pos_img.h)
                    {
                        choice=4;
                    }
                    break;

                case SDL_QUIT:
                    done=1;
                    break;
                }
            }
            if(choice==2)
            {
                afficher_img(settBG, screen);
                affichertxt(txt1, screen, "Sound:");
                afficher_img(sound1, screen);
                afficher_img(sound2, screen);
                affichertxt(txt2, screen, "SFX");
                affichertxt(txt3, screen, "Resolution:");
                if(NSFX==0)
                    afficher_img(on2, screen);
                else
                    afficher_img(off2, screen);
                if(O==1)
                    afficher_img(arr2, screen);
                else
                    afficher_img(arr1, screen);
                if(O==2)
                    afficher_img(plus2, screen);
                else
                    afficher_img(plus1, screen);
                if(O==3)
                    afficher_img(mins2, screen);
                else
                    afficher_img(mins1, screen);
                if(O==4)
                {
                    if(fulls==1)
                        afficher_img(res2, screen);
                    else
                        afficher_img(res1, screen);
                }
                else
                    afficher_img(res, screen);
                SDL_PollEvent(&event2);
                switch(event2.type)
                {
                case SDL_KEYDOWN:
                    switch(event2.key.keysym.sym)
                    {
                    case SDLK_BACKSPACE:
                        choice2=1;
                        break;

                    case SDLK_KP_PLUS:
                        choice2=2;
                        break;

                    case SDLK_KP_MINUS:
                        choice2=3;
                        break;

                    case SDLK_s:
                        choice2=4;
                        break;

                    case SDLK_f:
                        choice2=5;
                        break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if(event2.motion.x>=735 && event2.motion.x<=735+arr1.pos_img.w && event2.motion.y>=180 && event2.motion.y<=180+arr1.pos_img.h)
                    {
                        if(O!=1 && NSFX==0)
                        {
                            Mix_PlayChannel(-1, eff, 0);
                            O=1;
                        }
                    }
                    else if(event2.motion.x>=1130 && event2.motion.x<=1130+plus1.pos_img.w && event2.motion.y>=378 && event2.motion.y<=378+plus1.pos_img.h)
                    {
                        if(O!=2 && NSFX==0)
                        {
                            Mix_PlayChannel(-1, eff, 0);
                            O=2;
                        }
                    }
                    else if(event2.motion.x>=730 && event2.motion.x<=730+mins1.pos_img.w && event2.motion.y>=378 && event2.motion.y<=378+mins1.pos_img.h)
                    {
                        if(O!=3 && NSFX==0)
                        {
                            Mix_PlayChannel(-1, eff, 0);
                            O=3;
                        }
                    }
                    else if(event2.motion.x>=881 && event2.motion.x<=881+res.pos_img.w && event2.motion.y>=625 && event2.motion.y<=625+res.pos_img.h)
                        O=4;
                    else
                        O=0;
                    break;

                case SDL_MOUSEBUTTONDOWN :
                    if(event2.button.button==SDL_BUTTON_LEFT && event2.motion.x>=735 && event2.motion.x<=735+arr1.pos_img.w && event2.motion.y>=180 && event2.motion.y<=180+arr1.pos_img.h)
                    {
                        choice2=1;
                    }
                    else if(event2.button.button==SDL_BUTTON_LEFT && event2.motion.x>=1130 && event2.motion.x<=1130+plus1.pos_img.w && event2.motion.y>=378 && event2.motion.y<=378+plus1.pos_img.h)
                    {
                        choice2=2;
                    }
                    else if(event2.button.button==SDL_BUTTON_LEFT && event2.motion.x>=730 && event2.motion.x<=730+mins1.pos_img.w && event2.motion.y>=378 && event2.motion.y<=378+mins1.pos_img.h)
                    {
                        choice2=3;
                    }
                    else if(event2.button.button==SDL_BUTTON_LEFT && event2.button.x>=1100 && event2.button.x<=1100+on2.pos_img.w && event2.button.y>=480 && event2.button.y<=480+off2.pos_img.h)
                    {
                        choice2=4;
                    }
                    else if(event2.button.button==SDL_BUTTON_LEFT && event2.motion.x>=881 && event2.motion.x<=881+res.pos_img.w && event2.motion.y>=625 && event2.motion.y<=625+res.pos_img.h)
                    {
                        choice2=5;
                    }
                    else
                        choice2=-1;
                    break;

                case SDL_QUIT:
                    done=1;
                    break;
                }
                switch(choice2)
                {
                case 1:
                    choice=0;
                    choice2=-1;
                    SDL_Delay(500);
                    break;

                case 2:
                    if(volM!=MIX_MAX_VOLUME)
                    {
                        if(volM==0)
                        {
                            sound2.pos_img.w=75;
                        }
                        else if(volM==MIX_MAX_VOLUME/4)
                        {
                            sound2.pos_img.w=150;
                        }
                        else if(volM==MIX_MAX_VOLUME/2)
                        {
                            sound2.pos_img.w=225;
                        }
                        else if(volM==MIX_MAX_VOLUME*3/4)
                        {
                            sound2.pos_img.w=300;
                        }
                        volM=Mix_VolumeMusic(volM+MIX_MAX_VOLUME/4);
                        volM=Mix_VolumeMusic(-1);
                        if(NSFX==0)
                            volS=Mix_Volume(-1, volM);
                    }
                    else
                    {
                        sound2.pos_img.w=300;
                    }
                    choice2=-1;
                    SDL_Delay(500);
                    break;

                case 3:
                    if(volM!=0)
                    {
                        if(volM==MIX_MAX_VOLUME)
                        {
                            sound2.pos_img.w=225;
                        }
                        else if(volM==MIX_MAX_VOLUME*3/4)
                        {
                            sound2.pos_img.w=150;
                        }
                        else if(volM==MIX_MAX_VOLUME/2)
                        {
                            sound2.pos_img.w=75;
                        }
                        else if(volM==MIX_MAX_VOLUME/4)
                        {
                            sound2.pos_img.w=0;
                        }
                        volM=Mix_VolumeMusic(volM-MIX_MAX_VOLUME/4);
                        volM=Mix_VolumeMusic(-1);
                        if(NSFX==0)
                            volS=Mix_Volume(-1, volM);
                    }
                    choice2=-1;
                    SDL_Delay(500);
                    break;

                case 4:
                    if(NSFX!=1)
                    {
                        volS=Mix_Volume(-1, 0);
                        NSFX=1;
                    }
                    else
                    {
                        NSFX=0;
                        if(volM!=0)
                            volS=Mix_Volume(-1, volM);
                        else
                            volS=Mix_Volume(-1, MIX_MAX_VOLUME/2);
                    }
                    choice2=-1;
                    SDL_Delay(500);
                    break;

                case 5:
                    if(fulls==0)
                    {
                        screen=SDL_SetVideoMode(1914, 878, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
                        fulls=1;
                    }
                    else
                    {
                        screen=SDL_SetVideoMode(1914, 878, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
                        fulls=0;
                    }
                    choice2=-1;
                    SDL_Delay(500);
                    break;

                }
            }
            if(choice==3)
            {
                afficher_img(settBG, screen);
                afficher_img(cred, screen);
                if(O==0)
                    afficher_img(arr2, screen);
                else
                    afficher_img(arr1, screen);
                SDL_PollEvent(&event3);
                if(event3.type==SDL_KEYDOWN)
                {
                    if(event3.key.keysym.sym==SDLK_BACKSPACE)
                    {
                        choice=0;
                        choice3=-1;
                        SDL_Delay(500);
                    }
                    else if(event3.key.keysym.sym==SDL_QUIT)
                    {
                        done=1;
                    }
                }
                else if(event3.type==SDL_MOUSEMOTION && event3.button.button==SDL_BUTTON_LEFT && event3.motion.x>=735 && event3.motion.x<=735+arr1.pos_img.w && event3.motion.y>=180 && event3.motion.y<=180+arr1.pos_img.h)
                {
                    O=0;
                }
                else if(event3.type==SDL_MOUSEMOTION && event3.button.button==SDL_BUTTON_LEFT && event3.motion.x<735 && event3.motion.x>735+arr1.pos_img.w && event3.motion.y<180 && event3.motion.y>180+arr1.pos_img.h)
                {
                    O=-1;
                }
                else if(event3.type==SDL_MOUSEBUTTONDOWN && event3.button.button==SDL_BUTTON_LEFT && event3.motion.x>=735 && event3.motion.x<=735+arr1.pos_img.w && event3.motion.y>=180 && event3.motion.y<=180+arr1.pos_img.h)
                {
                    choice=0;
                    choice3=-1;
                    SDL_Delay(500);
                }
            }
            if(choice==4)
            {
                afficher_img(qtBG, screen);
                affichertxt(qttxt, screen, "Do you want to quit?");
                if(P2==0)
                    afficher_img(YES2, screen);
                else
                    afficher_img(YES, screen);
                if(P2==1)
                    afficher_img(NO2, screen);
                else
                    afficher_img(NO, screen);
                SDL_PollEvent(&event3);
                switch(event3.type)
                {
                case SDL_KEYDOWN:
                    switch(event3.key.keysym.sym)
                    {
                    case SDLK_LEFT:
                        P2=0;
                        break;

                    case SDLK_RIGHT:
                        P2=1;
                        break;

                    case SDLK_RETURN:
                        if(P2==0)
                        {
                            choice3=1;
                        }
                        else
                        {
                            choice3=2;
                        }
                        break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if(event3.motion.x>=1008 && event3.motion.x<=1008+NO.pos_img.w && event3.motion.y>=465 && event3.motion.y<=465+NO.pos_img.h)
                    {
                        if(P2!=1 && NSFX==0)
                            Mix_PlayChannel(-1, eff, 0);
                        P2=1;
                    }
                    else if(event3.motion.x>=810 && event3.motion.x<=810+YES.pos_img.w && event3.motion.y>=465 && event3.motion.y<=465+YES.pos_img.h)
                    {
                        if(P2!=0 && NSFX==0)
                            Mix_PlayChannel(-1, eff, 0);
                        P2=0;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event3.button.button==SDL_BUTTON_LEFT && event3.motion.x>=810 && event3.motion.x<=810+YES.pos_img.w && event3.motion.y>=465 && event3.motion.y<=465+YES.pos_img.h)
                        choice3=1;
                    else if(event3.button.button==SDL_BUTTON_LEFT && event3.motion.x>=1008 && event3.motion.x<=1008+NO.pos_img.w && event3.motion.y>=465 && event3.motion.y<=465+NO.pos_img.h)
                        choice3=2;
                    break;
                }
                if(choice3==1)
                {
                    done=1;
                    choice=-1;
                    choice3=-1;
                }
                else if(choice3==2)
                {
                    choice=0;
                    choice3=-1;
                    SDL_Delay(500);
                }
            }
        }
        else
        {
            if(entrernom(screen,nom,&y, &Bg[lvl])) ;
            if(y==1)
            {
                Mix_FadeOutMusic(1000);
                exit=0;
                while(!exit)
                {
                    start = SDL_GetTicks();
                    if(Bg[lvl].multi_J==1)
                    {
                        Bg[lvl].camera.w=957;
                        a=4;
                    }
                    else
                    {
                        Bg[lvl].camera.w=1914;
                        a=2;
                    }
                    afficherBack(Bg[lvl], screen);
                    SDL_Flip(screen);
                    if (pos.x == 1250 || pos2.x==1250)
                    {
                        p.posvie2.x = 250 ;
                    }
                    if (p.posvie2.x > 200)
                    {
                        jeux (&gril,&xo) ;

                        if (xo == 1)
                        {
                            p.posvie2.x = 146;
                        }
                        else
                        {
                            exit = 1;
                            choice=0;
                            p.posvie2.x=0;
                        }
                    }
                    //afficher_enemie (enmy,Bg[lvl].anim[Bg[lvl].nb_anim]);
                    afficher_enemie(enmy,screen);
                    afficherminimap(m,screen);
                    pos.x=Bg[lvl].camera.x+p.position.x;
                    pos.y=Bg[lvl].camera.y+p.position.y;
                    pos2.x=Bg[lvl].camera2.x+p2.position.x-957;
                    pos2.y=Bg[lvl].camera2.y+p2.position.y;
                    collision=collisionPP( pos, Bg[lvl].mask[0]);
                    collision2=collisionPP( pos2, Bg[lvl].mask[0]);
                    printf("%d", pos2.x);
                    if(pos.x<1115 || pos.x>1185)
                        U_D1=0;
                    if(pos2.x<1115 || pos2.x>1185)
                        U_D2=0;
                    if(collisionGND( pos, Bg[lvl].mask[0])!=1 && pos.x>screen->w/2 && U_D1==0)
                        Bg[lvl].camera.y+=5;
                    if(collisionGND( pos2, Bg[lvl].mask[0])!=1 && pos2.x>screen->w*3/4 && U_D2==0)
                        Bg[lvl].camera2.y+=5;
                    if (Bg[lvl].multi_J==0)
                    {
                        afficherPerso (p,screen);
                        saut(&p);
		                  if(pos.x>=Bg[lvl].anim[0]->w)
		                  {
		                 		 	lvl++;
		                 		 	p.position.x=0;
		                 		 	p.position.y=500;
		                 	}
                    }

                    if(Bg[lvl].multi_J==1)
                    {
                        afficherPerso (p,screen);
                        afficherPerso (p2,screen);
                        saut(&p);
                        saut(&p2);
		                  if(pos.x>=Bg[lvl].anim[0]->w && pos2.x>=Bg[lvl].anim[0]->w)
		                 		 lvl++;

                    }
                    animate_Enemy(&enmy);
                    move_enemy(&enmy);
                    deplacerIA(&enmy,p);
                    if(collision_E(enmy,p)==1)
                    {
                        printf("collison = 1 \n ");
                        //score-=1;
                    }
                    SDL_PollEvent(&event);
                    //affichertemps ( temps,screen);
                    afficherscore (screen,&score);
                    arduinoReadData(&receive);
                    printf("%d", receive);
                    switch(receive)
                    {
                    case 0:
                        p.direction=1;
                        if(pos.x <= screen->w/2 || Bg[lvl].camera.x+screen->w == Bg[lvl].anim[0]->w)
                        {
                            dt=1;
                            deplacerPerso(&p,screen,dt);
                        }
                        else
                        {
                            arduinoWriteData(collision);
                            scrolling (&Bg[lvl].camera, 0, collision);
                            animerPerso(&p);
                        }
                        pMprochaine.position.x += distance;
                        if (collisionPPP(pMprochaine, masked)==0)
                            majminimap(&p,&m,Bg[lvl].camera,redimonsionnement);
                        break;
                    case 1:
                        p.direction=2;
                        if (Bg[lvl].camera.x == 0 || pos.x >= Bg[lvl].anim[0]->w-(screen->w/2))
                        {
                            dt=2;
                            deplacerPerso(&p,screen,dt);
                        }
                        else
                        {
                            arduinoWriteData(collision);
                            scrolling (&Bg[lvl].camera, 1, collision);
                            animerPerso(&p);
                        }
                        pMprochaine.position.x -= distance;
                        if (collisionPPP(pMprochaine, masked)==0)
                            majminimap(&p,&m,Bg[lvl].camera,redimonsionnement);

                        break;
                    case 2:
                        if (pos.x <= screen->w/a || Bg[lvl].camera.x+Bg[lvl].camera.w == Bg[lvl].anim[0]->w)
                        {
                            dt=4;
                            deplacerPerso(&p,screen,dt);
                            saut(&p);
                        }
                        else
                        {
                            while(Bg[lvl].camera.y>(-30))
                            {
                                collision=collisionPP( pos, Bg[lvl].mask[0]);
                                scrolling (&(Bg[lvl].camera), 2, collision);
                                SDL_Flip(screen);
                                afficherBack(Bg[lvl], screen);
                                afficherPerso (p,screen);
                                if(Bg[lvl].multi_J==1)
                                    afficherPerso (p2,screen);
                                SDL_PollEvent(&event4);

                                switch(event4.type)
                                {
                                case SDL_KEYDOWN:
                                    switch(event4.key.keysym.sym)
                                    {
                                    case SDLK_d:
                                        scrolling (&(Bg[lvl].camera), 0, collision);
                                        break;

                                    case SDLK_q:
                                        scrolling (&(Bg[lvl].camera), 1, collision);
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    switch(event.type)
                    {
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                        case SDLK_w:
                            dt=0;
                            deplacerPerso(&p,screen,dt);
                            break;

                        case SDLK_x:
                            augmenter_vitesse(&p);
                            break;

                        case SDLK_c:
                            diminuer_vitesse(&p);
                            break;

                        case SDLK_ESCAPE:
                            exit=1;
                            choice=0;
                            sauvegarder(score,nom,sh);
                            Mix_FadeInMusic(music,-1,1000);
                            SDL_Delay(200);
                            break;
                        }
                        break;

                    case SDL_QUIT:
                        exit=1;
                        done=1;
                        sauvegarder(score,nom,sh);
                        SDL_Delay(200);
                        break;
                    }

                    keystates = SDL_GetKeyState( NULL );
                    if( keystates[ SDLK_d ] && collision!=1)
                    {
                        p.direction=1;
                        if(pos.x <= screen->w/a || pos.x>= Bg[lvl].anim[0]->w-(screen->w/2))//Bg[lvl].camera.x+Bg[lvl].camera.w == Bg[lvl].anim[0]->w)
                        {
                            dt=1;
                            deplacerPerso(&p,screen,dt);
                        }
                        else
                        {
                            scrolling (&Bg[lvl].camera, 0, collision);
                            animerPerso(&p);
                        }
                        pMprochaine.position.x += distance;
                        if (collisionPPP(pMprochaine, masked)==0)
                            majminimap(&p,&m,Bg[lvl].camera,redimonsionnement);
                    }
                    if( keystates[ SDLK_q ] && p.position.x>0 && collision!=2)
                    {
                        p.direction=2;
                        if (Bg[lvl].camera.x <= 0 || pos.x >= Bg[lvl].anim[0]->w-(screen->w/a))
                        {
                            dt=2;
                            deplacerPerso(&p,screen,dt);
                        }
                        else
                        {
                            scrolling (&Bg[lvl].camera, 1, collision);
                            animerPerso(&p);
                        }
                        pMprochaine.position.x -= distance;
                        if (collisionPPP(pMprochaine, masked)==0)
                            majminimap(&p,&m,Bg[lvl].camera,redimonsionnement);
                    }
                    if( keystates[ SDLK_z ] && pos.x>=1115 && pos.x<=1185)
                    {
                        U_D1=1;
                        scrolling (&(Bg[lvl].camera), 2, collision);
                    }
                    if( keystates[ SDLK_s ] && pos.x>=1115 && pos.x<=1185)
                    {
                        U_D1=1;
                        scrolling (&(Bg[lvl].camera), 3, collision);
                    }
                    if( keystates[ SDLK_SPACE ] && collisionGND( pos, Bg[lvl].mask[0])==1)
                    {
                        if (pos.x <= screen->w/a || Bg[lvl].camera.x+Bg[lvl].camera.w == Bg[lvl].anim[0]->w)
                        {
                            dt=4;
                            deplacerPerso(&p,screen,dt);
                            saut(&p);
                        }
                        else
                        {
                            posmax=Bg[lvl].camera.y;
                            while(Bg[lvl].camera.y>posmax-200)
                            {
                                collision=collisionPP( pos, Bg[lvl].mask[0]);
                                scrolling (&(Bg[lvl].camera), 2, collision);
                                SDL_Flip(screen);
                                afficherBack(Bg[lvl], screen);
                                afficherPerso (p,screen);
                                if(Bg[lvl].multi_J==1)
                                    afficherPerso (p2,screen);
                                SDL_PollEvent(&event4);

                                switch(event4.type)
                                {
                                case SDL_KEYDOWN:
                                    switch(event4.key.keysym.sym)
                                    {
                                    case SDLK_d:
                                    	 collision=collisionPP( pos, Bg[lvl].mask[0]);
                                    	 if(collision!=1)
	                                        scrolling (&(Bg[lvl].camera), 0, collision);
                                        break;

                                    case SDLK_q:
                                    	 collision=collisionPP( pos, Bg[lvl].mask[0]);
                                    	 if(collision!=2)
	                                        scrolling (&(Bg[lvl].camera), 1, collision);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if(Bg[lvl].multi_J==1)
                    {
                        if( keystates[ SDLK_RIGHT ] && p2.position.x<screen->w)
                        {
                            p2.direction=1;
                            if(pos2.x <= screen->w/4 || Bg[lvl].camera2.x+Bg[lvl].camera.w == Bg[lvl].anim[0]->w)
                            {
                                dt=1;
                                deplacerPerso(&p2,screen,dt);
                            }
                            else
                            {
                                scrolling (&Bg[lvl].camera2, 0, collision2);
                                animerPerso(&p2);
                            }
                        }
                        if( keystates[ SDLK_LEFT ] && p2.position.x>screen->w/2)
                        {
                            p2.direction=2;
                            if (Bg[lvl].camera2.x == 0 || pos2.x >= Bg[lvl].anim[0]->w-(screen->w/4))
                            {
                                dt=2;
                                deplacerPerso(&p2,screen,dt);
                            }
                            else
                            {
                                scrolling (&Bg[lvl].camera2, 1, collision2);
                                animerPerso(&p2);
                            }
                        }
                        if( keystates[ SDLK_UP ] && pos2.x>=1115 && pos2.x<=1185)
                        {
                            U_D2=1;
                            scrolling (&(Bg[lvl].camera2), 2, collision2);
                        }
                        if( keystates[ SDLK_DOWN ] && pos2.x>=1115 && pos2.x<=1185)
                        {
                            U_D2=1;
                            scrolling (&(Bg[lvl].camera2), 3, collision2);
                        }
                        if( keystates[ SDLK_RSHIFT ] && collisionGND( pos2, Bg[lvl].mask[0])==1)
                        {
                            if ( (pos2.x>Bg[lvl].anim[0]->w-(screen->w/2)) || (pos2.x<screen->w/2))
                            {
                                dt=4;
                                deplacerPerso(&p2,screen,dt);
                                saut(&p2);
                            }
                            else
                            {
                                posmax=Bg[lvl].camera2.y;
                                while(Bg[lvl].camera2.y>posmax-200)
                                {
                                    collision2=collisionPP( pos2, Bg[lvl].mask[0]);
                                    scrolling (&(Bg[lvl].camera2), 2, collision2);
                                    SDL_Flip(screen);
                                    afficherBack(Bg[lvl], screen);
                                    afficherPerso (p,screen);
                                    afficherPerso (p2,screen);
                                    SDL_PollEvent(&event);

                                    switch(event.type)
                                    {
                                    case SDL_KEYDOWN:
                                        switch(event.key.keysym.sym)
                                        {
                                        case SDLK_RIGHT:
                                            collision2=collisionPP( pos2, Bg[lvl].mask[0]);
                                            scrolling (&(Bg[lvl].camera2), 0, collision2);
                                            break;

                                        case SDLK_LEFT:
                                            collision2=collisionPP( pos2, Bg[lvl].mask[0]);
                                            scrolling (&(Bg[lvl].camera2), 1, collision2);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    switch(lvl)
                    {
                    case 0:
                        if(((pos.x==2800 && pos.y<600) || (pos2.x==2800 && pos2.y<600)) && boucle==1)
                        {

                            Init_Enigme(&e, "enigme/questions.txt", "enigme/reponses.txt", "enigme/vraireponses.txt");
                            while(boucle==1)
                            {
                                boucle=Play_Enigme(&e,screen,&Game);
                            }

                            if(Game)
                            {
                                printf("you win!!!");
                                animerEnigme(porte,&port,screen);
                                score += 10;
                            }
                            else if (!Game)
                            {
                                printf("you lost!!! %d ",Game);
                                animerEnigmee(porte,&port,screen);
                                if(score<=10)
                                	score=0;
                                else
                                	score-=10;
                            }
                            Mix_FadeOutMusic(1000);
                        }
                        if(pos.x==200 || pos2.x==200)
                        {
                            P=0;
                            while(!boucle)
                            {
                                SDL_Flip(screen);
                                affiche_Enigme(en, screen);
                                Enigme_animer(&en);
                                SDL_BlitSurface(en.anim[en.alea],NULL,screen,(&en.position_anim));
                                SDL_PollEvent(&event);

                                switch(event.type)

                                {
                                case SDL_QUIT:
                                {
                                    boucle=1;
                                }
                                break;

                                case SDL_KEYDOWN:
                                    switch(event.key.keysym.sym)
                                    {
                                    case SDLK_DOWN:
                                        if(P==0)
                                        {
                                            P=1;
                                            afficher_Img(mat[g][2], screen);
                                        }
                                        else if(P==1)
                                        {
                                            P=2;
                                            afficher_Img(mat[g][3], screen);
                                        }
                                        else if(P==2)
                                        {
                                            P=0;
                                            afficher_Img(mat[g][1], screen);
                                        }
                                        break;

                                    case SDLK_UP:
                                        if(P==0)
                                        {
                                            P=2;
                                            afficher_Img(mat[g][3], screen);
                                        }
                                        else if(P==1)
                                        {
                                            P=0;
                                            afficher_Img(mat[g][1], screen);
                                        }
                                        else if(P==2)
                                        {
                                            P=1;
                                            afficher_Img(mat[g][2], screen);
                                        }
                                        break;
                                    }
                                    break;


                                case SDL_MOUSEMOTION:
                                    if(event.motion.x>=650 && event.motion.x<=1300 && event.motion.y>=250 && event.motion.y<=400)
                                    {
                                        afficher_Img(mat[g][1], screen);
                                        P=0;
                                    }
                                    else if(event.motion.x>=650 && event.motion.x<=1300 && event.motion.y>=450 && event.motion.y<=550)
                                    {
                                        afficher_Img(mat[g][2], screen);
                                        P=1;
                                    }
                                    else if(event.motion.x>=650 && event.motion.x<=1300 && event.motion.y>=600 && event.motion.y<=750)
                                    {
                                        afficher_Img(mat[g][3], screen);
                                        P=2;
                                    }
                                    else
                                    {
                                        afficher_Img(mat[g][0], screen);
                                    }
                                    break;

                                }
                            }

                            SDL_FreeSurface(screen);
                        }
                        break;
                    }


                    SDL_Flip(screen);
                    if(frame==20)
                    {
                        if(temps>0)
                            temps--;
                        frame=0;
                    }
                    frame++;
                    if(1000/FPS>SDL_GetTicks()-start)
                        SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
                }
                //sauvegarder(score,nom,sh);

            }
            //Mix_FadeInMusic(music,-1,1000);
        }
    }
    for(i=0; i<49; i++)
        free_img(Menu_anime[x]);
    free_img(str1);
    free_img(str2);
    free_img(sett1);
    free_img(sett2);
    free_img(cred1);
    free_img(cred2);
    free_img(qt1);
    free_img(qt2);
    free_img(settBG);
    free_img(X1);
    free_img(X2);
    free_img(sound1);
    free_img(sound2);
    free_img(plus1);
    free_img(plus2);
    free_img(mins1);
    free_img(mins1);
    free_img(on);
    free_img(off);
    free_img(on2);
    free_img(off2);
    free_img(res);
    free_img(res1);
    free_img(res2);
    free_img(qtBG);
    free_img(YES);
    free_img(YES2);
    free_img(NO);
    free_img(NO2);
    free_img(cred);
    freetext(txt);
    freetext(txt1);
    freetext(txt2);
    freetext(txt3);
    freetext(txt4);
    freetext(qttxt);
    Mix_FreeMusic(music);
    Mix_FreeChunk(eff);
    free_memory(&e ) ;
//mini
    freeminimap(&m);
    SDL_FreeSurface(chiffres[1]);
    SDL_FreeSurface(chiffres[2]);
    SDL_FreeSurface(chiffres[3]);
    SDL_FreeSurface(chiffres[4]);
    SDL_FreeSurface(chiffres[5]);
    SDL_FreeSurface(chiffres[6]);
    SDL_FreeSurface(chiffres[7]);
    SDL_FreeSurface(chiffres[8]);
    SDL_FreeSurface(chiffres[9]);
    SDL_FreeSurface(chiffres[10]);
    SDL_FreeSurface(chiffres[11]);
    SDL_FreeSurface(chiffres[12]);
    SDL_FreeSurface(chiffres[13]);
    SDL_FreeSurface(screen);
    freeGrille(&gril);
    TTF_Quit();
    SDL_Quit();
//enemy
    SDL_FreeSurface(enmy.sprite);

    free_BG(Bg[lvl]);
    return 0;

}

