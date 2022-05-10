#include "enigme.h"
void Init_Enigme(Enigme *e, char *f1 , char *f2 ,char *f3)
{
	e->background[0]=IMG_Load("enigme/fond2.jpg");
	e->background[1]=IMG_Load("enigme/enigmes.png");

	e->win=IMG_Load("enigme/youWin1.png");
   	e->lost=IMG_Load("enigme/gameOver.png");

        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);  
        Mix_Music *music ;
        music=Mix_LoadMUS("enigme/game1.mp3");
        Mix_PlayMusic(music,-1);
	for(int i=1;i<5;i++)
	{
		char str[30];
		sprintf(str,"%d.png",i);
		e->boutons[i]=IMG_Load(str);
	}

	srand(time(NULL));
	e->choix_question=rand()%4;

	while(e->choix_question==0){
		srand(time(NULL));
		e->choix_question=rand()%4;
	}

	SDL_Color couleurNoire={0,0,0};
	TTF_Font *police;
	TTF_Init();
	police = TTF_OpenFont("enigme/Candara.ttf", 16);

	char question[150];
	FILE *fichier;
    fichier=fopen(f1, "r");
    int i=1,boucle=1;
    if(fichier!=NULL)
    {
    	while(fgets((question),150,fichier)!=NULL && boucle==1)
    	{
    		if(e->choix_question==i)
    		{
    			e->question = TTF_RenderText_Blended (police,question,couleurNoire);
    			boucle=0;//en quit le boucle while
    		}
    		else{
    			i++;
    		}
    		
    	} 	
    	fclose(fichier);
    }
    

    FILE *fic;
    fic=fopen(f2, "r");
    int min,max;
    switch(e->choix_question)
    {
    	case 1:
    	{
    		min=1;
    		max=3;
    		break;
    	}
    	case 2:
    	{
    		min=4;
    		max=6;
    		break;
    	}
    	case 3:
    	{
    		min=7;
    		max=9;
    		break;
    	}
    }
    int j=1;
    if(fic!=NULL)
    {
    	char reponses[150];
    	while(fgets((reponses),15,fic)!=NULL && j<=max)
    	{	
    		if(j>min || j==min)
    		{
    			e->reponses[j-min+1]= TTF_RenderText_Blended (police,reponses,couleurNoire);
    			printf("%s\n",reponses);
    		}
    		j++;
    		
    	}
    	fclose(fic);
    }
    
    printf("%d\n",e->choix_question);

    FILE *f;
    f=fopen(f3, "r");
    char vraiReponse[150];
    int k=1,boucle1=1;
    if(f!=NULL)
    {
    	while(fgets((vraiReponse),15,f)!=NULL && boucle1==1)
    	{
    		if(e->choix_question==k)
    		{
    			e->reponses[4]= TTF_RenderText_Blended (police,vraiReponse,couleurNoire);
    			
    			boucle1=0;//en quit le boucle while
    		}
    		else{
    			k++;
    		}
    		
    	} 	
    	fclose(f);
    }
    

    
    e->posRepones[1].x=295.5;
	e->posRepones[1].y=274.5;
	e->posRepones[2].x=295.5;
	e->posRepones[2].y=317.5;
	e->posRepones[3].x=295.5;
	e->posRepones[3].y=364.5;
	e->posRepones[4].x=295.5;
	e->posRepones[4].y=408.5;

	e->posQuestion.x=262;
	e->posQuestion.y=192;

	e->image_courrante=1;


	srand(time(NULL));
	e->positionVraiReponse=rand()%5;

	while(e->positionVraiReponse==0){
		srand(time(NULL));
		e->positionVraiReponse=rand()%5;
	}

}


void Display_Enigme(Enigme *e,SDL_Surface *ecran)
{
	SDL_Rect position;
	position.x = (800/2)-(500/2);
	position.y = (600/2)-(300/2);
	SDL_BlitSurface(e->background[0],NULL,ecran,NULL);
	SDL_BlitSurface(e->background[1],NULL,ecran,&position);

	SDL_BlitSurface(e->boutons[e->image_courrante],NULL,ecran,&position);

	
	switch(e->positionVraiReponse)
	{
		case 1:
		{
			SDL_BlitSurface(e->reponses[1],NULL,ecran,&(e->posRepones[2]));
			SDL_BlitSurface(e->reponses[2],NULL,ecran,&(e->posRepones[3]));
			SDL_BlitSurface(e->reponses[3],NULL,ecran,&(e->posRepones[4]));
			break;
		}
		case 2:
		{
			SDL_BlitSurface(e->reponses[1],NULL,ecran,&(e->posRepones[1]));
			SDL_BlitSurface(e->reponses[2],NULL,ecran,&(e->posRepones[3]));
			SDL_BlitSurface(e->reponses[3],NULL,ecran,&(e->posRepones[4]));
			break;
		}
		case 3:
		{
			SDL_BlitSurface(e->reponses[1],NULL,ecran,&(e->posRepones[1]));
			SDL_BlitSurface(e->reponses[2],NULL,ecran,&(e->posRepones[2]));
			SDL_BlitSurface(e->reponses[3],NULL,ecran,&(e->posRepones[4]));
			break;
		}
		case 4:
		{
			SDL_BlitSurface(e->reponses[1],NULL,ecran,&(e->posRepones[1]));
			SDL_BlitSurface(e->reponses[2],NULL,ecran,&(e->posRepones[2]));
			SDL_BlitSurface(e->reponses[3],NULL,ecran,&(e->posRepones[3]));
			break;
		}
	}
	

	SDL_BlitSurface(e->reponses[4],NULL,ecran,&(e->posRepones[e->positionVraiReponse]));//la vrai reponse


	SDL_BlitSurface(e->question,NULL,ecran,&(e->posQuestion));
	SDL_Flip(ecran);
}

int Verify_Enigme(Enigme *e,int *Game,SDL_Surface *ecran)
{
      Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);  
     Mix_Chunk* button,*win1, *lose1; 
     win1=Mix_LoadWAV("enigme/win.wav");
     lose1=Mix_LoadWAV("enigme/fail.wav");
	SDL_Rect position={100,100};
	if(e->positionVraiReponse==e->image_courrante)
	{
		(*Game)=1;
                 
		SDL_BlitSurface(e->win,NULL,ecran,&position);
		SDL_Flip(ecran);
                 Mix_PlayChannel(-1,win1,0);
		SDL_Delay(3000);
		return 0;//win
	}
	else
	{
		(*Game)=0;
		SDL_BlitSurface(e->lost,NULL,ecran,&position);
		SDL_Flip(ecran);
                Mix_PlayChannel(-1,lose1,0);
		SDL_Delay(3000);
		return 0;//lost
	}
}

int Play_Enigme(Enigme *e,SDL_Surface *ecran,int *Game)
{
	Display_Enigme(e,ecran);
	SDL_Event event;
	while(1)
	{
		Display_Enigme(e,ecran);//affichage

		while(SDL_PollEvent(&event))
		{
		switch (event.type)
		{ 
			case SDL_KEYDOWN:
			{
				if(event.key.keysym.sym==SDLK_UP)
				{
					e->image_courrante--;
					if(e->image_courrante<1)
					{
						e->image_courrante=4;
					}
				}
				else if(event.key.keysym.sym==SDLK_DOWN)
				{
					e->image_courrante++;
					if(e->image_courrante>4)
					{
						e->image_courrante=1;
					}
		
				}
				else if(event.key.keysym.sym==SDLK_RETURN)
				{
					return Verify_Enigme(e,Game,ecran);
				}
				break;
			}
			case SDL_MOUSEMOTION:
			{
				printf("Souris en position %d %d\n",event.motion.x, event.motion.y);
			}
			case SDL_MOUSEBUTTONUP:
			{

				if(event.motion.x>280 && event.motion.x<525 && event.motion.y>255 && event.motion.y<290)
				{
					e->image_courrante=1;	 
					if (event.button.button == SDL_BUTTON_LEFT)
					{ 
						return Verify_Enigme(e,Game,ecran);
					}
					break;
				}
				else if(event.motion.x>280 && event.motion.x<525 && event.motion.y>300 && event.motion.y<335)
				{
					e->image_courrante=2;			 
					if (event.button.button == SDL_BUTTON_LEFT)
					{ 
						return Verify_Enigme(e,Game,ecran);
					}
					break;
				}
				else if(event.motion.x>280 && event.motion.x<525 && event.motion.y>350 && event.motion.y<380)
				{
					e->image_courrante=3;	
					if (event.button.button == SDL_BUTTON_LEFT)
					{ 
						return Verify_Enigme(e,Game,ecran);
					}
					break;
				}
				else if(event.motion.x>280 && event.motion.x<525 && event.motion.y>395 && event.motion.y<425)
				{
					e->image_courrante=4;	
					if (event.button.button == SDL_BUTTON_LEFT)
					{ 
						return Verify_Enigme(e,Game,ecran);
					}
					break;
				}
				break;
			}
			case SDL_QUIT:
			{	
				return 0;
			}
		}}
	}printf("sortie");
}



void animerEnigme (SDL_Surface *porte[14],SDL_Rect *port,SDL_Surface *ecran)
{
    int j;
    char ch[50];
 
    port->x=  0 ;
    port->y=  0 ;

    for(j=1; j<15; j++)
    {
        sprintf(ch,"../projet1/enigme/animation/%d.png",j);
        porte[j]=IMG_Load(ch);
    }

    for(j=1; j<15; j++)
    {
        SDL_BlitSurface(porte[j], NULL,ecran,port);
        SDL_Flip(ecran);
        SDL_Delay(120);
    }  
}

void animerEnigmee (SDL_Surface *porte[14],SDL_Rect *port,SDL_Surface *ecran)
{
    int j;
    char ch[50];
 
    port->x=  0 ;
    port->y=  0 ;

    for(j=1; j<14; j++)
    {
        sprintf(ch,"../projet1/enigme/animation/%d.png",j);
        porte[j]=IMG_Load(ch);
    }

    for(j=1; j<14; j++)
    {
        SDL_BlitSurface(porte[j], NULL,ecran,port);
        SDL_Flip(ecran);
        SDL_Delay(120);
    }  
}




void free_memory(Enigme *e ){

SDL_FreeSurface (e->background[0]) ;
SDL_FreeSurface (e->background[1]) ;
SDL_FreeSurface (e->win) ;
SDL_FreeSurface (e->lost) ;
for( int i=0;i<4;i++)
{
SDL_FreeSurface(e->reponses[i]) ;
}

}



