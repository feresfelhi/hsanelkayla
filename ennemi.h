#define ENNEMI_H_INCLUDED
void initEnnemi(Ennemi*e)
void afficherEnnemi(Ennemi e,SDL_Surface *screen)
void animerEnnemi(Ennemi * e)
int collisionBB(personne p, Ennemi e)
void deplacerA(Ennemi * e , SDL_Rect posPerso)
#endif
