/**
GUERY Angèle
HELIN Dylan
**/

#include "head.h"


int main() {
    srand(time(NULL));
    int tour=1; //numero du tour, si c impair c au blanc sinon au noir

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
    int a;
    Joueur j1,j2;
    Plateau p;
    CoupsJouables tab;
    bool IA1,IA2;
    menuChoixJoueur(&IA1, &IA2);
    initialisationJoueur(&j1, &j2, IA1, IA2);
    initialisationPlateau (p);
    if (j1.couleur==1){
        printf("Le joueur 1 est de couleur Blanche et le joueur 2 est de couleur Noire\nLe joueur 1 commence \n");
    } else{
        printf("Le joueur 1 est de couleur Noire et le joueur 2 est de couleur Blanche\nLe joueur 2 commence \n");
    }

    while (victoire(p)==0){
        afficherTourJoueur(tour, j1);
        a = initialiserLesCoups(tab,p,tour);
        affichage (p,tab);
        if (a==0){
            tour = tour+1;
            printf("\n Vous ne pouvez rien placer, vous passez votre tour\n");
        } else{
            tour=placerPion(tour,tab,p);
        }
    }
    affichage (p,tab);
    a=victoire(p);
    if (a>0){
        printf("Victoire des Blancs\n");
    } else{
        if (a<0){
            printf("Victoire des Noirs\n");
        }else{
            printf("Egalite\n");
        }
    }

}
