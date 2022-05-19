#include "blanc.h"
#include <stdio.h>

void InitGrille (grille * g)
{
  const char *resource[] = {"Tileset2.bmp"}; //resource graphique 
  int i,j;
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Unable to load SDL ! %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
  atexit(SDL_Quit);
  for (i=0;i<3;i++)
    for (j=0;j<3;j++)
     {
       g->matrice[i][j] = FREE; //la matrice est initialiser a 0
     }
  g->ecran = SDL_SetVideoMode(1914, 878, 32, SDL_HWSURFACE|SDL_DOUBLEBUF| SDL_RESIZABLE);
  g->til.image = SDL_LoadBMP(resource[0]); //telechargement de l'image resource
  for (i=0;i<NUMBER_OF_TILES;i++) //initialisation des dimensions des cases de la grilles
  {
    g->til.pos[i].h = HEIGHT_CELL;
    g->til.pos[i].w = WIDTH_CELL;
    g->til.pos[i].x = i*WIDTH_CELL;
    g->til.pos[i].y = 0;
  }
}

void freeGrille (grille * g)
{
    SDL_FreeSurface(g->til.image);
    g->til.image = NULL;
}

bool complete(const int matrice[3][3])
{
  int i ,j ;
  for (i=0;i<3;i++)
   {
     for (j=0;j<3;j++)
      {
        if (matrice[i][j] == FREE) //s'il existe encore des cases aves une valeurs 0 alors le jeu n'est pas encore termine 
          return false ;
      }
   }
   return true; //toutes les cases sont remplises aucune n'a une valeur egale a 0
}

bool ligne (const int matrice[3][3] , int ligne)
{
  int i;
  int test = matrice[ligne][0]; //initialisation d'un entier test dans la valeur contenu par l'une des cases dans la 1 ere colone 
  if (test == FREE) //la valeur de la case est egale a 0
   {
     return false ;
   }
  for (i=0;i<3;i++)
   {
     if (matrice[ligne][i] != test)// la case dans la meme ligne et differenete colone ne possede pas la meme valeur que test
       return false;
   }
  return true ; //3 case taht b3athhom ont la meme valeur (soit 1 soit 2)
}

bool colone (const int matrice[3][3], int colone)
{
  int i ;
  int test = matrice[0][colone]; //initialisation d'un entier test dans la valeur contenu par l'une des cases dans la 1 ere ligne
  if (test == FREE) //la valeur de la case est egale a 0
    return false;
  for (i=0;i<3;i++)
    if(matrice[i][colone]!=test) // la case dans la meme colone et differenet ligne ne possede pas la meme valeur que test
      return false;
  return true; //3 case taht b3athhom ont la meme valeur (soit 1 soit 2)
}

bool diagonale (const int matrice[3][3])
{
  bool ret = true; //variable de type boolean pour stocker notre resultat
  int i;
  int test = matrice[0][0]; //initialisation d'un entier test a la premier case de la matrice
  if (test == FREE) //la 1ere case a une valeur 0
    ret = false;
  if (ret ) //cad la case a une valeur differentes de 0
  {
    for (i=0;i<3;i++)
      if ( matrice[i][i] != test ) //les cases de la diagonales n'ont pas la meme valeurs de la premier case de la matrice
        ret = false ;
  }
  if (ret) //les cases de la 1ere diagonale ont la meme valeur -> VICTOIRE
    return true ;
  test = matrice[0][2]; //changement de diagonale (2eme diagonale)
  if (test == FREE) //la 1ere case de la 2 eme diagonale a une valeur 0
    return false;
  for (i=0;i<3;i++)
    if (matrice[i][2-i] != test) //les cases de la 2 eme diagonale n'ont pas la meme valeurs de la premier case de la diagonale , le parcour se fait 2_i car le parcour se fait de facon ywa5ar b tweli
      return false;
  return true; //la 2eme diagonal est valide ->VICTOIRE
}

bool perdu (const int matrice[3][3] , bool * victory)
{
  int i;
  *victory = false; //initialisation de defat a faux
  for (i=0;i<3;i++)
   {
     if (ligne(matrice,i) || colone(matrice,i)) //si une ligne ou une colone est valide alors VICTOIRE
       return true;
   }
   if (diagonale(matrice)) //si une diagonale est valide alors VICTOIRE
       return true;
   *victory = true;
   if (complete(matrice)) //si la matrice est complete sans aucune validation alors la perte est aussi vrai 
      return true;
   return false;
}

void player1 (grille *g) 
{
  SDL_Event e;
  do
   {
     SDL_WaitEvent(&e); // on attends que le joueur choisi la position de son x
   }
  while (e.type !=SDL_MOUSEBUTTONDOWN ||e.button.button != SDL_BUTTON_LEFT || g->matrice[e.button.y/HEIGHT_CELL][e.button.x/WIDTH_CELL] != FREE); //mouvement et clic sourit 
  g->matrice[e.button.y/HEIGHT_CELL][e.button.x/WIDTH_CELL] = PLAYER1; //la cellule choisit prend x = 1
}

void player2 (grille *g)
{
   int copie[3][3];
   bool victory ;
   int x , y;
   for (x=0 ; x<3 ; x++)
     for (y=0 ; y<3 ; y++)
       {
         copie[x][y] = g->matrice[x][y];
       } 
   for (x=0;x<3;x++)
    {
      for (y=0;y<3;y++)
       {
         if (copie[x][y] == FREE)
          {
            copie[x][y] = PLAYER1;
            if (perdu((const int(*)[3])copie,&victory))
             {
               g->matrice[x][y] = PLAYER2;
               return;
             }
            copie[x][y] = PLAYER2;
            if (perdu((const int(*)[3])copie,&victory))
             {
               g->matrice[x][y] = PLAYER1;
               return ;
             }
             copie[x][y] = FREE;
          }
       }
    }
   do
    {
      x = rand()%3; //generation aleatoire de x
      y = rand()%3; //generation aleatoire de y 
    }
   while (g->matrice[x][y] != FREE); //jusqu'a nil9aw case vide w n3abiwha b 2 
   g->matrice[x][y] = PLAYER2; //il case heki tit3aba b o 
}

void jeux (grille *g ,int *v ) //fonction du jeux 
{
  int dernierjoueur;
  bool victory ; //booleene pour tester la perte et la victoire
  while (!perdu((const int(*)[3])g->matrice,&victory)) // pas de perte victory = true 
  {
    affichage(g);
    SDL_Flip (g->ecran);
    player1(g); //joueur 1 joue 
    dernierjoueur = 1;
    if (!perdu((const int(*)[3])g->matrice,&victory)) //pas de perte victory = true 
     {
       affichage(g);
       player2(g); //l'ordinateur joue son jeux
       dernierjoueur = 2;
     }
    else
      break;
  }
 affichage(g);
 if (!victory)
  {
    printf ("perdant \n");
    *v = 1;
  } 
  else
   {
     printf ("gagnant \n");
     *v = 0;
   }
   
   
}

void affichage(grille *g)
{
    int i, j;
    SDL_Rect dst;
    for(i = 0; i < 3; ++i)
    {
        dst.x = i*WIDTH_CELL;
        for(j = 0; j < 3; ++j)
        {
            dst.y = j*HEIGHT_CELL;
            SDL_BlitSurface(g->til.image, &g->til.pos[g->matrice[j][i]], g->ecran, &dst);
        }
    }
}
/*void initialiserTic (tic * t)
{
  int i;
  t->grille = IMG_Load("grille.jpg");
  t->x = IMG_Load("x.jpg");
  t->o = IMG_Load("X-Letter-PNG-HD.png");
  t->posgrille.x=600;
  t->posgrille.y=600;
  for (i=0;i<9;i++)
  {
    tab[i]=0;
  }
  t->joueur1 = 1;
  t->nb_tour = 0;
  police = TTF_OpenFont("Urusans.TTF",40);
  couleur = {0,0,0} ;
  t->post.x=0; 
  t->post.y=0;
}

void aficherTic (int tabsuivi[],SDL_Surface * ecran)
{
  
}*/
