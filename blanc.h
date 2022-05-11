#ifndef BLANC_H_INCLUDED
#define BLANC_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>

#define NUMBER_OF_TILES 3 //considere l'ecran comme des petite cases et au lieu d'utiliser toute une image on utilise que une petite image qui va etre decoupe et reutiliser a partie de notre besoin 
#define HEIGHT_CELL 128 //hauteur de la cellule de la grille
#define WIDTH_CELL 128 //largeur de la cellule de la grille

typedef short bool;
#define true 1
#define false 0

enum {FREE = 0, PLAYER1 = 1, PLAYER2 = 2}; //enumeration / declaration de nouveaux enumeration si la case est vide la matrice prend la valeur de free si elle est occupe par le 1er joueur alors la matrice prend la valeur de player1 sinon elle prend la valeur de Player 2

//structure du tils 
typedef struct 
{
  SDL_Surface *image;
  SDL_Rect pos[NUMBER_OF_TILES];
} tiles;

//structure de la grille
typedef struct 
{
 int matrice[3][3];
 SDL_Surface *ecran;
 tiles til;
}grille;

void InitGrille (grille * g) ; //initialisation de la grille
void freeGrille (grille * g); //liberer la grille
bool complete (const int matrice[3][3]); //matrice complette ou les 0 n'existe pas : personne ne gagne
bool ligne (const int matrice[3][3] , int ligne); //une ligne est faite d'ou victoire
bool colone (const int matrice[3][3], int colone); // une colone est faite d'ou victoire
bool diagonale (const int matrice[3][3]); //une diagonale est faite d'ou une victoire
bool perdu (const int matrice[3][3] , bool * victory); //le joueur a perdu
void player1 (grille *g); //joueur 
void player2 (grille *g); //ordinateur
void jeux (grille *g , int *v); //fonction du jeux
void affichage(grille *g);

#endif



/*typedef struct 
{
  SDL_Rect posgrille;
  SDL_Surface *grille;
  SDL_Rect posx;
  SDL_Surface *x;
  SDL_Rect poso;
  SDL_Surface *o;
  int tab[9];
  SDL_Rect pos1case;
  int joueur1;
  int nb_tour;
  SDL_Surface *txt;
  TTF_Font *police = NULL;
  SDL_Color couleur ;
  SDL_Rect post;
  char text[30];
}tic;

void initialiserTic (tic * t);
void aficherTic (int tabsuivi[],SDL_Surface * ecran);
int atilganer (int tabsuivi[]);
void resultat (int tabsuivi[], SDL_Surface * ecran );
void liberer (tic t);
int minmax (int tabsuivi[9], int joueur);
void calcul_coup (int tabsuivi[9]);*/
