/**
GUERY Angèle
HELIN Dylan
**/

#include "head.h"


int main() {
    srand(time(NULL));
    int tabValCaseIA[8][8]={
            {500, -150,30,10,10,30,-150,500},
            {-150,-250,0,0,0,0,-250,-150},
            {30,0,1,2,2,1,0,30},
            {10,0,2,16,16,2,0,10},
            {10,0,2,16,16,2,0,10},
            {30,0,1,2,2,1,0,30},
            {-150,-250,0,0,0,0,-250,-150},
            {500, -150,30,10,10,30,-150,500}
    };

    Joueur j1,j2;
    Plateau p;
    CoupsJouables tab;


    initialisationJoueur(&j1, &j2, false, false);
    initialisationPlateau (p);

    int a = initialiserLesCoups(tab,p,1);
    affichage (p,tab);
}
