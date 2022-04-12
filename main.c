#include "fct.h"

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
	int done=0, P=0, P2=0, choice=-1, choice2=-1, choice3=-1, exit, O=0, volM, volS, NSFX=0, fulls=1, x;
	float i=0;
	char nbBG[20];
	SDL_Event event, event2, event3;
	text txt, txt1, txt2, txt3, txt4, qttxt;
	Mix_Music *music;
	Mix_Chunk * eff;
	atexit(SDL_Quit);
	
	screen=SDL_SetVideoMode(1914, 878, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	if(!screen)
	{
		printf("unable to open a 1914x878 wind %s\n", SDL_GetError());
		return 1;
	}
	music=Mix_LoadMUS("music menu.mp3");
	eff=Mix_LoadWAV("click.wav");
	
	initImg(&BG, "BG2.png", 0, 0);
	initImg(&BG2, "nBG.png", 0, 0);
	initImg(&str1, "start1.png", 694, 270);
	initImg(&str2, "start2.png", 694, 261);
	initImg(&sett1, "settings1.png", 694, 412);
	initImg(&sett2, "settings2.png", 694, 404);
	initImg(&cred1, "credits1.png", 694, 554);
	initImg(&cred2, "credits2.png", 694, 544);
	initImg(&qt1, "quit1.png", 694, 696);
	initImg(&qt2, "quit2.png", 694, 686);
	initImg(&settBG, "SettBG.png", 689, 100);
	initImg(&X1, "X.png", 1135, 180);
	initImg(&X2, "X2.png", 1135, 180);
	initImg(&arr1, "arrow1.png", 735, 180);
	initImg(&arr2, "arrow2.png", 735, 180);
	initImg(&sound1, "sound1.png", 809, 360);
	initImg(&sound2, "sound2.png", 809, 360);
	initImg(&plus1, "+.png", 1130, 378);
	initImg(&plus2, "+2.png", 1130, 378);
	initImg(&mins1, "-.png", 730, 378);
	initImg(&mins2, "-2.png", 730, 378);
	initImg(&on, "on.png", 833, 480);
	initImg(&off, "off.png", 833, 450);
	initImg(&on2, "on.png", 1100, 480);
	initImg(&off2, "off.png", 1100, 480);
	initImg(&res, "res.png", 881, 625);
	initImg(&res1, "resF.png", 881, 625);
	initImg(&res2, "resXF.png", 881, 625);
	initImg(&qtBG, "qt conf.png", 450, 350);
	initImg(&YES, "YES.png", 810, 465);
	initImg(&YES2, "YES2.png", 810, 465);
	initImg(&NO, "NO.png", 1008, 465);
	initImg(&NO2, "NO2.png", 1008, 465);
	initImg(&cred, "credits.png", 720, 270);
	for (x=0; x<=117; x++)
	{
		sprintf(nbBG, "frames/BG%d.jpg", x);
		initImg(&Menu_anime[x], nbBG, 0, 0);
	}

	initTitle(&txt, 650, 90, 80, "Bleeding_Cowboys.ttf");
	initText(&qttxt, 660, 375, 40, "MedusaGothic D.otf");
	initText(&txt1, 720, 270, 50, "MedusaGothic D.otf");
	initText(&txt2, 1020, 475, 32, "MedusaGothic D.otf");
	initText(&txt3, 760, 535, 50, "MedusaGothic D.otf");
	
	Mix_PlayMusic(music, -1);
	volM=Mix_VolumeMusic(MIX_MAX_VOLUME/2);
	volM=MIX_MAX_VOLUME/2;
	volS=Mix_Volume(-1, volM);
	sound2.pos_img.w=150;
	while(!done)
	{
		if(x>117)
			i=0;
		i+=0.2;
		x=i;
		SDL_Flip(screen);
		SDL_PollEvent(&event);
		
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_DOWN:
					afficher_img(Menu_anime[x], screen);
					affichertxt(txt, screen, "HSAN EL KAYLA");
						if(P==0)
						{
							P=1;
							afficher_img(str1, screen);
							afficher_img(sett2, screen);
							afficher_img(cred1, screen);
							afficher_img(qt1, screen);
						}
						else if(P==1)
						{
							P=2;
							afficher_img(str1, screen);
							afficher_img(sett1, screen);
							afficher_img(cred2, screen);
							afficher_img(qt1, screen);
						}
						else if(P==2)
						{
							P=3;
							afficher_img(str1, screen);
							afficher_img(sett1, screen);
							afficher_img(cred1, screen);
							afficher_img(qt2, screen);
						}
						else if(P==3)
						{
							P=0;
							afficher_img(str2, screen);
							afficher_img(sett1, screen);
							afficher_img(cred1, screen);
							afficher_img(qt1, screen);
						}
						Mix_PlayChannel(-1, eff, 0);
						SDL_Delay(200);
						break;
					case SDLK_UP:
						afficher_img(Menu_anime[x], screen);
						affichertxt(txt, screen, "HSAN EL KAYLA");
						if(P==0)
						{
							P=3;
							afficher_img(str1, screen);
							afficher_img(sett1, screen);
							afficher_img(cred1, screen);
							afficher_img(qt2, screen);
						}
						else if(P==1)
						{
							P=0;
							afficher_img(str2, screen);
							afficher_img(sett1, screen);
							afficher_img(cred1, screen);
							afficher_img(qt1, screen);
						}
						else if(P==2)
						{
							P=1;
							afficher_img(str1, screen);
							afficher_img(sett2, screen);
							afficher_img(cred1, screen);
							afficher_img(qt1, screen);
						}
						else if(P==3)
						{
							P=2;
							afficher_img(str1, screen);
							afficher_img(sett1, screen);
							afficher_img(cred2, screen);
							afficher_img(qt1, screen);
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
			case SDL_KEYUP:
				afficher_img(Menu_anime[x], screen);
				affichertxt(txt, screen, "HSAN EL KAYLA");
				if(P==0)
				{
					afficher_img(str2, screen);
					afficher_img(sett1, screen);
					afficher_img(cred1, screen);
					afficher_img(qt1, screen);
				}
				else if(P==1)
				{
					afficher_img(str1, screen);
					afficher_img(sett2, screen);
					afficher_img(cred1, screen);
					afficher_img(qt1, screen);
				}
				else if(P==2)
				{
					afficher_img(str1, screen);
					afficher_img(sett1, screen);
					afficher_img(cred2, screen);
					afficher_img(qt1, screen);
				}
				else if(P==3)
				{
					afficher_img(str1, screen);
					afficher_img(sett1, screen);
					afficher_img(cred1, screen);
					afficher_img(qt2, screen);
				}
				else
				{
					afficher_img(str1, screen);
					afficher_img(sett1, screen);
					afficher_img(cred1, screen);
					afficher_img(qt1, screen);
				}
				break;

			case SDL_MOUSEMOTION:
				afficher_img(Menu_anime[x], screen);
				affichertxt(txt, screen, "HSAN EL KAYLA");
				if(event.motion.x>=694 && event.motion.x<=694+str1.pos_img.w && event.motion.y>=270 && event.motion.y<=270+str1.pos_img.h)
				{
					afficher_img(str2, screen);
					afficher_img(sett1, screen);
					afficher_img(cred1, screen);
					afficher_img(qt1, screen);
					if(P!=0)
						Mix_PlayChannel(-1, eff, 0);
					P=0;
				}
				else if(event.motion.x>=694 && event.motion.x<=694+sett1.pos_img.w && event.motion.y>=412 && event.motion.y<=404+sett1.pos_img.h)
				{
					afficher_img(str1, screen);
					afficher_img(sett2, screen);
					afficher_img(cred1, screen);
					afficher_img(qt1, screen);
					if(P!=1)
						Mix_PlayChannel(-1, eff, 0);
					P=1;
				}
				else if(event.motion.x>=694 && event.motion.x<=694+cred1.pos_img.w && event.motion.y>=554 && event.motion.y<=554+cred1.pos_img.h)
				{
					afficher_img(str1, screen);
					afficher_img(sett1, screen);
					afficher_img(cred2, screen);
					afficher_img(qt1, screen);
					if(P!=2)
						Mix_PlayChannel(-1, eff, 0);
					P=2;
				}
				else if(event.motion.x>=694 && event.motion.x<=694+qt1.pos_img.w && event.motion.y>=696 && event.motion.y<=696+qt1.pos_img.h)
				{
					afficher_img(str1, screen);
					afficher_img(sett1, screen);
					afficher_img(cred1, screen);
					afficher_img(qt2, screen);
					if(P!=3)
						Mix_PlayChannel(-1, eff, 0);
					P=3;
				}
				else
				{
					afficher_img(str1, screen);
					afficher_img(sett1, screen);
					afficher_img(cred1, screen);
					afficher_img(qt1, screen);
					
				}
				break;

			case SDL_MOUSEBUTTONDOWN :
				if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=694 && event.button.x<=694+str1.pos_img.w && event.button.y>=270 && event.button.y<=270+str1.pos_img.h)
				{
					choice=1;
				}
				else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=694 && event.button.x<=694+sett1.pos_img.w && event.button.y>=412 && event.button.y<=404+sett1.pos_img.h)
				{
					choice=2;
				}
				else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=694 && event.button.x<=694+cred1.pos_img.w && event.button.y>=554 && event.button.y<=554+cred1.pos_img.h)
				{
					choice=3;
				}
				else if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=694 && event.button.x<=694+qt1.pos_img.w && event.button.y>=696 && event.button.y<=696+qt1.pos_img.h)
				{
					choice=4;
				}
				break;

			case SDL_QUIT:
				done=1;
				break;
		}

		switch(choice)
		{
			case 1:
				exit=0;
				while(!exit)
				{
					afficher_img(BG, screen);
					SDL_Flip(screen);
					SDL_PollEvent(&event2);
					if(event2.type==SDL_KEYDOWN)
					{
						if(event2.key.keysym.sym==SDLK_ESCAPE)
						{
							exit=1;
							done=1;
						}
					}
				}
				break;
			case 2:
				exit=0;
				choice=-1;
				afficher_img(Menu_anime[x], screen);
				afficher_img(settBG, screen);
				afficher_img(arr1, screen);
				affichertxt(txt1, screen, "Sound:");
				afficher_img(sound1, screen);
				afficher_img(sound2, screen);
				afficher_img(plus1, screen);
				afficher_img(mins1, screen);
				affichertxt(txt2, screen, "SFX");
				affichertxt(txt3, screen, "Resolution:");
				afficher_img(res, screen);
				if(NSFX==0)
					afficher_img(on2, screen);
				else
					afficher_img(off2, screen);
				while(!exit)
				{
					if(x>117)
						i=0;
					i+=0.2;
					x=i;
					SDL_Flip(screen);
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
							
							case SDL_KEYUP:
								afficher_img(Menu_anime[x], screen);
								afficher_img(settBG, screen);
								affichertxt(txt1, screen, "Sound:");
								afficher_img(sound1, screen);
								afficher_img(sound2, screen);
								afficher_img(arr1, screen);
								afficher_img(plus1, screen);
								afficher_img(mins1, screen);
								affichertxt(txt2, screen, "SFX");
								affichertxt(txt3, screen, "Resolution:");
								afficher_img(res, screen);
								if(NSFX==0)
									afficher_img(on2, screen);
								else
									afficher_img(off2, screen);
							break;

						case SDL_MOUSEMOTION:
							if(event2.motion.x>=735 && event2.motion.x<=735+arr1.pos_img.w && event2.motion.y>=180 && event2.motion.y<=180+arr1.pos_img.h)
							{
								afficher_img(Menu_anime[x], screen);
								afficher_img(settBG, screen);
								affichertxt(txt1, screen, "Sound:");
								afficher_img(sound1, screen);
								afficher_img(sound2, screen);
								afficher_img(arr2, screen);
								afficher_img(plus1, screen);
								afficher_img(mins1, screen);
								affichertxt(txt2, screen, "SFX");
								affichertxt(txt3, screen, "Resolution:");
								afficher_img(res, screen);
								if(O!=1 && NSFX==0)
								{
									Mix_PlayChannel(-1, eff, 0);
									O=1;
								}
							}
							else if(event2.motion.x>=1130 && event2.motion.x<=1130+plus1.pos_img.w && event2.motion.y>=378 && event2.motion.y<=378+plus1.pos_img.h)
							{
								afficher_img(Menu_anime[x], screen);
								afficher_img(settBG, screen);
								affichertxt(txt1, screen, "Sound:");
								afficher_img(sound1, screen);
								afficher_img(sound2, screen);
								afficher_img(arr1, screen);
								afficher_img(plus2, screen);
								afficher_img(mins1, screen);
								affichertxt(txt2, screen, "SFX");
								affichertxt(txt3, screen, "Resolution:");
								afficher_img(res, screen);
								if(O!=2 && NSFX==0)
								{
									Mix_PlayChannel(-1, eff, 0);
									O=2;
								}
							}
							else if(event2.motion.x>=730 && event2.motion.x<=730+mins1.pos_img.w && event2.motion.y>=378 && event2.motion.y<=378+mins1.pos_img.h)
							{
								afficher_img(Menu_anime[x], screen);
								afficher_img(settBG, screen);
								affichertxt(txt1, screen, "Sound:");
								afficher_img(sound1, screen);
								afficher_img(sound2, screen);
								afficher_img(arr1, screen);
								afficher_img(plus1, screen);
								afficher_img(mins2, screen);
								affichertxt(txt2, screen, "SFX");
								affichertxt(txt3, screen, "Resolution:");
								afficher_img(res, screen);
								if(O!=3 && NSFX==0)
								{
									Mix_PlayChannel(-1, eff, 0);
									O=3;
								}
							}	
							else if(event2.motion.x>=881 && event2.motion.x<=881+res.pos_img.w && event2.motion.y>=625 && event2.motion.y<=625+res.pos_img.h)
							{
								afficher_img(Menu_anime[x], screen);
								afficher_img(settBG, screen);
								affichertxt(txt1, screen, "Sound:");
								afficher_img(sound1, screen);
								afficher_img(sound2, screen);
								afficher_img(arr1, screen);
								afficher_img(plus1, screen);
								afficher_img(mins1, screen);
								affichertxt(txt2, screen, "SFX");
								affichertxt(txt3, screen, "Resolution:");
								if(fulls==1)
									afficher_img(res2, screen);
								else
									afficher_img(res1, screen);
							}
							else
							{
								O=0;
								afficher_img(Menu_anime[x], screen);
								afficher_img(settBG, screen);
								affichertxt(txt1, screen, "Sound:");
								afficher_img(sound1, screen);
								afficher_img(sound2, screen);
								afficher_img(arr1, screen);
								afficher_img(plus1, screen);
								afficher_img(mins1, screen);
								affichertxt(txt2, screen, "SFX");
								affichertxt(txt3, screen, "Resolution:");
								afficher_img(res, screen);
							}
							if(NSFX==0)
								afficher_img(on2, screen);
							else
								afficher_img(off2, screen);
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
							exit=1;
							break;
					}
					switch(choice2)
					{
						case 1:
							exit=1;
							choice=-1;
							afficher_img(Menu_anime[x], screen);
							affichertxt(txt, screen, "HSAN EL KAYLA");
							afficher_img(str1, screen);
							afficher_img(sett2, screen);
							afficher_img(cred1, screen);
							afficher_img(qt1, screen);
							SDL_Delay(500);
							break;

						case 2:
							afficher_img(Menu_anime[x], screen);
							afficher_img(settBG, screen);
							afficher_img(arr1, screen);
							affichertxt(txt1, screen, "Sound:");
							afficher_img(sound1, screen);
							afficher_img(plus1, screen);
							afficher_img(mins1, screen);
							affichertxt(txt2, screen, "SFX");
							affichertxt(txt3, screen, "Resolution:");
							afficher_img(res, screen);
							if(volM!=MIX_MAX_VOLUME)
							{
								if(volM==0)
								{
									sound2.pos_img.w=75;
									afficher_img(sound2, screen);
								}
								else if(volM==MIX_MAX_VOLUME/4)
								{
									sound2.pos_img.w=150;
									afficher_img(sound2, screen);
								}
								else if(volM==MIX_MAX_VOLUME/2)
								{
									sound2.pos_img.w=225;
									afficher_img(sound2, screen);
								}
								else if(volM==MIX_MAX_VOLUME*3/4)
								{
									sound2.pos_img.w=300;
									afficher_img(sound2, screen);
								}
								volM=Mix_VolumeMusic(volM+MIX_MAX_VOLUME/4);
								volM=Mix_VolumeMusic(-1);
								if(NSFX==0)
									volS=Mix_Volume(-1, volM);
							}
							else
							{
								sound2.pos_img.w=300;
								afficher_img(sound2, screen);
							}
							if(NSFX==0)
								afficher_img(on2, screen);
							else
								afficher_img(off2, screen);
							SDL_Delay(500);
							afficher_img(plus1, screen);
							break;

						case 3:
							afficher_img(Menu_anime[x], screen);
							afficher_img(settBG, screen);
							afficher_img(arr1, screen);
							affichertxt(txt1, screen, "Sound:");
							afficher_img(sound1, screen);
							afficher_img(plus1, screen);
							afficher_img(mins1, screen);
							affichertxt(txt2, screen, "SFX");
							affichertxt(txt3, screen, "Resolution:");
							afficher_img(res, screen);
							if(volM!=0)
							{
								if(volM==MIX_MAX_VOLUME)
								{
									sound2.pos_img.w=225;
									afficher_img(sound2, screen);
								}		
								else if(volM==MIX_MAX_VOLUME*3/4)
								{
									sound2.pos_img.w=150;
									afficher_img(sound2, screen);
								}		
								else if(volM==MIX_MAX_VOLUME/2)
								{
									sound2.pos_img.w=75;
									afficher_img(sound2, screen);
								}		
								else if(volM==MIX_MAX_VOLUME/4)
								{
									sound2.pos_img.w=0;
									afficher_img(sound2, screen);
								}		
								volM=Mix_VolumeMusic(volM-MIX_MAX_VOLUME/4);
								volM=Mix_VolumeMusic(-1);
								if(NSFX==0)
									volS=Mix_Volume(-1, volM);
							}
							if(NSFX==0)
								afficher_img(on2, screen);
							else
								afficher_img(off2, screen);
							SDL_Delay(500);
							afficher_img(mins1, screen);
							break;

						case 4:
							if(NSFX!=1)
							{
								afficher_img(off2, screen);
								volS=Mix_Volume(-1, 0);
								NSFX=1;
							}
							else
							{
								afficher_img(on2, screen);
								NSFX=0;
								if(volM!=0)
									volS=Mix_Volume(-1, volM);
								else
									volS=Mix_Volume(-1, MIX_MAX_VOLUME/2);
							}
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
							SDL_Delay(500);
							break;
					}
					choice2=-1;
				}
				break;

			case 3:
				choice=-1;
				exit=0;
				while(exit!=1)
				{
					SDL_Flip(screen);
					if(x>117)
						i=0;
					i+=0.2;
					x=i;
					afficher_img(Menu_anime[x], screen);
					afficher_img(settBG, screen);
					afficher_img(arr1, screen);
					afficher_img(cred, screen);
					SDL_PollEvent(&event3);
					if(event3.type==SDL_KEYDOWN)
					{
						if(event3.key.keysym.sym==SDLK_BACKSPACE)
						exit=1;
						afficher_img(Menu_anime[x], screen);
						affichertxt(txt, screen, "HSAN EL KAYLA");
						afficher_img(str1, screen);
						afficher_img(sett2, screen);
						afficher_img(cred1, screen);
						afficher_img(qt1, screen);
						SDL_Delay(500);
					}
					else if(event3.type==SDL_MOUSEMOTION && SDL_BUTTON_LEFT && event3.motion.x>=735 && event3.motion.x<=735+arr1.pos_img.w && event3.motion.y>=180 && event3.motion.y<=180+arr1.pos_img.h)
					{
						afficher_img(Menu_anime[x], screen);
						afficher_img(settBG, screen);
						afficher_img(arr2, screen);
						afficher_img(cred, screen);
					}
					else if(event3.type==SDL_MOUSEMOTION && SDL_BUTTON_LEFT && event3.motion.x<735 && event3.motion.x>735+arr1.pos_img.w && event3.motion.y<180 && event3.motion.y>180+arr1.pos_img.h)
					{
						afficher_img(Menu_anime[x], screen);
						afficher_img(settBG, screen);
						afficher_img(arr1, screen);
						afficher_img(cred, screen);
					}
					else if(event3.type==SDL_MOUSEBUTTONDOWN && SDL_BUTTON_LEFT && event3.motion.x>=735 && event3.motion.x<=735+arr1.pos_img.w && event3.motion.y>=180 && event3.motion.y<=180+arr1.pos_img.h)
					{
						exit=1;
						afficher_img(Menu_anime[x], screen);
						affichertxt(txt, screen, "HSAN EL KAYLA");
						afficher_img(str1, screen);
						afficher_img(sett2, screen);
						afficher_img(cred1, screen);
						afficher_img(qt1, screen);
						SDL_Delay(500);
					}
				}
				break;

			case 4:
				exit=0;
				P2=0;
				afficher_img(Menu_anime[x], screen);
				afficher_img(qtBG, screen);
				affichertxt(qttxt, screen, "Do you want to quit?");
				afficher_img(YES, screen);
				afficher_img(NO2, screen);
				while(exit==0)
				{
					if(x>117)
						i=0;
					i+=0.2;
					x=i;
					SDL_Flip(screen);
					SDL_PollEvent(&event3);
					switch(event3.type)
					{
						case SDL_KEYDOWN:
							switch(event3.key.keysym.sym)
								{
									case SDLK_LEFT:
										P2=0;
										afficher_img(Menu_anime[x], screen);
										afficher_img(qtBG, screen);
										affichertxt(qttxt, screen, "Do you want to quit?");
										afficher_img(YES2, screen);
										afficher_img(NO, screen);
										break;

									case SDLK_RIGHT:
										P2=1;
										afficher_img(Menu_anime[x], screen);
										afficher_img(qtBG, screen);
										affichertxt(qttxt, screen, "Do you want to quit?");
										afficher_img(YES, screen);
										afficher_img(NO2, screen);
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
							
							case SDL_KEYUP:
								if(P2==0)
								{
									afficher_img(Menu_anime[x], screen);
									afficher_img(qtBG, screen);
									affichertxt(qttxt, screen, "Do you want to quit?");
									afficher_img(YES2, screen);
									afficher_img(NO, screen);
								}
								else if(P2==1)
								{
									afficher_img(Menu_anime[x], screen);
									afficher_img(qtBG, screen);
									affichertxt(qttxt, screen, "Do you want to quit?");
									afficher_img(YES, screen);
									afficher_img(NO2, screen);
								}
							break;
						
						case SDL_MOUSEMOTION:
							afficher_img(Menu_anime[x], screen);
							if(event3.motion.x>=1008 && event3.motion.x<=1008+NO.pos_img.w && event3.motion.y>=465 && event3.motion.y<=465+NO.pos_img.h)
							{
								afficher_img(Menu_anime[x], screen);
								afficher_img(qtBG, screen);
								affichertxt(qttxt, screen, "Do you want to quit?");
								afficher_img(YES, screen);
								afficher_img(NO2, screen);
								if(P2!=0 && NSFX==0)
									Mix_PlayChannel(-1, eff, 0);
								P2=0;
							}
							else if(event3.motion.x>=810 && event3.motion.x<=810+YES.pos_img.w && event3.motion.y>=465 && event3.motion.y<=465+YES.pos_img.h)
							{
								afficher_img(Menu_anime[x], screen);
								afficher_img(qtBG, screen);
								affichertxt(qttxt, screen, "Do you want to quit?");
								afficher_img(YES2, screen);
								afficher_img(NO, screen);
								if(P2!=1 && NSFX==0)
									Mix_PlayChannel(-1, eff, 0);
								P2=1;
							}
							else
							{
								afficher_img(Menu_anime[x], screen);
								afficher_img(qtBG, screen);
								affichertxt(qttxt, screen, "Do you want to quit?");
								afficher_img(YES, screen);
								afficher_img(NO, screen);
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
						exit=1;
						done=1;
						choice=-1;
						choice3=-1;
					}
					else if(choice3==2)
					{
						exit=1;
						choice=-1;
						choice3=-1;
						afficher_img(Menu_anime[x], screen);
						affichertxt(txt, screen, "HSAN EL KAYLA");
						afficher_img(str1, screen);
						afficher_img(sett1, screen);
						afficher_img(cred1, screen);
						afficher_img(qt2, screen);
						SDL_Delay(500);
					}
				}
				break;
		}
	}
	for(i=0; i<=117; i++)
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
	return 0;
}

