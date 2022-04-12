#include "fonctionperso.h"

void initPerso(Personne *p){

int sc;
//vi=initTextvie(&p->vie);
sc=initTextscore(&p->score);

//(*p).
  p->vie=IMG_Load("vie1.png");
  p->posvie.x=40;
		p->posvie.y=40;
(*p).image=IMG_Load("spritesheet mc.png");  

p->position.x=0;
p->position.y=700;

p->frame.w=50;
p->frame.h=110;
p->frame.x=0;
p->frame.y=0;

p->nbframe=0;
p->test=1;
p->direction=0;
p->courant=0;

p->vx = 4;
p->vgrav = 0.3;
p->vsaut = -6.5;
p->vy = p->vsaut;

p->acceleration=5;
p->vitesse=0;

}
void afficherPerso (Personne p,SDL_Surface *screen){

	//displayvie(p.vie,screen);
SDL_BlitSurface(p.vie,NULL,screen,&(p.posvie));     
	displayscore(p.score,screen);
	SDL_BlitSurface(p.image,&(p.frame),screen,&(p.position));     
}



void deplacerPerso(Personne *p ,SDL_Surface *screen,int dt){ 
	//p->direction=dt;

	if(dt!= p->courant)
	{
		p->direction=0;// la yemshy la 3al imine o la 3al isar o la ynagez 
		p->courant = p->direction;
	}
	
	if (dt==0){
		while(p->position.y<700) 
   		{ 
     			p->position.y+=3;
    		}
    		p->direction=dt;
    		animerPerso(p);
	
	}
	
	if (dt==1){
		p->position.x+=p->vitesse; 
		p->direction=dt;
		animerPerso(p);
	
	}
   	
 	if (dt==2){
   		p->position.x-=p->vitesse;
   		p->direction=dt;
   		animerPerso(p);
	
	}
	
	if (dt==3){
		 
		p->position.y-=2; 
	 
	}
}


void animerPerso(Personne *p){

	if(p->direction==1)
	{
		p->frame.y=0;
		p->nbframe++;
	if(p->nbframe>=4)
	{
		p->nbframe=0;
	}
		p->frame.x=p->nbframe * p->frame.w;  

	}	
	else
		if(p->direction==2)
		{ 
			p->frame.y=110;
			p->nbframe++;
		if(p->nbframe>=4)
		{
			p->nbframe=0;
		}
		p->frame.x=p->nbframe * p->frame.w;  
  
		}
	else 
		if(p->direction==0)
		{
			p->frame.x=0;

		}

}


void saut(Personne *p){
	
	if(p->position.y<700){
   	p->position.x += p->vx;
   	p->position.y+= p->vy;
   	p->vy += p->vgrav;
   }
  	if (p->position.y> 700)
    	p->vy = p->vsaut;
}
void vitesseUP(Personne *p){
	 SDL_Delay(10);
       
         p->vitesse+=p->acceleration;
         p->position.x+=p->vitesse;
         p->direction=1;
         if(p->vitesse>=30)
         {
          p->vitesse=30;
         }
}
void vitesseDOWN(Personne *p){
 	p->vitesse=0; 

}





























